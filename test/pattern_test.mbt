///|
type Range (Int, Int) derive(Eq, Hash, ToJson)

///|
impl Show for Range with output(self : Range, logger : &Logger) -> Unit {
  logger.write_object(self._)
}

///|
struct Environment {
  vars : Map[String, Array[Range]]
  ranges : Map[Range, String]
}

///|
fn Environment::add_var(
  self : Environment,
  name : String,
  range : Range
) -> Unit {
  self.ranges[range] = name
  match self.vars.get(name) {
    None => self.vars.set(name, [range])
    Some(ranges) => ranges.push(range)
  }
}

///|
struct Query {
  source : String
  capture : Array[String]
}

///|
type! PatternError {
  NestedPattern(Int)
  MetaVarOutOfPattern(Int)
  UnterminatedPattern
}

///|
fn pattern_query(
  parser : @tree_sitter.Parser,
  env : Environment,
  pattern : String
) -> Query! {
  struct Context {
    replaced : StringBuilder
    brackets : Array[Int]
    mut start : Int?
    mut end : Int?
    mut var : (Int, StringBuilder)?
  }
  let context = Context::{
    replaced: StringBuilder::new(),
    brackets: [],
    start: None,
    end: None,
    var: None,
  }
  loop 0, pattern.view() {
    offset, ['$', '[', .. pattern] => {
      if context.var is Some(_) {
        raise MetaVarOutOfPattern(offset)
      }
      if context.start is Some(_) {
        raise NestedPattern(offset)
      }
      context.replaced.write_string("  ")
      context.start = Some(offset)
      continue offset + 2, pattern
    }
    offset, ['[', .. pattern] => {
      context.replaced.write_char('[')
      if context.start is Some(_) {
        context.brackets.push(offset)
      }
      continue offset + 1, pattern
    }
    offset, [']', .. pattern] =>
      match context.start {
        None => {
          context.replaced.write_char(']')
          continue offset + 1, pattern
        }
        Some(_) =>
          match context.brackets.pop() {
            None => {
              context.end = Some(offset)
              context.replaced.write_char(' ')
              continue offset + 1, pattern
            }
            Some(_) => {
              context.replaced.write_char(']')
              continue offset + 1, pattern
            }
          }
      }
    offset, ['$', .. pattern] => {
      if context.start is None {
        raise MetaVarOutOfPattern(offset)
      }
      context.replaced.write_char('_')
      match context.var {
        None => context.var = Some((offset, StringBuilder::new()))
        Some((start, name)) => {
          env.add_var(name.to_string(), (start, offset))
          context.var = Some((offset, StringBuilder::new()))
        }
      }
      continue offset + 1, pattern
    }
    offset, [char, .. pattern] =>
      match context.var {
        None => {
          context.replaced.write_char(char)
          continue offset + 1, pattern
        }
        Some((start, name)) =>
          if char.is_ascii_alphabetic() {
            context.replaced.write_char(' ')
            name.write_char(char)
            continue offset + 1, pattern
          } else {
            context.replaced.write_char(char)
            env.add_var(name.to_string(), (start, offset))
            continue offset + 1, pattern
          }
      }
    offset, [] =>
      if context.var is Some((start, name)) {
        env.add_var(name.to_string(), (start, offset))
      }
  }
  guard context.start is Some(pattern_start) && context.end is Some(pattern_end) else {
    raise UnterminatedPattern
  }
  let context = context.replaced.to_string()
  let context_tree = parser.parse_string(None, context)
  let context_root = context_tree.root_node()
  let capture_name : Array[String] = []
  fn generate_pattern(node : @tree_sitter.Node, stripping : Bool?) -> String {
    if node.start_byte() <= pattern_start || node.end_byte() >= pattern_end {
      let child_patterns = []
      for child in node.children() {
        if child.end_byte() <= pattern_start ||
          child.start_byte() >= pattern_end {
          continue
        }
        if child.is_named() && child.type_() == "semicolon" {
          continue
        }
        child_patterns.push(generate_pattern(child, None))
      }
      match child_patterns {
        [] => {
          println("Unable to generate pattern for node: \{node.type_()}")
          panic()
        }
        [child_pattern] => return child_pattern
        child_patterns => {
          let pattern = StringBuilder::new()
          pattern.write_char('(')
          pattern.write_string(child_patterns.join(" "))
          pattern.write_char(')')
          return pattern.to_string()
        }
      }
    }
    if node.child_count() == 1 {
      if stripping is Some(true) || stripping is None {
        return generate_pattern(node.child(0).unwrap(), Some(true))
      }
    }
    let stripping = Some(false)
    if not(node.is_named()) {
      if node.type_() == "_" {
        for range, name in env.ranges {
          if node.start_byte() == range._.0 {
            let mut exists = false
            for old_name in capture_name {
              if old_name == name {
                exists = true
                break
              }
            }
            if not(exists) {
              capture_name.push(name)
            }
            return "(_) @\{name}"
          }
        }
      }
      return node.string()
    }
    let child_patterns = []
    for child in node.children() {
      if child.is_named() && child.type_() == "semicolon" {
        continue
      }
      child_patterns.push(generate_pattern(child, stripping))
    }
    let child_patterns = child_patterns.join(" ")
    return "(\{node.type_()} \{child_patterns})"
  }

  let pattern = generate_pattern(context_root, None)
  let pattern = pattern + " @pattern"
  capture_name.push("pattern")
  { source: pattern, capture: capture_name }
}

///|
fn node_equal(node : @tree_sitter.Node, other : @tree_sitter.Node) -> Bool {
  if node.type_() != other.type_() {
    return false
  }
  for i in 0..<node.child_count() {
    match (node.child(i), other.child(i)) {
      (Some(self_child), Some(other_child)) =>
        if not(node_equal(self_child, other_child)) {
          return false
        }
      _ => return false
    }
  }
  return true
}

///|
test "pattern" {
  let env = Environment::{ vars: Map::new(), ranges: Map::new() }
  let pattern =
    #|fn main {
    #|  $[ $A == $A ]
    #|}
  let source =
    #|fn main {
    #|  if 1 == 1 {
    #|    println("Hello, world!")
    #|  }
    #|}
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_moonbit.language()
  parser.set_language(language)
  let source_tree = parser.parse_string(None, source)
  let source_root = source_tree.root_node()
  let pattern_query = pattern_query!(parser, env, pattern)
  inspect!(
    pattern_query.source,
    content=
      #|(binary_expression (compound_expression (simple_expression (_) @A)) ("==") (compound_expression (simple_expression (_) @A))) @pattern
    ,
  )
  let query = @tree_sitter.Query::new!(language, pattern_query.source)
  let query_cursor = @tree_sitter.QueryCursor::new()
  query_cursor.exec(query, source_root)
  let ranges = []
  while true {
    let next_match = query_cursor.next_match()
    guard next_match is Some(match_) else { break }
    let meta_var_nodes : Map[String, Array[@tree_sitter.Node]] = {}
    for capture in match_.captures {
      let capture_index = capture.index
      let name = pattern_query.capture[capture_index]
      match meta_var_nodes.get(name) {
        None => meta_var_nodes.set(name, [capture.node])
        Some(nodes) => nodes.push(capture.node)
      }
    }
    let mut satisfied = true
    for _, nodes in meta_var_nodes {
      for i in 1..<nodes.length() {
        if not(node_equal(nodes[i], nodes[0])) {
          satisfied = false
          break
        }
      }
      if not(satisfied) {
        break
      }
    }
    if satisfied {
      let pattern_node = meta_var_nodes["pattern"].unwrap()[0]
      let (start, end) = (pattern_node.start_byte(), pattern_node.end_byte())
      let text = source[start:end]
      ranges.push((text, start, end))
    }
  }
  inspect!(
    ranges,
    content=
      #|[("1 == 1", 15, 21)]
    ,
  )
}

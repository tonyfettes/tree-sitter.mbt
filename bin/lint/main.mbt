///|
type Rule String

///|
let rule_set : Map[String, Rule] = {
  let trivial_equal =
    #|fn main {
    #|  $[ $A == $A ]
    #|}
  { "trivial_equal": trivial_equal }
}

///|
type! PatternError {
  NestedPattern(Int)
  MetaVarOutOfPattern(Int)
  UnterminatedPattern
}

///|
struct Pattern {
  source : String
  capture : Array[String]
  vars : Map[String, Array[(Int, Int)]]
  ranges : Map[(Int, Int), String]
}

///|
pub fn Pattern::parse(
  source : String,
  parser : @tree_sitter.Parser
) -> Pattern!PatternError {
  struct Context {
    replaced : StringBuilder
    brackets : Array[Int]
    mut start : Int?
    mut end : Int?
    mut var : (Int, StringBuilder)?
  }
  let meta_vars : Map[String, Array[(Int, Int)]] = {}
  let meta_ranges : Map[(Int, Int), String] = {}
  fn env_add_var(name : String, range : (Int, Int)) {
    meta_ranges[range] = name
    match meta_vars.get(name) {
      None => meta_vars.set(name, [range])
      Some(ranges) => ranges.push(range)
    }
  }

  let context = Context::{
    replaced: StringBuilder::new(),
    brackets: [],
    start: None,
    end: None,
    var: None,
  }
  loop 0, source[:] {
    offset, ['$', '[', .. source] => {
      if context.var is Some(_) {
        raise MetaVarOutOfPattern(offset)
      }
      if context.start is Some(_) {
        raise NestedPattern(offset)
      }
      context.replaced.write_string("  ")
      context.start = Some(offset)
      continue offset + 2, source
    }
    offset, ['[', .. source] => {
      context.replaced.write_char('[')
      if context.start is Some(_) {
        context.brackets.push(offset)
      }
      continue offset + 1, source
    }
    offset, [']', .. source] =>
      match context.start {
        None => {
          context.replaced.write_char(']')
          continue offset + 1, source
        }
        Some(_) =>
          match context.brackets.pop() {
            None => {
              context.end = Some(offset)
              context.replaced.write_char(' ')
              continue offset + 1, source
            }
            Some(_) => {
              context.replaced.write_char(']')
              continue offset + 1, source
            }
          }
      }
    offset, ['$', .. source] => {
      if context.start is None {
        raise MetaVarOutOfPattern(offset)
      }
      context.replaced.write_char('_')
      match context.var {
        None => context.var = Some((offset, StringBuilder::new()))
        Some((start, name)) => {
          env_add_var(name.to_string(), (start, offset))
          context.var = Some((offset, StringBuilder::new()))
        }
      }
      continue offset + 1, source
    }
    offset, [char, .. source] =>
      match context.var {
        None => {
          context.replaced.write_char(char)
          continue offset + 1, source
        }
        Some((start, name)) =>
          if char.is_ascii_alphabetic() {
            context.replaced.write_char(' ')
            name.write_char(char)
            continue offset + 1, source
          } else {
            context.replaced.write_char(char)
            env_add_var(name.to_string(), (start, offset))
            continue offset + 1, source
          }
      }
    offset, [] =>
      if context.var is Some((start, name)) {
        env_add_var(name.to_string(), (start, offset))
      }
  }
  guard context.start is Some(pattern_start) && context.end is Some(pattern_end) else {
    raise UnterminatedPattern
  }
  let context = context.replaced.to_string()
  let context_tree = parser.parse_string(None, context)
  let context_root = context_tree.root_node()
  let capture_name : Array[String] = []
  fn generate_query(node : @tree_sitter.Node, stripping : Bool?) -> String {
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
        child_patterns.push(generate_query(child, None))
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
        return generate_query(node.child(0).unwrap(), Some(true))
      }
    }
    let stripping = Some(false)
    if not(node.is_named()) {
      if node.type_() == "_" {
        for range, name in meta_ranges {
          if node.start_byte() == range.0 {
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
      child_patterns.push(generate_query(child, stripping))
    }
    let child_patterns = child_patterns.join(" ")
    return "(\{node.type_()} \{child_patterns})"
  }

  let query = generate_query(context_root, None)
  let query = query + " @pattern"
  capture_name.push("pattern")
  { source: query, capture: capture_name, vars: meta_vars, ranges: meta_ranges }
}

///|
fn node_equal(
  source : String,
  node : @tree_sitter.Node,
  other : @tree_sitter.Node
) -> Bool {
  if node.type_() != other.type_() {
    return false
  }
  if node.child_count() is 1 && other.child_count() is 1 {
    let node_text = source[node.start_byte():node.end_byte()]
    let other_text = source[other.start_byte():other.end_byte()]
    if node_text.to_string() != other_text.to_string() {
      return false
    }
  }
  for i in 0..<node.child_count() {
    match (node.child(i), other.child(i)) {
      (Some(self_child), Some(other_child)) =>
        if not(node_equal(source, self_child, other_child)) {
          return false
        }
      _ => return false
    }
  }
  return true
}

///|
pub fn Pattern::search(
  self : Pattern,
  source : String,
  node : @tree_sitter.Node,
  language : @tree_sitter.Language
) -> Array[@tree_sitter.Node]! {
  let query = @tree_sitter.Query::new!(language, self.source)
  let query_cursor = @tree_sitter.QueryCursor::new()
  query_cursor.exec(query, node)
  let instances = []
  while true {
    guard query_cursor.next_match() is Some(match_) else { break }
    let meta_var_nodes : Map[String, Array[@tree_sitter.Node]] = {}
    for capture in match_.captures {
      let capture_index = capture.index
      let name = self.capture[capture_index]
      match meta_var_nodes.get(name) {
        None => meta_var_nodes.set(name, [capture.node])
        Some(nodes) => nodes.push(capture.node)
      }
    }
    let mut satisfied = true
    for _, nodes in meta_var_nodes {
      for i in 1..<nodes.length() {
        if not(node_equal(source, nodes[i], nodes[0])) {
          satisfied = false
          break
        }
      }
      if not(satisfied) {
        break
      }
    }
    if satisfied {
      let matched = meta_var_nodes["pattern"].unwrap()[0]
      instances.push(matched)
    }
  }
  instances
}

///|
fn main {
  try {
    let args = @sys.get_cli_args()
    guard args is [_, source_path] else {
      println("Usage: \{args[0]} <source_path>")
      panic()
    }
    let source = @fs.read_file_to_string!(source_path)
    let lines = source.split("\n").collect()
    let parser = @tree_sitter.Parser::new()
    let language = @tree_sitter_moonbit.language()
    parser.set_language(language)
    let source_tree = parser.parse_string(None, source)
    let source_root = source_tree.root_node()
    for name, rule in rule_set {
      let pattern = Pattern::parse!(rule._, parser)
      let instances = pattern.search!(source, source_root, language)
      for instance in instances {
        let start = instance.start_point()
        let end = instance.end_point()
        println(name)
        let start_row = start.row()
        for i, line in lines[start.row():end.row() + 1] {
          println("\{start_row + i} | \{line}")
        }
      }
    }
  } catch {
    error => {
      if "a" == "a" {
        println("xxx")
      }
      println("Error: \{error}")
    }
  }
}

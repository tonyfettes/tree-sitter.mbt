///|
type Range (UInt, UInt) derive(Eq, Hash, ToJson)

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
fn pattern_query(
  parser : @tree_sitter.Parser,
  language : @tree_sitter.Language,
  env : Environment,
  pattern : String
) -> Query! {
  let replaced = StringBuilder::new()
  loop 0U, pattern[:], None {
    offset, ['$', .. pattern], None => {
      replaced.write_char('_')
      continue offset + 1, pattern, Some((offset, StringBuilder::new()))
    }
    offset, ['$', .. pattern], Some((start, pattern_identifier)) => {
      replaced.write_char('_')
      env.add_var(pattern_identifier.to_string(), (start, offset))
      continue offset + 1, pattern, Some((offset, StringBuilder::new()))
    }
    offset, [char, .. pattern], Some((start, pattern_identifier)) =>
      if char.is_ascii_alphabetic() {
        replaced.write_char(' ')
        pattern_identifier.write_char(char)
        continue offset + 1, pattern, Some((start, pattern_identifier))
      } else {
        replaced.write_char(char)
        env.add_var(pattern_identifier.to_string(), (start, offset))
        continue offset + 1, pattern, None
      }
    offset, [char, .. pattern], None => {
      replaced.write_char(char)
      continue offset + 1, pattern, None
    }
    offset, [], Some((start, pattern_identifier)) =>
      env.add_var(pattern_identifier.to_string(), (start, offset))
    _, [], None => ()
  }
  let replaced = replaced.to_string()
  println("replaced = \{replaced}")
  let context =
    $|fn main {
    $|  \{replaced}
    $|}
  let extract_query =
    #|(structure
    #| (structure_item
    #|  (function_definition
    #|   (block_expression
    #|    (statement_expression
    #|     (expression
    #|      (pipeline_expression
    #|       (compound_expression
    #|        (binary_expression) @pattern))))))))
  let context_tree = parser.parse_string(None, context)
  let context_root = context_tree.root_node()
  println("context_root = \{context_root}")
  let extract_query = @tree_sitter.Query::new!(language, extract_query)
  let query_cursor = @tree_sitter.QueryCursor::new()
  query_cursor.exec(extract_query, context_root)
  guard query_cursor.next_capture() is Some(pattern_capture) else {
    println("Error: pattern not found")
    panic()
  }
  let pattern_node = pattern_capture.node
  let capture_name : Array[String] = []
  fn generate_pattern(node : @tree_sitter.Node) -> String {
    if not(node.is_named()) {
      if node.type_() == "_" {
        for range, name in env.ranges {
          if node.start_byte() == pattern_node.start_byte() + range._.0 {
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
      child_patterns.push(generate_pattern(child))
    }
    let child_patterns = child_patterns.join(" ")
    return "(\{node.type_()} \{child_patterns})"
  }

  let pattern = generate_pattern(pattern_capture.node) + " @pattern"
  capture_name.push("pattern")
  { source: pattern, capture: capture_name }
}


///|
fn node_equal(node : @tree_sitter.Node, other : @tree_sitter.Node) -> Bool {
  if node.type_() != other.type_() {
    return false
  }
  for i in 0U..<node.child_count() {
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
test "a" {
  let env = Environment::{ vars: Map::new(), ranges: Map::new() }
  let pattern =
    #|$A == $A
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
  let pattern_query = pattern_query!(parser, language, env, pattern)
  inspect!(
    pattern_query.source,
    content=
      #|(binary_expression (compound_expression (simple_expression (_) @A)) ("==") (compound_expression (simple_expression (_) @A))) @pattern
    ,
  )
  let query = @tree_sitter.Query::new!(language, pattern_query.source)
  let query_cursor = @tree_sitter.QueryCursor::new()
  query_cursor.exec(query, source_root)
  while true {
    let next_match = query_cursor.next_match()
    if next_match is None {
      break
    }
    let match_ = next_match.unwrap()
    let meta_var_nodes : Map[String, Array[@tree_sitter.Node]] = {}
    for capture in match_.captures {
      let capture_index = capture.index.reinterpret_as_int()
      println("Capture: \{capture_index}")
      let name = pattern_query.capture[capture_index]
      println("Capture Name: \{name}")
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
      println("Patter found: \{start} - \{end}")
      let text = source[start.reinterpret_as_int():end.reinterpret_as_int()]
      println("Source: \{text}")
    }
  }
}

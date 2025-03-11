///|
type Rule String

///|
let rule_set : Map[String, Rule] = {
  let trivial_equal =
    #|$A == $A
  { "trivial_equal": trivial_equal }
}

///|
struct Context {
  vars : Map[String, Array[(UInt, UInt)]]
  ranges : Map[(UInt, UInt), String]
}

///|
fn Context::add_var(
  self : Context,
  name : String,
  range : (UInt, UInt)
) -> Unit {
  self.ranges[range] = name
  match self.vars.get(name) {
    None => self.vars.set(name, [range])
    Some(ranges) => ranges.push(range)
  }
}

///|
type! PatternError {
  NestedContext(UInt)
  MetaVarOutOfContext(UInt)
  UnterminatedContext
}

///|
fn search(rule : Rule, source : String) -> Array[((UInt, UInt), String)]! {
  let pattern = rule._
  let meta_vars : Map[String, Array[(UInt, UInt)]] = {}
  let meta_ranges : Map[(UInt, UInt), String] = {}
  fn add_meta_var(identifier : String, range : (UInt, UInt)) -> Unit {
    meta_ranges[range] = identifier
    match meta_vars.get(identifier) {
      None => meta_vars.set(identifier, [range])
      Some(ranges) => ranges.push(range)
    }
  }

  let replaced = StringBuilder::new()
  let brackets = []
  loop 0U, pattern[:], false, None {
    offset, ['$', '[', .. pattern], false, None => {
      continue offset + 2, pattern, true, None
    }
    offset, ['$', '[', ..], _, _ => raise NestedContext(offset)
    offset, [_, ..], false, Some(_) => raise MetaVarOutOfContext(offset)
    offset, [_, .. pattern], false, None => {
      continue offset + 1, pattern, false, None
    }
    offset, ['[', .. pattern], true, None => {
      brackets.push(offset)
      replaced.write_char('[')
      continue offset + 1, pattern, true, None
    }
    offset, ['$', .. pattern], true, None => {
      replaced.write_char('_')
      continue offset + 1, pattern, true, Some((offset, StringBuilder::new()))
    }
    offset, ['$', .. pattern], true, Some((start, pattern_identifier)) => {
      replaced.write_char('_')
      add_meta_var(pattern_identifier.to_string(), (start, offset))
      continue offset + 1, pattern, true, Some((offset, StringBuilder::new()))
    }
    offset, [char, .. pattern], true, Some((start, pattern_identifier)) =>
      if char.is_ascii_alphabetic() {
        replaced.write_char(' ')
        pattern_identifier.write_char(char)
        continue offset + 1, pattern, true, Some((start, pattern_identifier))
      } else {
        replaced.write_char(char)
        add_meta_var(pattern_identifier.to_string(), (start, offset))
        continue offset + 1, pattern, true, None
      }
    offset, [char, .. pattern], true, None => {
      replaced.write_char(char)
      continue offset + 1, pattern, true, None
    }
    _, [], true, _ => raise UnterminatedContext
    _, [], false, _ => ()
  }
  let replaced = replaced.to_string()
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
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_moonbit.language()
  parser.set_language(language)
  let source_tree = parser.parse_string(None, source)
  let context_tree = parser.parse_string(None, context)
  let source_root = source_tree.root_node()
  let context_root = context_tree.root_node()
  let extract_query = @tree_sitter.Query::new!(language, extract_query)
  let query_cursor = @tree_sitter.QueryCursor::new()
  query_cursor.exec(extract_query, context_root)
  guard query_cursor.next_capture() is Some(pattern_capture)
  let pattern_node = pattern_capture.node
  let capture_name : Array[String] = []
  fn generate_pattern(node : @tree_sitter.Node) -> String {
    if not(node.is_named()) {
      if node.type_() == "_" {
        for range, name in meta_ranges {
          if node.start_byte() == pattern_node.start_byte() + range.0 {
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

  fn node_equal(self : @tree_sitter.Node, other : @tree_sitter.Node) -> Bool {
    if self.type_() != other.type_() {
      return false
    }
    for i in 0U..<self.child_count() {
      match (self.child(i), other.child(i)) {
        (Some(self_child), Some(other_child)) =>
          if not(node_equal(self_child, other_child)) {
            return false
          }
        _ => return false
      }
    }
    return true
  }

  let pattern = generate_pattern(pattern_capture.node) + " @pattern"
  capture_name.push("pattern")
  println("Pattern: \{pattern}")
  let query = @tree_sitter.Query::new!(language, pattern)
  query_cursor.exec(query, source_root)
  let result = []
  while query_cursor.next_match() is Some(match_) {
    let meta_var_nodes : Map[String, Array[@tree_sitter.Node]] = {}
    for capture in match_.captures {
      let capture_index = capture.index.reinterpret_as_int()
      println("Capture: \{capture_index}")
      let name = capture_name[capture_index]
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
      let text = source[start.reinterpret_as_int():end.reinterpret_as_int()]
      result.push(((start, end), text.to_string()))
    }
  }
  result
}

///|
fn main {
  try {
    let args = @sys.get_cli_args()
    guard args is [_, source_path] else {
      println("Usage: \{args[0]} <source_path>")
      @sys.exit(1)
    }
    let source = @fs.read_file_to_string!(source_path)
    for name, rule in rule_set {
      for result in search!(rule, source) {
        println("Rule: \{name}")
        println("Range: \{result.0}")
        println("Text: \{result.1}")
      }
    }
  } catch {
    error => println("Error: \{error}")
  }
}

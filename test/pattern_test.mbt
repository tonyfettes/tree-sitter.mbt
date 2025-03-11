///|
test {
  let pattern =
    #|$A == $A
  let source =
    #|fn main {
    #|  if 1 == 1 {
    #|    println("Hello, world!")
    #|  }
    #|}
  let meta_vars : Map[String, Array[(UInt, UInt)]] = {}
  let meta_ranges : Map[(UInt, UInt), String] = {}
  fn add_meta_var(identifier : String, range : (UInt, UInt)) -> Unit {
    meta_ranges[range] = identifier
    match meta_vars.get(identifier) {
      None => meta_vars.set(identifier, [range])
      Some(ranges) => ranges.push(range)
    }
  }

  fn islower(char : Char) -> Bool {
    char >= 'a' && char <= 'z'
  }

  fn isupper(char : Char) -> Bool {
    char >= 'A' && char <= 'Z'
  }

  fn isalpha(char : Char) -> Bool {
    islower(char) || isupper(char)
  }

  let replaced = StringBuilder::new()
  loop 0U, pattern[:], None {
    offset, ['$', .. pattern], None => {
      replaced.write_char('_')
      continue offset + 1, pattern, Some((offset, StringBuilder::new()))
    }
    offset, ['$', .. pattern], Some((start, pattern_identifier)) => {
      replaced.write_char('_')
      add_meta_var(pattern_identifier.to_string(), (start, offset))
      continue offset + 1, pattern, Some((offset, StringBuilder::new()))
    }
    offset, [char, .. pattern], Some((start, pattern_identifier)) =>
      if isalpha(char) {
        replaced.write_char(' ')
        pattern_identifier.write_char(char)
        continue offset + 1, pattern, Some((start, pattern_identifier))
      } else {
        replaced.write_char(char)
        add_meta_var(pattern_identifier.to_string(), (start, offset))
        continue offset + 1, pattern, None
      }
    offset, [char, .. pattern], None => {
      replaced.write_char(char)
      continue offset + 1, pattern, None
    }
    offset, [], Some((start, pattern_identifier)) =>
      add_meta_var(pattern_identifier.to_string(), (start, offset))
    _, [], None => ()
  }
  let replaced = replaced.to_string()
  @json.inspect!(meta_vars, content={ "A": [[0, 2], [6, 8]] })
  @json.inspect!(meta_ranges, content={ "(0, 2)": "A", "(6, 8)": "A" })
  @json.inspect!(replaced, content="_  == _ ")
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
  @json.inspect!(@sexp.parse!(source_root.string()), content=[
    [
      "structure",
      [
        "structure_item",
        [
          "function_definition",
          ["function_identifier", ["lowercase_identifier"]],
          [
            "block_expression",
            [
              "statement_expression",
              [
                "expression",
                [
                  "if_expression",
                  [
                    "compound_expression",
                    [
                      "binary_expression",
                      [
                        "compound_expression",
                        [
                          "simple_expression",
                          [
                            "atomic_expression",
                            ["literal", ["integer_literal"]],
                          ],
                        ],
                      ],
                      [
                        "compound_expression",
                        [
                          "simple_expression",
                          [
                            "atomic_expression",
                            ["literal", ["integer_literal"]],
                          ],
                        ],
                      ],
                    ],
                  ],
                  [
                    "block_expression",
                    [
                      "statement_expression",
                      [
                        "expression",
                        [
                          "pipeline_expression",
                          [
                            "compound_expression",
                            [
                              "simple_expression",
                              [
                                "apply_expression",
                                [
                                  "simple_expression",
                                  [
                                    "qualified_identifier",
                                    ["lowercase_identifier"],
                                  ],
                                ],
                                [
                                  "argument",
                                  [
                                    "expression",
                                    [
                                      "pipeline_expression",
                                      [
                                        "compound_expression",
                                        [
                                          "simple_expression",
                                          [
                                            "atomic_expression",
                                            [
                                              "literal",
                                              [
                                                "string_literal",
                                                [
                                                  "string_fragment",
                                                  ["unescaped_string_fragment"],
                                                ],
                                              ],
                                            ],
                                          ],
                                        ],
                                      ],
                                    ],
                                  ],
                                ],
                              ],
                            ],
                          ],
                        ],
                      ],
                    ],
                    ["semicolon", ["automatic_semicolon"]],
                  ],
                ],
              ],
            ],
            ["semicolon", ["automatic_semicolon"]],
          ],
        ],
      ],
    ],
  ])
  let context_root = context_tree.root_node()
  @json.inspect!(@sexp.parse!(context_root.string()), content=[
    [
      "structure",
      [
        "structure_item",
        [
          "function_definition",
          ["function_identifier", ["lowercase_identifier"]],
          [
            "block_expression",
            [
              "statement_expression",
              [
                "expression",
                [
                  "pipeline_expression",
                  [
                    "compound_expression",
                    [
                      "binary_expression",
                      ["compound_expression", ["simple_expression"]],
                      ["compound_expression", ["simple_expression"]],
                    ],
                  ],
                ],
              ],
            ],
            ["semicolon", ["automatic_semicolon"]],
          ],
        ],
      ],
    ],
  ])
  let extract_query = @tree_sitter.Query::new!(language, extract_query)
  let query_cursor = @tree_sitter.QueryCursor::new()
  query_cursor.exec(extract_query, context_root)
  guard query_cursor.next_capture() is Some(pattern_capture)
  @json.inspect!(@sexp.parse!(pattern_capture.node.string()), content=[
    [
      "binary_expression",
      ["compound_expression", ["simple_expression"]],
      ["compound_expression", ["simple_expression"]],
    ],
  ])
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
      println("Patter found: \{start} - \{end}")
      let text = source[start.reinterpret_as_int():end.reinterpret_as_int()]
      println("Source: \{text}")
    }
  }
}

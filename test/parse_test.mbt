///|
test "json" {
  let json = @tree_sitter_json.language()
  let parser = @tree_sitter.Parser::new()
  parser.set_language(json)
  let source =
    #|{
    #|  "name": "John Doe",
    #|  "age": 43
    #|}
  let tree = parser.parse_string(None, source)
  let root_node = tree.root_node()
  inspect!(
    root_node.string(),
    content="(document (object (pair key: (string (string_content)) value: (string (string_content))) (pair key: (string (string_content)) value: (number))))",
  )
  let root_node_first_child = root_node.child(0).map(@tree_sitter.Node::string)
  inspect!(
    root_node_first_child,
    content=
      #|Some("(object (pair key: (string (string_content)) value: (string (string_content))) (pair key: (string (string_content)) value: (number)))")
    ,
  )
}

///|
test "moonbit" {
  let moonbit = @tree_sitter_moonbit.language()
  let parser = @tree_sitter.Parser::new()
  parser.set_language(moonbit)
  let source =
    #|fn main {
    #|  println("Hello, World!")
    #|}
  let tree = parser.parse_string(None, source)
  let root_node = tree.root_node()
  inspect!(
    root_node.string(),
    content="(structure (structure_item (function_definition (function_identifier (lowercase_identifier)) (block_expression (statement_expression (expression (pipeline_expression (compound_expression (simple_expression (apply_expression (simple_expression (qualified_identifier (lowercase_identifier))) (argument (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment)))))))))))))))) (semicolon (automatic_semicolon))))))",
  )
}

///|
test "query" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_moonbit.language()
  parser.set_language(language)
  let source =
    #|fn main {
    #|  if 1 == 1 {
    #|    println("Hello, world!")
    #|  }
    #|  for i = 0; i < 10; i = i + 1 {
    #|    println("Hello, world!")
    #|  }
    #|}
  let source_tree = parser.parse_string(None, source)
  let source_root = source_tree.root_node()
  let query =
    #|(for_expression) @forExpression
  let query = @tree_sitter.Query::new!(language, query)
  let query_cursor = @tree_sitter.QueryCursor::new()
  query_cursor.exec(query, source_root)
  guard query_cursor.next_match() is Some(match_) else {
    fail!("Expected match")
  }
  inspect!(
    match_.captures[0].node,
    content="(for_expression (for_keyword) (for_binder (lowercase_identifier) (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))) (semicolon) (compound_expression (binary_expression (compound_expression (simple_expression (qualified_identifier (lowercase_identifier)))) (compound_expression (simple_expression (atomic_expression (literal (integer_literal))))))) (semicolon) (for_binder (lowercase_identifier) (expression (pipeline_expression (compound_expression (binary_expression (compound_expression (simple_expression (qualified_identifier (lowercase_identifier)))) (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))))) (block_expression (statement_expression (expression (pipeline_expression (compound_expression (simple_expression (apply_expression (simple_expression (qualified_identifier (lowercase_identifier))) (argument (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment)))))))))))))))) (semicolon (automatic_semicolon))))",
  )
}

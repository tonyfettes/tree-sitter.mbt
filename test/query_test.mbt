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
  let source_tree = parser
    .parse_string(source)
    .or_error!(Failure("Parse error"))
  let source_root = source_tree.root_node()
  let query =
    #|(for_expression) @forExpression
  let query = @tree_sitter.Query::new!(language, query)
  let query_cursor = @tree_sitter.QueryCursor::new()
  query_cursor.exec(query, source_root)
  let matches : Array[@tree_sitter.QueryMatch] = []
  while query_cursor.next_match() is Some(matched) {
    matches.push(matched)
  }
  @json.inspect!(matches.length(), content=1)
}

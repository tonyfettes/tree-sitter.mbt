///|
test {
  let language = @tree_sitter_moonbit.language()
  let parser = @tree_sitter.Parser::new()
  parser.set_language!(language)
  let source =
    #|fn main {
    #|  let test :
  let tree = parser.parse_string!(source)
  let root_node = tree.root_node()
  inspect!(
    root_node,
    content=
      #|(structure
      #| (ERROR
      #|  (function_identifier
      #|   (lowercase_identifier))
      #|  (pattern
      #|   (simple_pattern
      #|    (lowercase_identifier)))
      #|  (colon)))
    ,
  )
  let tree_cursor = @tree_sitter.TreeCursor::new(root_node)
  assert_true!(tree_cursor.goto_first_child())
  assert_true!(tree_cursor.goto_first_child())
  assert_true!(tree_cursor.goto_next_sibling())
  assert_true!(tree_cursor.goto_next_sibling())
  @json.inspect!(tree_cursor.current_node(), content={
    "node": "(\"{\")",
    "text": "{",
    "range": {
      "start": { "row": 0, "column": 8 },
      "end": { "row": 0, "column": 9 },
    },
  })
  tree_cursor.current_node().next_symbol_names().collect()
  |> @json.inspect!(content=[
    "end", "lowercase_identifier", "priv", "pub", "(", "readonly", "all", "open",
    ")", "derive_keyword", ",", "extern", "type", "!", "{", "}", "=", ".(", "typealias",
    "struct", "enum", "mut", "let", "const", "async", "fn", "test", "trait", "+",
    "_", "traitalias", "as", "fnalias", "impl", "with", "\"", "\\{", "true", "false",
    "integer_literal", "b'", "'", "b\"", "unescaped_string_fragment_token1", "escape_sequence_token1",
    "escape_sequence_token2", "escape_sequence_token3", "escape_sequence_token4",
    "escape_sequence_token5", "escape_sequence_token6", "multiline_string_separator",
    "multiline_interpolation_separator", "-", "pipe_operator", "*", "/", "%", "<<",
    ">>", ">", ">=", "<=", "<", "==", "!=", "&", "^", "|", "&&", "||", "..", "if",
    "=>", "~", "!!", "[", "]", "accessor_token1", "match", "break", "continue", "try",
    "catch", "else", "unfinished", "guard", "~:", "while", "loop", "for_keyword",
    "in", "return", "raise", "->", "uppercase_identifier", ";", "dot", "dot_dot_lt",
    "dot_dot_eq", "colon", "colon_colon", "question_operator", "is_keyword", "plus_equal",
    "minus_equal", "asterisk_equal", "slash_equal", "percent_equal", "dot_lowercase_identifier",
    "dot_uppercase_identifier", "package_identifier", "comment", "docstring", "#",
    "automatic_newline", "automatic_semicolon", "float_literal",
  ])
  let lookahead_iterator = @tree_sitter.LookaheadIterator::new(
    language,
    tree_cursor.current_node().next_parse_state(),
  ).or_error!(Failure("Failed to create lookahead iterator"))
  let names = []
  while lookahead_iterator.next() {
    let name = lookahead_iterator.current_symbol_name()
    if name is Some(name) {
      names.push(name)
    }
  }
  @json.inspect!(names, content=[
    "end", "lowercase_identifier", "priv", "pub", "(", "readonly", "all", "open",
    ")", "derive_keyword", ",", "extern", "type", "!", "{", "}", "=", ".(", "typealias",
    "struct", "enum", "mut", "let", "const", "async", "fn", "test", "trait", "+",
    "_", "traitalias", "as", "fnalias", "impl", "with", "\"", "\\{", "true", "false",
    "integer_literal", "b'", "'", "b\"", "unescaped_string_fragment_token1", "escape_sequence_token1",
    "escape_sequence_token2", "escape_sequence_token3", "escape_sequence_token4",
    "escape_sequence_token5", "escape_sequence_token6", "multiline_string_separator",
    "multiline_interpolation_separator", "-", "pipe_operator", "*", "/", "%", "<<",
    ">>", ">", ">=", "<=", "<", "==", "!=", "&", "^", "|", "&&", "||", "..", "if",
    "=>", "~", "!!", "[", "]", "accessor_token1", "match", "break", "continue", "try",
    "catch", "else", "unfinished", "guard", "~:", "while", "loop", "for_keyword",
    "in", "return", "raise", "->", "uppercase_identifier", ";", "dot", "dot_dot_lt",
    "dot_dot_eq", "colon", "colon_colon", "question_operator", "is_keyword", "plus_equal",
    "minus_equal", "asterisk_equal", "slash_equal", "percent_equal", "dot_lowercase_identifier",
    "dot_uppercase_identifier", "package_identifier", "comment", "docstring", "#",
    "automatic_newline", "automatic_semicolon", "float_literal",
  ])
}

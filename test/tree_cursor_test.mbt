///|
test "tree_cursor" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_json.language()
  parser.set_language(language)
  let source_code = "[1, null]"
  let tree = parser
    .parse_string(None, source_code)
    .or_error!(Failure("Parse error"))
  let root_node = tree.root_node()
  let tree_cursor = @tree_sitter.TreeCursor::new(root_node)
  inspect!(tree_cursor.goto_parent(), content="false")
  inspect!(
    tree_cursor.current_node(),
    content="(document (array (number) (null)))",
  )
  inspect!(tree_cursor.goto_first_child(), content="true")
  inspect!(tree_cursor.current_node(), content="(array (number) (null))")
  inspect!(tree_cursor.goto_next_sibling(), content="false")
  inspect!(tree_cursor.goto_first_child(), content="true")
  inspect!(
    tree_cursor.current_node(),
    content=
      #|("[")
    ,
  )
  inspect!(tree_cursor.goto_next_sibling(), content="true")
  inspect!(tree_cursor.current_node(), content="(number)")
  inspect!(tree_cursor.goto_next_sibling(), content="true")
  inspect!(
    tree_cursor.current_node(),
    content=
      #|(",")
    ,
  )
  inspect!(
    tree_cursor.goto_parent() && tree_cursor.goto_parent(),
    content="true",
  )
  inspect!(
    tree_cursor.current_node(),
    content="(document (array (number) (null)))",
  )
}

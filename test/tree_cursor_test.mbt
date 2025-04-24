///|
test "tree_cursor" {
  let parser = @tree_sitter.parser(@tree_sitter_json.language())
  let tree_cursor = parser.parse_string!("[1, null]").walk()
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

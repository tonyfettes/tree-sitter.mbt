///|
fn main {
  let args = @sys.get_cli_args()
  if args.length() != 2 {
    println("Usage: parse_json <path>")
    return
  }
  let path = args[1]
  guard @ts.Language::load(path, "json") is Some(json) else {
    println("Failed to load language")
    return
  }
  let parser = @ts.Parser::new()
  parser.set_language(json)
  let source_code = "[1, null]"
  let tree = parser.parse_string(None, source_code)
  let root_node = tree.root_node()
  let tree_cursor = @ts.TreeCursor::new(root_node)
  println(tree_cursor.goto_parent())
  println(tree_cursor.goto_first_child())
  println(tree_cursor.current_node().string())
  println(tree_cursor.goto_next_sibling())
  println(tree_cursor.goto_first_child())
  println(tree_cursor.current_node().string())
  println(tree_cursor.goto_next_sibling())
  println(tree_cursor.current_node().string())
  println(tree_cursor.goto_next_sibling())
  println(tree_cursor.current_node().string())
  println(tree_cursor.goto_parent() && tree_cursor.goto_parent())
  println(tree_cursor.current_node().string())
  tree_cursor.delete()
  tree.delete()
  parser.delete()
}

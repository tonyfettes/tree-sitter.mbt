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
  let array_node = root_node.named_child(0)
  let number_node = array_node.named_child(0)
  println(root_node.type_())
  println(array_node.type_())
  println(number_node.type_())
  println(root_node.child_count())
  println(array_node.child_count())
  println(array_node.named_child_count())
  println(number_node.child_count())
  println("Syntax tree: \{root_node.string()}")
  tree.delete()
  parser.delete()
}

///|
fn main {
  let json = @ts.Language::load("../tree-sitter-json/json.so", "json")
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
  tree.delete()
  parser.delete()
}

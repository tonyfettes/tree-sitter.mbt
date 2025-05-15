///|
test "node basic operations" {
  let parser = @tree_sitter.parser(@tree_sitter_json.language())
  let source =
    #|{"name": "test", "value": 123}
  let tree = parser.parse_string!(source)
  let root = tree.root_node()

  // Test basic node properties
  inspect!(root.type_(), content="document")
  inspect!(root.is_named(), content="true")
  inspect!(root.has_error(), content="false")

  // Test node navigation
  let object_node = root.child(0).or_error!(Failure("No object node"))
  inspect!(object_node.type_(), content="object")
  let name_pair = object_node.named_child(0).or_error!(Failure("No name pair"))
  let value_pair = object_node
    .named_child(1)
    .or_error!(Failure("No value pair"))
  inspect!(name_pair.type_(), content="pair")
  inspect!(value_pair.type_(), content="pair")

  // Test node position information
  inspect!(root.start_byte() == 0, content="true")
  let source_length = source.length()
  inspect!(root.end_byte() == source_length, content="true")

  // Test node text extraction
  let name_value = name_pair.child(1).or_error!(Failure("No name value")).text()
  inspect!(name_value, content=":")
}

///|
test "node iteration" {
  let parser = @tree_sitter.parser(@tree_sitter_json.language())
  let source =
    #|[1, 2, 3, 4, 5]
  let tree = parser.parse_string!(source)
  let root = tree.root_node()
  let array_node = root.child(0).or_error!(Failure("No array node"))

  // Count children using iteration
  let children = []
  for child in array_node.children() {
    if child.is_named() {
      children.push(child.type_())
    }
  }

  // Should have 5 named children (numbers)
  inspect!(children.length(), content="5")

  // Check that all named children are numbers
  let all_numbers = children.iter().all(fn(type_) { type_ == "number" })
  inspect!(all_numbers, content="true")
}

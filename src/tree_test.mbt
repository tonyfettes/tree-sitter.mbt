///|
test "tree basic operations" {
  let json = @tree_sitter_json.language()
  let parser = @tree_sitter.parser(json)
  let source =
    #|{"name": "Test", "value": 123}

  // Create and test basic tree operations
  let tree = parser.parse_string!(source)

  // Test tree.copy() creates a copy
  let tree_copy = tree.copy()

  // Both trees should have the same structure and content
  let root = tree.root_node()
  let copy_root = tree_copy.root_node()
  inspect!(root.type_(), content="document")
  inspect!(copy_root.type_(), content="document")

  // Check child nodes
  let root_child = root.child(0).or_error!(Failure("No child found"))
  let copy_root_child = copy_root.child(0).or_error!(Failure("No child found"))
  inspect!(root_child.type_(), content="object")
  inspect!(copy_root_child.type_(), content="object")

  // Check language
  let tree_lang = tree.language()
  inspect!(tree_lang.name(), content="None")
}

///|
test "tree edit operations" {
  let json = @tree_sitter_json.language()
  let parser = @tree_sitter.parser(json)

  // Create an initial tree
  let source =
    #|{"name": "Original"}
  let original_tree = parser.parse_string!(source)

  // Get original node content
  let root_node = original_tree.root_node()
  let object_node = root_node.child(0).or_error!(Failure("No object node"))
  let original_node_count = object_node.named_child_count()
  inspect!(original_node_count, content="1")

  // Create edited source with additional property
  let edited_source =
    #|{"name": "Original", "new_prop": true}

  // Create an edit operation to update the tree
  let edit = @tree_sitter.InputEdit::new(
    start_byte=19, // Position after closing quote of "Original"
    old_end_byte=20, // Position of closing brace in original
    new_end_byte=36, // Position of closing brace in edited
    start_point=@tree_sitter.Point::new(0, 19),
    old_end_point=@tree_sitter.Point::new(0, 20),
    new_end_point=@tree_sitter.Point::new(0, 36),
  )

  // Apply the edit to the tree
  original_tree.edit(edit)

  // Re-parse with edited source
  let new_tree = parser.parse_string!(edited_source, old_tree=original_tree)

  // Check the new tree structure
  let new_root = new_tree.root_node()
  let new_object = new_root
    .child(0)
    .or_error!(Failure("No object node in new tree"))
  let new_node_count = new_object.named_child_count()
  inspect!(new_node_count, content="2")

  // Get changed ranges between original and new tree
  let changed_ranges = original_tree.get_changed_ranges(new_tree)
  inspect!(changed_ranges.length(), content="1") // Should have one changed range
}

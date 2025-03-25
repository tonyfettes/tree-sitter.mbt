///|
type Tree

///|
/// Create a shallow copy of the syntax tree. This is very fast.
///
/// You need to copy a syntax tree in order to use it on more than one thread at
/// a time, as syntax trees are not thread safe.
pub extern "c" fn Tree::copy(self : Tree) -> Tree = "moonbit_ts_tree_copy"

///|
/// Get the root node of the syntax tree.
pub extern "c" fn Tree::root_node(self : Tree) -> Node = "moonbit_ts_tree_root_node"

///|
extern "c" fn Tree::_root_node_with_offset(self : Tree, offset : UInt) -> Node = "moonbit_ts_tree_root_node_with_offset"

///|
/// Get the root node of the syntax tree, but with its position
/// shifted forward by the given offset.
pub fn Tree::root_node_with_offset(self : Tree, offset : Int) -> Node {
  self._root_node_with_offset(int_to_uint(offset))
}

///|
/// Get the language that was used to parse the syntax tree.
pub extern "c" fn Tree::language(self : Tree) -> Language = "moonbit_ts_tree_language"

///|
extern "c" fn Tree::_included_ranges(self : Tree) -> FixedArray[UInt] = "moonbit_ts_tree_included_ranges"

///|
/// Get the array of included ranges that was used to parse the syntax tree.
fn Tree::included_ranges(self : Tree) -> Array[Range] {
  let flatten_ranges = self._included_ranges()
  Array::makei(flatten_ranges.length() / 6, fn(i) {
    Range::_new(
      Point::_new(flatten_ranges[i * 6], flatten_ranges[i * 6 + 1]),
      Point::_new(flatten_ranges[i * 6 + 2], flatten_ranges[i * 6 + 3]),
      flatten_ranges[i * 6 + 4],
      flatten_ranges[i * 6 + 5],
    )
  })
}

///|
/// Edit the syntax tree to keep it in sync with source code that has been
/// edited.
///
/// You must describe the edit both in terms of byte offsets and in terms of
/// (row, column) coordinates.
pub extern "c" fn Tree::edit(self : Tree, edit : InputEdit) = "moonbit_ts_tree_edit"

///|
extern "c" fn Tree::_get_changed_ranges(
  self : Tree,
  other : Tree
) -> FixedArray[UInt] = "moonbit_ts_tree_get_changed_ranges"

///|
/// Compare an old edited syntax tree to a new syntax tree representing the same
/// document, returning an array of ranges whose syntactic structure has changed.
///
/// For this to work correctly, the old syntax tree must have been edited such
/// that its ranges match up to the new tree. Generally, you'll want to call
/// this function right after calling one of the Parser::parse functions.
/// You need to pass the old tree that was passed to parse, as well as the new
/// tree that was returned from that function.
///
/// The returned ranges indicate areas where the hierarchical structure of syntax
/// nodes (from root to leaf) has changed between the old and new trees. Characters
/// outside these ranges have identical ancestor nodes in both trees.
///
/// Note that the returned ranges may be slightly larger than the exact changed areas,
/// but Tree-sitter attempts to make them as small as possible.
pub fn Tree::get_changed_ranges(self : Tree, other : Tree) -> Array[Range] {
  let flatten_ranges = self._get_changed_ranges(other)
  Array::makei(flatten_ranges.length() / 6, fn(i) {
    Range::_new(
      Point::_new(flatten_ranges[i * 6], flatten_ranges[i * 6 + 1]),
      Point::_new(flatten_ranges[i * 6 + 2], flatten_ranges[i * 6 + 3]),
      flatten_ranges[i * 6 + 4],
      flatten_ranges[i * 6 + 5],
    )
  })
}

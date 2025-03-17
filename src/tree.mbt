///|
/// A syntax tree.
extern type Tree

///|
/// Create a shallow copy of the syntax tree. This is very fast.
///
/// You need to copy a syntax tree in order to use it on more than one thread at
/// a time, as syntax trees are not thread safe.
pub extern "c" fn Tree::copy(self : Tree) -> Tree = "moonbit_ts_tree_copy"

///|
/// Delete the syntax tree, freeing all of the memory that it used.
pub extern "c" fn Tree::delete(self : Tree) = "moonbit_ts_tree_delete"

///|
/// Get the root node of the syntax tree.
pub extern "c" fn Tree::root_node(self : Tree) -> Node = "moonbit_ts_tree_root_node"

///|
extern "c" fn Tree::_root_node_with_offset(self : Tree, offset : UInt) -> Node = "moonbit_ts_tree_root_node_with_offset"

///|
pub fn Tree::root_node_with_offset(self : Tree, offset : Int) -> Node {
  self._root_node_with_offset(int_to_uint(offset))
}

///|
pub extern "c" fn Tree::language(self : Tree) -> Language = "moonbit_ts_tree_language"

///|
extern "c" fn Tree::_included_ranges(self : Tree) -> FixedArray[UInt] = "moonbit_ts_tree_included_ranges"

///|
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
pub extern "c" fn Tree::edit(self : Tree, edit : InputEdit) = "moonbit_ts_tree_edit"

///|
extern "c" fn Tree::get_changed_ranges(
  self : Tree,
  other : Tree
) -> FixedArray[UInt] = "moonbit_ts_tree_get_changed_ranges"

///|
pub fn Tree::changed_ranges(self : Tree, other : Tree) -> Array[Range] {
  let flatten_ranges = self.get_changed_ranges(other)
  Array::makei(flatten_ranges.length() / 6, fn(i) {
    Range::_new(
      Point::_new(flatten_ranges[i * 6], flatten_ranges[i * 6 + 1]),
      Point::_new(flatten_ranges[i * 6 + 2], flatten_ranges[i * 6 + 3]),
      flatten_ranges[i * 6 + 4],
      flatten_ranges[i * 6 + 5],
    )
  })
}

///|
extern type Tree

///|
pub extern "c" fn Tree::copy(self : Tree) -> Tree = "moonbit_ts_tree_copy"

///|
pub extern "c" fn Tree::delete(self : Tree) = "moonbit_ts_tree_delete"

///|
pub extern "c" fn Tree::root_node(self : Tree) -> Node = "moonbit_ts_tree_root_node"

///|
pub extern "c" fn Tree::root_node_with_offset(
  self : Tree,
  offset : UInt
) -> Node = "moonbit_ts_tree_root_node_with_offset"

///|
pub extern "c" fn Tree::language(self : Tree) -> Language = "moonbit_ts_tree_language"

///|
extern "c" fn Tree::_included_ranges(self : Tree) -> FixedArray[UInt] = "moonbit_ts_tree_included_ranges"

///|
fn Tree::included_ranges(self : Tree) -> Array[Range] {
  let flatten_ranges = self._included_ranges()
  Array::makei(flatten_ranges.length() / 6, fn(i) {
    Range::new(
      Point::new(flatten_ranges[i * 6], flatten_ranges[i * 6 + 1]),
      Point::new(flatten_ranges[i * 6 + 2], flatten_ranges[i * 6 + 3]),
      flatten_ranges[i * 6 + 4],
      flatten_ranges[i * 6 + 5],
    )
  })
}

///|
pub extern "c" fn Tree::edit(self : Tree, edit : InputEdit) -> Tree = "moonbit_ts_tree_edit"

///|
extern "c" fn Tree::get_changed_ranges(
  self : Tree,
  other : Tree
) -> FixedArray[UInt] = "moonbit_ts_tree_get_changed_ranges"

///|
pub fn Tree::changed_ranges(self : Tree, other : Tree) -> Array[Range] {
  let flatten_ranges = self.get_changed_ranges(other)
  Array::makei(flatten_ranges.length() / 6, fn(i) {
    Range::new(
      Point::new(flatten_ranges[i * 6], flatten_ranges[i * 6 + 1]),
      Point::new(flatten_ranges[i * 6 + 2], flatten_ranges[i * 6 + 3]),
      flatten_ranges[i * 6 + 4],
      flatten_ranges[i * 6 + 5],
    )
  })
}

///|
type TreeCursor Bytes

///|
pub extern "c" fn TreeCursor::new(node : Node) -> TreeCursor = "moonbit_ts_tree_cursor_new"

///|
pub extern "c" fn TreeCursor::delete(self : TreeCursor) = "moonbit_ts_tree_cursor_delete"

///|
pub extern "c" fn TreeCursor::reset(self : TreeCursor, node : Node) = "moonbit_ts_tree_cursor_reset"

///|
pub extern "c" fn TreeCursor::reset_to(self : TreeCursor, other : TreeCursor) = "moonbit_ts_tree_cursor_reset_to"

///|
pub extern "c" fn TreeCursor::current_node(self : TreeCursor) -> Node = "moonbit_ts_tree_cursor_current_node"

///|
pub extern "c" fn TreeCursor::current_field_name(self : TreeCursor) -> Bytes = "moonbit_ts_tree_cursor_current_field_name"

///|
pub extern "c" fn TreeCursor::current_field_id(self : TreeCursor) -> FieldId = "moonbit_ts_tree_cursor_current_field_id"

///|
pub extern "c" fn TreeCursor::goto_parent(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_parent"

///|
pub extern "c" fn TreeCursor::goto_next_sibling(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_next_sibling"

///|
pub extern "c" fn TreeCursor::goto_previous_sibling(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_previous_sibling"

///|
pub extern "c" fn TreeCursor::goto_first_child(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_first_child"

///|
pub extern "c" fn TreeCursor::goto_last_child(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_last_child"

///|
extern "c" fn TreeCursor::_goto_descendant(
  self : TreeCursor,
  goal_descendant_index : UInt
) -> Unit = "moonbit_ts_tree_cursor_goto_descendant"

///|
pub fn TreeCursor::goto_descendant(
  self : TreeCursor,
  goal_descendant_index : Int
) -> Unit {
  self._goto_descendant(int_to_uint(goal_descendant_index))
}

///|
extern "c" fn TreeCursor::_current_descendant_index(self : TreeCursor) -> UInt = "moonbit_ts_tree_cursor_current_descendant_index"

///|
pub fn TreeCursor::current_descendant_index(self : TreeCursor) -> Int {
  uint_to_int(self._current_descendant_index())
}

///|
extern "c" fn TreeCursor::_current_depth(self : TreeCursor) -> UInt = "moonbit_ts_tree_cursor_current_depth"

///|
pub fn TreeCursor::current_depth(self : TreeCursor) -> Int {
  uint_to_int(self._current_depth())
}

///|
extern "c" fn TreeCursor::_goto_first_child_for_byte(
  self : TreeCursor,
  goal_byte : UInt
) -> Bool = "moonbit_ts_tree_cursor_goto_first_child_for_byte"

pub fn TreeCursor::goto_first_child_for_byte(
  self : TreeCursor,
  goal_byte : Int
) -> Bool {
  self._goto_first_child_for_byte(int_to_uint(goal_byte))
}

///|
pub extern "c" fn TreeCursor::goto_first_child_for_point(
  self : TreeCursor,
  goal_point : Point
) -> Bool = "moonbit_ts_tree_cursor_goto_first_child_for_point"

///|
pub extern "c" fn TreeCursor::copy(self : TreeCursor) -> TreeCursor = "moonbit_ts_tree_cursor_copy"

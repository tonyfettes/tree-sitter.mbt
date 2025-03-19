///|
type TreeCursor Bytes

///|
/// Create a new tree cursor starting from the given node.
///
/// A tree cursor allows you to walk a syntax tree more efficiently than is
/// possible using the `Node` functions. It is a mutable object that is always
/// on a certain syntax node, and can be moved imperatively to different nodes.
///
/// Note that the given node is considered the root of the cursor,
/// and the cursor cannot walk outside this node.
pub extern "c" fn TreeCursor::new(node : Node) -> TreeCursor = "moonbit_ts_tree_cursor_new"

///|
/// Delete a tree cursor, freeing all of the memory that it used.
pub extern "c" fn TreeCursor::delete(self : TreeCursor) = "moonbit_ts_tree_cursor_delete"

///|
/// Re-initialize a tree cursor to start at the original node that the cursor was
/// constructed with.
pub extern "c" fn TreeCursor::reset(self : TreeCursor, node : Node) = "moonbit_ts_tree_cursor_reset"

///|
/// Re-initialize a tree cursor to the same position as another cursor.
///
/// Unlike TreeCursor::reset, this will not lose parent information and
/// allows reusing already created cursors.
pub extern "c" fn TreeCursor::reset_to(self : TreeCursor, other : TreeCursor) = "moonbit_ts_tree_cursor_reset_to"

///|
/// Get the tree cursor's current node.
pub extern "c" fn TreeCursor::current_node(self : TreeCursor) -> Node = "moonbit_ts_tree_cursor_current_node"

///|
extern "c" fn TreeCursor::_current_field_name(
  self : TreeCursor
) -> @c.Pointer[Byte] = "moonbit_ts_tree_cursor_current_field_name"

///|
/// Get the field name of the tree cursor's current node.
///
/// This returns `None` if the current node doesn't have a field.
/// See also `Node::child_by_field_name`.
pub fn TreeCursor::current_field_name(self : TreeCursor) -> String? {
  let name = self._current_field_name()
  if name.is_null() {
    return None
  }
  let buffer = @buffer.new()
  for i = 0; name[i] != 0; i = i + 1 {
    buffer.write_byte(name[i])
  }
  let name = buffer.contents()
  let name = @encoding.decoder(UTF8).decode_lossy(name)
  Some(name)
}

///|
/// Get the field id of the tree cursor's current node.
///
/// This returns zero if the current node doesn't have a field.
/// See also `Node::child_by_field_id`, `Language::field_id_for_name`.
pub extern "c" fn TreeCursor::current_field_id(self : TreeCursor) -> FieldId = "moonbit_ts_tree_cursor_current_field_id"

///|
/// Move the cursor to the parent of its current node.
///
/// This returns `true` if the cursor successfully moved, and returns `false`
/// if there was no parent node (the cursor was already on the root node).
///
/// Note that the node the cursor was constructed with is considered the root
/// of the cursor, and the cursor cannot walk outside this node.
pub extern "c" fn TreeCursor::goto_parent(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_parent"

///|
/// Move the cursor to the next sibling of its current node.
///
/// This returns `true` if the cursor successfully moved, and returns `false`
/// if there was no next sibling node.
///
/// Note that the node the cursor was constructed with is considered the root
/// of the cursor, and the cursor cannot walk outside this node.
pub extern "c" fn TreeCursor::goto_next_sibling(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_next_sibling"

///|
/// Move the cursor to the previous sibling of its current node.
///
/// This returns `true` if the cursor successfully moved, and returns `false` if
/// there was no previous sibling node.
///
/// Note, that this function may be slower than `TreeCursor::goto_next_sibling`
/// due to how node positions are stored. In the worst case, this will need to
/// iterate through all the children up to the previous sibling node to recalculate
/// its position. Also note that the node the cursor was constructed with is
/// considered the root of the cursor, and the cursor cannot walk outside this node.
pub extern "c" fn TreeCursor::goto_previous_sibling(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_previous_sibling"

///|
/// Move the cursor to the first child of its current node.
///
/// This returns `true` if the cursor successfully moved, and returns `false`
/// if there were no children.
pub extern "c" fn TreeCursor::goto_first_child(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_first_child"

///|
/// Move the cursor to the last child of its current node.
///
/// This returns `true` if the cursor successfully moved, and returns `false` if
/// there were no children.
///
/// Note that this function may be slower than TreeCursor::goto_first_child
/// because it needs to iterate through all the children to compute the child's
/// position.
pub extern "c" fn TreeCursor::goto_last_child(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_last_child"

///|
/// Move the cursor to the node that is the nth descendant of
/// the original node that the cursor was constructed with, where
/// zero represents the original node itself.
extern "c" fn TreeCursor::_goto_descendant(
  self : TreeCursor,
  goal_descendant_index : UInt
) -> Unit = "moonbit_ts_tree_cursor_goto_descendant"

///|
/// Move the cursor to the node that is the nth descendant of
/// the original node that the cursor was constructed with, where
/// zero represents the original node itself.
pub fn TreeCursor::goto_descendant(
  self : TreeCursor,
  goal_descendant_index : Int
) -> Unit {
  self._goto_descendant(int_to_uint(goal_descendant_index))
}

///|
/// Get the index of the cursor's current node out of all of the
/// descendants of the original node that the cursor was constructed with.
extern "c" fn TreeCursor::_current_descendant_index(self : TreeCursor) -> UInt = "moonbit_ts_tree_cursor_current_descendant_index"

///|
/// Get the index of the cursor's current node out of all of the
/// descendants of the original node that the cursor was constructed with.
pub fn TreeCursor::current_descendant_index(self : TreeCursor) -> Int {
  uint_to_int(self._current_descendant_index())
}

///|
/// Get the depth of the cursor's current node relative to the original
/// node that the cursor was constructed with.
extern "c" fn TreeCursor::_current_depth(self : TreeCursor) -> UInt = "moonbit_ts_tree_cursor_current_depth"

///|
/// Get the depth of the cursor's current node relative to the original
/// node that the cursor was constructed with.
pub fn TreeCursor::current_depth(self : TreeCursor) -> Int {
  uint_to_int(self._current_depth())
}

///|
/// Move the cursor to the first child of its current node that contains or starts after
/// the given byte offset.
///
/// This returns the index of the child node if one was found, and returns -1
/// if no such child was found.
extern "c" fn TreeCursor::_goto_first_child_for_byte(
  self : TreeCursor,
  goal_byte : UInt
) -> Bool = "moonbit_ts_tree_cursor_goto_first_child_for_byte"

///|
/// Move the cursor to the first child of its current node that contains or starts after
/// the given byte offset.
///
/// This returns the index of the child node if one was found, and returns -1
/// if no such child was found.
pub fn TreeCursor::goto_first_child_for_byte(
  self : TreeCursor,
  goal_byte : Int
) -> Bool {
  self._goto_first_child_for_byte(int_to_uint(goal_byte))
}

///|
/// Move the cursor to the first child of its current node that contains or starts after
/// the given point.
///
/// This returns the index of the child node if one was found, and returns -1
/// if no such child was found.
pub extern "c" fn TreeCursor::goto_first_child_for_point(
  self : TreeCursor,
  goal_point : Point
) -> Bool = "moonbit_ts_tree_cursor_goto_first_child_for_point"

///|
pub extern "c" fn TreeCursor::copy(self : TreeCursor) -> TreeCursor = "moonbit_ts_tree_cursor_copy"

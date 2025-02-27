///|
type TreeCursor Bytes

///|
pub extern "c" fn TreeCursor::new(node : Node) -> TreeCursor = "moonbit_ts_tree_cursor_new"

///|
pub extern "c" fn TreeCursor::goto_first_child(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_first_child"

///|
pub extern "c" fn TreeCursor::goto_next_sibling(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_next_sibling"

///|
pub extern "c" fn TreeCursor::goto_parent(self : TreeCursor) -> Bool = "moonbit_ts_tree_cursor_goto_parent"

///|
pub extern "c" fn TreeCursor::current_node(self : TreeCursor) -> Node = "moonbit_ts_tree_cursor_current_node"

///|
pub extern "c" fn TreeCursor::current_field_name(self : TreeCursor) -> Bytes = "moonbit_ts_tree_cursor_current_field_name"

///|
pub extern "c" fn TreeCursor::current_field_id(self : TreeCursor) -> FieldId = "moonbit_ts_tree_cursor_current_field_id"

///|
pub extern "c" fn TreeCursor::delete(self : TreeCursor) = "moonbit_ts_tree_cursor_delete"

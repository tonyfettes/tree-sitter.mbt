///|
type Node Bytes

///|
pub extern "c" fn Node::named_child(self : Node, child_index : UInt) -> Node = "moonbit_ts_node_named_child"

///|
pub extern "c" fn Node::child_count(self : Node) -> UInt = "moonbit_ts_node_child_count"

///|
pub extern "c" fn Node::named_child_count(self : Node) -> UInt = "moonbit_ts_node_named_child_count"

///|
extern "c" fn Node::_string(self : Node) -> Bytes = "moonbit_ts_node_string"

///|
pub fn Node::string(self : Node) -> String {
  @encoding.decode_strict(UTF8, self._string()).to_string?().unwrap()
}

///|
extern "c" fn Node::_type(self : Node) -> Bytes = "moonbit_ts_node_type"

///|
pub fn Node::type_(self : Node) -> String {
  @encoding.decode_strict(UTF8, self._type()).to_string?().unwrap()
}

///|
extern "c" fn Node::start_byte(self : Node) -> UInt = "moonbit_ts_node_start_byte"

///|
extern "c" fn Node::end_byte(self : Node) -> UInt = "moonbit_ts_node_end_byte"

///|
extern "c" fn Node::start_point(self : Node) -> Point = "moonbit_ts_node_start_point"

///|
extern "c" fn Node::end_point(self : Node) -> Point = "moonbit_ts_node_end_point"

///|
extern "c" fn Node::_next_sibling(self : Node) -> Node = "moonbit_ts_node_next_sibling"

///|
extern "c" fn Node::_prev_sibling(self : Node) -> Node = "moonbit_ts_node_prev_sibling"

///|
extern "c" fn Node::_child(self : Node, index : UInt) -> Node = "moonbit_ts_node_child"

///|
pub fn Node::child(self : Node, index : UInt) -> Node? {
  let child = self._child(index)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
extern "c" fn Node::_next_named_sibling(self : Node) -> Node = "moonbit_ts_node_next_named_sibling"

///|
extern "c" fn Node::_prev_named_sibling(self : Node) -> Node = "moonbit_ts_node_prev_named_sibling"

///|
extern "c" fn Node::is_null(self : Node) -> Bool = "moonbit_ts_node_is_null"

///|
extern "c" fn Node::is_named(self : Node) -> Bool = "moonbit_ts_node_is_named"

///|
pub fn Node::next_sibling(self : Node) -> Node? {
  let next_sibling = self._next_sibling()
  if next_sibling.is_null() {
    None
  } else {
    Some(next_sibling)
  }
}

///|
pub fn Node::prev_sibling(self : Node) -> Node? {
  let prev_sibling = self._prev_sibling()
  if prev_sibling.is_null() {
    None
  } else {
    Some(prev_sibling)
  }
}

///|
extern "c" fn Node::parent(self : Node) -> Node = "moonbit_ts_node_parent"

///|
extern "c" fn Node::_child_by_field_name(self : Node, name : Bytes) -> Node = "moonbit_ts_node_child_by_field_name"

///|
pub fn Node::child_by_field_name(self : Node, name : String) -> Node? {
  let name_bytes = @buffer.new()
  name_bytes.write_bytes(@encoding.encode(UTF8, name))
  name_bytes.write_byte(0)
  let child = self._child_by_field_name(name_bytes.contents())
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
extern "c" fn Node::_child_by_field_id(self : Node, id : FieldId) -> Node = "moonbit_ts_node_child_by_field_id"

///|
pub fn Node::child_by_field_id(self : Node, id : FieldId) -> Node? {
  let child = self._child_by_field_id(id)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
pub extern "c" fn Node::edit(self : Node, edit : InputEdit) -> Unit = "moonbit_ts_node_edit"

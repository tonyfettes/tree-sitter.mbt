///|
type Node Bytes

///|
pub extern "c" fn Node::named_child(self : Node, child_index : Int) -> Node = "moonbit_ts_node_named_child"

///|
pub extern "c" fn Node::child_count(self : Node) -> Int = "moonbit_ts_node_child_count"

///|
pub extern "c" fn Node::named_child_count(self : Node) -> Int = "moonbit_ts_node_named_child_count"

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

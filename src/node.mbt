///|
type Node Bytes

///|
extern "c" fn Node::_type(self : Node) -> Bytes = "moonbit_ts_node_type"

///|
pub fn Node::type_(self : Node) -> String {
  @encoding.decoder(UTF8).decode_lossy(self._type())
}

///|
pub extern "c" fn Node::symbol(self : Node) -> Symbol = "moonbit_ts_node_symbol"

///|
pub extern "c" fn Node::language(self : Node) -> Language = "moonbit_ts_node_language"

///|
extern "c" fn Node::_grammar_type(self : Node) -> Bytes = "moonbit_ts_node_grammar_type"

///|
pub fn Node::grammar_type(self : Node) -> String {
  @encoding.decoder(UTF8).decode_lossy(self._grammar_type())
}

///|
pub extern "c" fn Node::grammar_symbol(self : Node) -> Symbol = "moonbit_ts_node_grammar_symbol"

///|
pub extern "c" fn Node::start_byte(self : Node) -> UInt = "moonbit_ts_node_start_byte"

///|
pub extern "c" fn Node::start_point(self : Node) -> Point = "moonbit_ts_node_start_point"

///|
pub extern "c" fn Node::end_byte(self : Node) -> UInt = "moonbit_ts_node_end_byte"

///|
extern "c" fn Node::_string(self : Node) -> Bytes = "moonbit_ts_node_string"

///|
pub fn Node::string(self : Node) -> String {
  @encoding.decoder(UTF8).decode_lossy(self._string())
}

///|
pub impl Show for Node with output(self : Node, logger : &Logger) -> Unit {
  logger.write_string(self.string())
}

///|
pub extern "c" fn Node::end_point(self : Node) -> Point = "moonbit_ts_node_end_point"

///|
extern "c" fn Node::is_null(self : Node) -> Bool = "moonbit_ts_node_is_null"

///|
pub extern "c" fn Node::is_named(self : Node) -> Bool = "moonbit_ts_node_is_named"

///|
pub extern "c" fn Node::is_missing(self : Node) -> Bool = "moonbit_ts_node_is_missing"

///|
pub extern "c" fn Node::is_extra(self : Node) -> Bool = "moonbit_ts_node_is_extra"

///|
pub extern "c" fn Node::has_changes(self : Node) -> Bool = "moonbit_ts_node_has_changes"

///|
pub extern "c" fn Node::has_error(self : Node) -> Bool = "moonbit_ts_node_has_error"

///|
pub extern "c" fn Node::is_error(self : Node) -> Bool = "moonbit_ts_node_is_error"

///|
pub extern "c" fn Node::parse_state(self : Node) -> StateId = "moonbit_ts_node_parse_state"

///|
pub extern "c" fn Node::next_parse_state(self : Node) -> StateId = "moonbit_ts_node_next_parse_state"

///|
extern "c" fn Node::_parent(self : Node) -> Node = "moonbit_ts_node_parent"

///|
pub fn Node::parent(self : Node) -> Node? {
  let parent = self._parent()
  if parent.is_null() {
    None
  } else {
    Some(parent)
  }
}

///|
extern "c" fn Node::_child_with_descendant(
  self : Node,
  descendant : Node
) -> Node = "moonbit_ts_node_child_with_descendant"

///|
pub fn Node::child_with_descendant(self : Node, descendant : Node) -> Node? {
  let child = self._child_with_descendant(descendant)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

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
pub fn Node::children(self : Node) -> Iter[Node] {
  Iter::new(fn(yield_) {
    for i in 0U..<self.child_count() {
      match yield_(self._child(i)) {
        IterEnd => return IterEnd
        IterContinue => continue
      }
    }
    IterContinue
  })
}

///|
extern "c" fn Node::_field_name_for_child(
  self : Node,
  child_index : UInt
) -> Bytes = "moonbit_ts_node_field_name_for_child"

///|
pub fn Node::field_name_for_child(self : Node, child_index : UInt) -> String {
  @encoding.decoder(UTF8).decode_lossy(self._field_name_for_child(child_index))
}

///|
extern "c" fn Node::_field_name_for_named_child(
  self : Node,
  child_index : UInt
) -> Bytes = "moonbit_ts_node_field_name_for_named_child"

///|
pub fn Node::field_name_for_named_child(
  self : Node,
  child_index : UInt
) -> String {
  @encoding.decoder(UTF8).decode_lossy(
    self._field_name_for_named_child(child_index),
  )
}

///|
pub extern "c" fn Node::child_count(self : Node) -> UInt = "moonbit_ts_node_child_count"

///|
extern "c" fn Node::_named_child(self : Node, child_index : UInt) -> Node = "moonbit_ts_node_named_child"

///|
pub fn Node::named_child(self : Node, child_index : UInt) -> Node? {
  let child = self._named_child(child_index)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
pub extern "c" fn Node::named_child_count(self : Node) -> UInt = "moonbit_ts_node_named_child_count"

///|
extern "c" fn Node::_child_by_field_name(self : Node, name : Bytes) -> Node = "moonbit_ts_node_child_by_field_name"

///|
pub fn Node::child_by_field_name(self : Node, name : String) -> Node? {
  let name_bytes = @encoding.encode(UTF8, name)
  let child = self._child_by_field_name(name_bytes)
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
extern "c" fn Node::_next_sibling(self : Node) -> Node = "moonbit_ts_node_next_sibling"

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
extern "c" fn Node::_prev_sibling(self : Node) -> Node = "moonbit_ts_node_prev_sibling"

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
extern "c" fn Node::_next_named_sibling(self : Node) -> Node = "moonbit_ts_node_next_named_sibling"

///|
pub fn Node::next_named_sibling(self : Node) -> Node? {
  let next_named_sibling = self._next_named_sibling()
  if next_named_sibling.is_null() {
    None
  } else {
    Some(next_named_sibling)
  }
}

///|
extern "c" fn Node::_prev_named_sibling(self : Node) -> Node = "moonbit_ts_node_prev_named_sibling"

///|
pub fn Node::prev_named_sibling(self : Node) -> Node? {
  let prev_named_sibling = self._prev_named_sibling()
  if prev_named_sibling.is_null() {
    None
  } else {
    Some(prev_named_sibling)
  }
}

///|
extern "c" fn Node::_first_child_for_byte(self : Node, byte : UInt) -> Node = "moonbit_ts_node_first_child_for_byte"

///|
pub fn Node::first_child_for_byte(self : Node, byte : UInt) -> Node? {
  let child = self._first_child_for_byte(byte)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
extern "c" fn Node::_first_named_child_for_byte(
  self : Node,
  byte : UInt
) -> Node = "moonbit_ts_node_first_named_child_for_byte"

///|
pub fn Node::first_named_child_for_byte(self : Node, byte : UInt) -> Node? {
  let child = self._first_child_for_byte(byte)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
pub extern "c" fn Node::descendant_count(self : Node) -> UInt = "moonbit_ts_node_descendant_count"

///|
extern "c" fn Node::_descendant_for_byte_range(
  self : Node,
  start_byte : UInt,
  end_byte : UInt
) -> Node = "moonbit_ts_node_descendant_for_byte_range"

///|
pub fn Node::descendant_for_byte_range(
  self : Node,
  start_byte : UInt,
  end_byte : UInt
) -> Node? {
  let descendant = self._descendant_for_byte_range(start_byte, end_byte)
  if descendant.is_null() {
    None
  } else {
    Some(descendant)
  }
}

///|
extern "c" fn Node::_descendant_for_point_range(
  self : Node,
  start_point : Point,
  end_point : Point
) -> Node = "moonbit_ts_node_descendant_for_point_range"

///|
pub fn Node::descendant_for_point_range(
  self : Node,
  start_point : Point,
  end_point : Point
) -> Node? {
  let descendant = self._descendant_for_point_range(start_point, end_point)
  if descendant.is_null() {
    None
  } else {
    Some(descendant)
  }
}

///|
pub extern "c" fn Node::edit(self : Node, edit : InputEdit) -> Unit = "moonbit_ts_node_edit"

///|
pub extern "c" fn Node::eq(self : Node, other : Node) -> Bool = "moonbit_ts_node_eq"

///|
impl Eq for Node with op_equal(self, other) -> Bool {
  self.eq(other)
}

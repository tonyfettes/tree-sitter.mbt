///|
type Node

///|
#borrow(self)
extern "c" fn Node::_type(self : Node) -> @c.Pointer[Byte] = "moonbit_ts_node_type"

///|
/// Get the node's type as a string.
pub fn Node::type_(self : Node) -> String {
  return decode_c_string(self._type()).unwrap()
}

///|
/// Get the node's type as a numerical id.
#borrow(self)
pub extern "c" fn Node::symbol(self : Node) -> Symbol = "moonbit_ts_node_symbol"

///|
/// Get the node's language.
#borrow(self)
pub extern "c" fn Node::language(self : Node) -> Language = "moonbit_ts_node_language"

///|
#borrow(self)
extern "c" fn Node::_grammar_type(self : Node) -> @c.Pointer[Byte] = "moonbit_ts_node_grammar_type"

///|
/// Get the node's type as it appears in the grammar ignoring aliases as a string.
pub fn Node::grammar_type(self : Node) -> String {
  return decode_c_string(self._grammar_type()).unwrap()
}

///|
/// Get the node's type as a numerical id as it appears in the grammar ignoring
/// aliases. This should be used in `Language::next_state` instead of
/// `Node::symbol`.
#borrow(self)
pub extern "c" fn Node::grammar_symbol(self : Node) -> Symbol = "moonbit_ts_node_grammar_symbol"

///|
/// Get the node's start byte.
#borrow(self)
pub extern "c" fn Node::start_byte(self : Node) -> Int = "moonbit_ts_node_start_byte"

///|
/// Get the node's start position in terms of rows and columns.
#borrow(self)
pub extern "c" fn Node::start_point(self : Node) -> Point = "moonbit_ts_node_start_point"

///|
/// Get the node's end byte.
#borrow(self)
pub extern "c" fn Node::end_byte(self : Node) -> Int = "moonbit_ts_node_end_byte"

///|
#borrow(self)
extern "c" fn Node::_string(self : Node) -> @c.Pointer[Byte] = "moonbit_ts_node_string"

///|
/// Get an S-expression representing the node as a string.
pub fn Node::string(self : Node) -> String {
  return decode_c_string(self._string()).unwrap()
}

///|
pub impl Show for Node with output(self : Node, logger : &@builtin.Logger) -> Unit {
  logger.write_string(self.string())
}

///|
/// Get the node's end position in terms of rows and columns.
#borrow(self)
pub extern "c" fn Node::end_point(self : Node) -> Point = "moonbit_ts_node_end_point"

///|
/// Check if the node is null. Functions like `Node::child` and
/// `Node::next_sibling` will return a null node to indicate that no such node
/// was found.
#borrow(self)
extern "c" fn Node::is_null(self : Node) -> Bool = "moonbit_ts_node_is_null"

///|
/// Check if the node is *named*. Named nodes correspond to named rules in the
/// grammar, whereas *anonymous* nodes correspond to string literals in the
/// grammar.
#borrow(self)
pub extern "c" fn Node::is_named(self : Node) -> Bool = "moonbit_ts_node_is_named"

///|
/// Check if the node is *missing*. Missing nodes are inserted by the parser in
/// order to recover from certain kinds of syntax errors.
#borrow(self)
pub extern "c" fn Node::is_missing(self : Node) -> Bool = "moonbit_ts_node_is_missing"

///|
/// Check if the node is *extra*. Extra nodes represent things like comments,
/// which are not required the grammar, but can appear anywhere.
#borrow(self)
pub extern "c" fn Node::is_extra(self : Node) -> Bool = "moonbit_ts_node_is_extra"

///|
/// Check if a syntax node has been edited.
#borrow(self)
pub extern "c" fn Node::has_changes(self : Node) -> Bool = "moonbit_ts_node_has_changes"

///|
/// Check if the node is a syntax error or contains any syntax errors.
#borrow(self)
pub extern "c" fn Node::has_error(self : Node) -> Bool = "moonbit_ts_node_has_error"

///|
/// Check if the node is a syntax error.
#borrow(self)
pub extern "c" fn Node::is_error(self : Node) -> Bool = "moonbit_ts_node_is_error"

///|
/// Get this node's parse state.
#borrow(self)
pub extern "c" fn Node::parse_state(self : Node) -> StateId = "moonbit_ts_node_parse_state"

///|
/// Get the parse state after this node.
#borrow(self)
pub extern "c" fn Node::next_parse_state(self : Node) -> StateId = "moonbit_ts_node_next_parse_state"

///|
/// Get the node's immediate parent.
#borrow(self)
extern "c" fn Node::_parent(self : Node) -> Node = "moonbit_ts_node_parent"

///|
/// Get the node's immediate parent.
/// Prefer `Node::child_with_descendant` for iterating over the node's ancestors.
pub fn Node::parent(self : Node) -> Node? {
  let parent = self._parent()
  if parent.is_null() {
    None
  } else {
    Some(parent)
  }
}

///|
/// Get the node that contains `descendant`.
///
/// Note that this can return `descendant` itself.
#borrow(self, descendant)
extern "c" fn Node::_child_with_descendant(
  self : Node,
  descendant : Node
) -> Node = "moonbit_ts_node_child_with_descendant"

///|
/// Get the node that contains `descendant`.
///
/// Note that this can return `descendant` itself.
pub fn Node::child_with_descendant(self : Node, descendant : Node) -> Node? {
  let child = self._child_with_descendant(descendant)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
#borrow(self)
extern "c" fn Node::_child(self : Node, index : UInt) -> Node = "moonbit_ts_node_child"

///|
fn int_to_uint(value : Int) -> UInt {
  guard value >= 0
  value.reinterpret_as_uint()
}

///|
fn uint_to_int(value : UInt) -> Int {
  guard value <= @int.max_value.reinterpret_as_uint()
  value.reinterpret_as_int()
}

///|
/// Get the node's child at the given index, where zero represents the first
/// child.
pub fn Node::child(self : Node, index : Int) -> Node? {
  let index = int_to_uint(index)
  let child = self._child(index)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
/// Get all children of the node.
pub fn Node::children(self : Node) -> Iter[Node] {
  Iter::new(fn(yield_) {
    for i in 0U..<self._child_count() {
      match yield_(self._child(i)) {
        IterEnd => return IterEnd
        IterContinue => continue
      }
    }
    IterContinue
  })
}

///|
#borrow(self)
extern "c" fn Node::_field_name_for_child(
  self : Node,
  child_index : UInt
) -> @c.Pointer[Byte] = "moonbit_ts_node_field_name_for_child"

///|
/// Get the field name for node's child at the given index, where zero represents
/// the first child. Returns `None`, if no field is found.
pub fn Node::field_name_for_child(self : Node, child_index : Int) -> String? {
  let child_index = int_to_uint(child_index)
  let field_name = self._field_name_for_child(child_index)
  if field_name.is_null() {
    return None
  }
  let buffer = @buffer.new()
  for i = 0; field_name[i] != 0; i = i + 1 {
    @buffer.write_byte(buffer, field_name[i])
  }
  let field_name = buffer.contents()
  Some(@encoding.decoder(UTF8).decode_lossy(field_name))
}

///|
#borrow(self)
extern "c" fn Node::_field_name_for_named_child(
  self : Node,
  child_index : UInt
) -> @c.Pointer[Byte] = "moonbit_ts_node_field_name_for_named_child"

///|
/// Get the field name for node's named child at the given index, where zero
/// represents the first named child. Returns `None`, if no field is found.
pub fn Node::field_name_for_named_child(
  self : Node,
  child_index : Int
) -> String? {
  let child_index = int_to_uint(child_index)
  let field_name = self._field_name_for_named_child(child_index)
  if field_name.is_null() {
    return None
  }
  let buffer = @buffer.new()
  for i = 0; field_name[i] != 0; i = i + 1 {
    @buffer.write_byte(buffer, field_name[i])
  }
  let field_name = buffer.contents()
  Some(@encoding.decoder(UTF8).decode_lossy(field_name))
}

///|
#borrow(self)
extern "c" fn Node::_child_count(self : Node) -> UInt = "moonbit_ts_node_child_count"

///|
/// Get the node's number of children.
pub fn Node::child_count(self : Node) -> Int {
  uint_to_int(self._child_count())
}

///|
#borrow(self)
extern "c" fn Node::_named_child(self : Node, child_index : UInt) -> Node = "moonbit_ts_node_named_child"

///|
/// Get the node's *named* child at the given index.
///
/// See also `Node::is_named`.
pub fn Node::named_child(self : Node, child_index : Int) -> Node? {
  let child_index = int_to_uint(child_index)
  let child = self._named_child(child_index)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
#borrow(self)
extern "c" fn Node::_named_child_count(self : Node) -> UInt = "moonbit_ts_node_named_child_count"

///|
/// Get the node's number of *named* children.
///
/// See also `Node::is_named`.
pub fn Node::named_child_count(self : Node) -> Int {
  uint_to_int(self._named_child_count())
}

///|
/// Get all named children of the node.
pub fn Node::named_children(self : Node) -> Iter[Node] {
  Iter::new(fn(yield_) {
    for i in 0U..<self._named_child_count() {
      match yield_(self._named_child(i)) {
        IterEnd => return IterEnd
        IterContinue => continue
      }
    }
    IterContinue
  })
}

///|
/// Get the node's child with the given field name.
#borrow(self, name)
extern "c" fn Node::_child_by_field_name(self : Node, name : Bytes) -> Node = "moonbit_ts_node_child_by_field_name"

///|
/// Get the node's child with the given field name.
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
#borrow(self)
extern "c" fn Node::_child_by_field_id(self : Node, id : FieldId) -> Node = "moonbit_ts_node_child_by_field_id"

///|
/// Get the node's child with the given numerical field id.
///
/// You can convert a field name to an id using the
/// `Language::field_id_for_name` function.
pub fn Node::child_by_field_id(self : Node, id : FieldId) -> Node? {
  let child = self._child_by_field_id(id)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
#borrow(self)
extern "c" fn Node::_next_sibling(self : Node) -> Node = "moonbit_ts_node_next_sibling"

///|
/// Get the node's next sibling.
pub fn Node::next_sibling(self : Node) -> Node? {
  let next_sibling = self._next_sibling()
  if next_sibling.is_null() {
    None
  } else {
    Some(next_sibling)
  }
}

///|
#borrow(self)
extern "c" fn Node::_prev_sibling(self : Node) -> Node = "moonbit_ts_node_prev_sibling"

///|
/// Get the node's previous sibling.
pub fn Node::prev_sibling(self : Node) -> Node? {
  let prev_sibling = self._prev_sibling()
  if prev_sibling.is_null() {
    None
  } else {
    Some(prev_sibling)
  }
}

///|
#borrow(self)
extern "c" fn Node::_next_named_sibling(self : Node) -> Node = "moonbit_ts_node_next_named_sibling"

///|
/// Get the node's next *named* sibling.
pub fn Node::next_named_sibling(self : Node) -> Node? {
  let next_named_sibling = self._next_named_sibling()
  if next_named_sibling.is_null() {
    None
  } else {
    Some(next_named_sibling)
  }
}

///|
#borrow(self)
extern "c" fn Node::_prev_named_sibling(self : Node) -> Node = "moonbit_ts_node_prev_named_sibling"

///|
/// Get the node's previous *named* sibling.
pub fn Node::prev_named_sibling(self : Node) -> Node? {
  let prev_named_sibling = self._prev_named_sibling()
  if prev_named_sibling.is_null() {
    None
  } else {
    Some(prev_named_sibling)
  }
}

///|
#borrow(self)
extern "c" fn Node::_first_child_for_byte(self : Node, byte : UInt) -> Node = "moonbit_ts_node_first_child_for_byte"

///|
/// Get the node's first child that contains or starts after the given byte offset.
pub fn Node::first_child_for_byte(self : Node, byte : Int) -> Node? {
  let byte = int_to_uint(byte)
  let child = self._first_child_for_byte(byte)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
#borrow(self)
extern "c" fn Node::_first_named_child_for_byte(
  self : Node,
  byte : UInt
) -> Node = "moonbit_ts_node_first_named_child_for_byte"

///|
/// Get the node's first named child that contains or starts after the given byte offset.
pub fn Node::first_named_child_for_byte(self : Node, byte : Int) -> Node? {
  let byte = int_to_uint(byte)
  let child = self._first_child_for_byte(byte)
  if child.is_null() {
    None
  } else {
    Some(child)
  }
}

///|
/// Get the node's number of descendants, including one for the node itself.
#borrow(self)
pub extern "c" fn Node::descendant_count(self : Node) -> Int = "moonbit_ts_node_descendant_count"

///|
extern "c" fn Node::_descendant_for_byte_range(
  self : Node,
  start_byte : UInt,
  end_byte : UInt
) -> Node = "moonbit_ts_node_descendant_for_byte_range"

///|
/// Get the smallest node within this node that spans the given range of bytes.
pub fn Node::descendant_for_byte_range(
  self : Node,
  start_byte : Int,
  end_byte : Int
) -> Node? {
  let start_byte = int_to_uint(start_byte)
  let end_byte = int_to_uint(end_byte)
  let descendant = self._descendant_for_byte_range(start_byte, end_byte)
  if descendant.is_null() {
    None
  } else {
    Some(descendant)
  }
}

///|
#borrow(self, start_point, end_point)
extern "c" fn Node::_descendant_for_point_range(
  self : Node,
  start_point : Point,
  end_point : Point
) -> Node = "moonbit_ts_node_descendant_for_point_range"

///|
/// Get the smallest node within this node that spans the given range of
/// (row, column) positions.
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
/// Edit the node to keep it in-sync with source code that has been edited.
///
/// This function is only rarely needed. When you edit a syntax tree with the
/// `Tree::edit` function, all of the nodes that you retrieve from the tree
/// afterward will already reflect the edit. You only need to use `Node::edit`
/// when you have a `Node` instance that you want to keep and continue to use
/// after an edit.
#borrow(self, edit)
pub extern "c" fn Node::edit(self : Node, edit : InputEdit) -> Unit = "moonbit_ts_node_edit"

///|
/// Check if two nodes are identical.
#borrow(self, other)
pub extern "c" fn Node::eq(self : Node, other : Node) -> Bool = "moonbit_ts_node_eq"

///|
impl Eq for Node with op_equal(self, other) -> Bool {
  self.eq(other)
}

///|
extern type Language

pub extern "c" fn json() -> Language = "tree_sitter_json"

///|
extern type Parser

///|
pub extern "c" fn Parser::new() -> Parser = "moonbit_ts_parser_new"

///|
pub extern "c" fn Parser::delete(self : Parser) = "moonbit_ts_parser_delete"

///|
pub extern "c" fn Parser::set_language(
  self : Parser,
  language : Language
) -> Unit = "moonbit_ts_parser_set_language"

///|
pub fn Parser::parse_string(
  self : Parser,
  old_tree : Tree?,
  string : String
) -> Tree {
  self._parse_bytes(Nullable::of(old_tree), @encoding.encode(UTF8, string))
}

///|
extern "c" fn Parser::_parse_bytes(
  self : Parser,
  old_tree : Nullable[Tree],
  string : Bytes
) -> Tree = "moonbit_ts_parser_parse_string"

///|
priv extern type Nullable[_]

///|
fn Nullable::some[T](value : T) -> Nullable[T] = "%identity"

///|
fn Nullable::of[T](option : T?) -> Nullable[T] {
  match option {
    Some(value) => Nullable::some(value)
    None => Nullable::none()
  }
}

///|
fn identity[T, U](value : T) -> U = "%identity"

///|
fn Nullable::none[T]() -> Nullable[T] {
  identity(0)
}

///|
extern type Tree

///|
pub extern "c" fn Tree::root_node(self : Tree) -> Node = "moonbit_ts_tree_root_node"

///|
pub extern "c" fn Tree::delete(self : Tree) = "moonbit_ts_tree_delete"

///|
struct Node {
  tree: Tree
}

///|
pub extern "c" fn Node::named_child(self : Node, child_index : Int) -> Node = "moonbit_ts_node_named_child"

///|
extern "c" fn Node::_type(self : Node) -> Bytes = "moonbit_ts_node_type"

///|
pub fn Node::type_(self : Node) -> String {
  @encoding.decode_strict(UTF8, self._type()).to_string?().unwrap()
}

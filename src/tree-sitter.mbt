///|
extern type Language

///|
extern "c" fn Language::_load(pathname : Bytes, symbol : Bytes) -> Language = "moonbit_ts_language_load"

///|
pub fn Language::load(path : String, name : String) -> Language {
  let pathname = @buffer.new()
  pathname.write_bytes(@encoding.encode(UTF8, path))
  pathname.write_byte(0)
  let symbol = @buffer.new()
  symbol.write_bytes(b"tree_sitter_")
  symbol.write_bytes(@encoding.encode(UTF8, name))
  symbol.write_byte(0)
  Language::_load(pathname.contents(), symbol.contents())
}

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
type Node Bytes

///|
pub extern "c" fn Node::named_child(self : Node, child_index : Int) -> Node = "moonbit_ts_node_named_child"

///|
pub extern "c" fn Node::child_count(self : Node) -> Int = "moonbit_ts_node_child_count"

///|
pub extern "c" fn Node::named_child_count(self : Node) -> Int = "moonbit_ts_node_named_child_count"

///|
extern "c" fn Node::_type(self : Node) -> Bytes = "moonbit_ts_node_type"

///|
pub fn Node::type_(self : Node) -> String {
  @encoding.decode_strict(UTF8, self._type()).to_string?().unwrap()
}

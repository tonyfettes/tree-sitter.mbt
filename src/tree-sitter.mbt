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
extern "c" fn Parser::_parse(
  self : Parser,
  old_tree : Nullable[Tree],
  input : Input_
) -> Tree = "moonbit_ts_parser_parse"

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
fn Nullable::cast[T, U](self : Nullable[T]) -> Nullable[U] = "%identity"

///|
extern "c" fn Nullable::null() -> Nullable[Unit] = "moonbit_c_null"

///|
fn Nullable::none[T]() -> Nullable[T] {
  Nullable::null().cast()
}

///|
fn Nullable::unwrap[T](self : Nullable[T]) -> T = "%identity"

///|
extern type Tree

///|
pub extern "c" fn Tree::root_node(self : Tree) -> Node = "moonbit_ts_tree_root_node"

///|
pub extern "c" fn Tree::delete(self : Tree) = "moonbit_ts_tree_delete"

///|
pub(open) trait DecodeFunction {
  input_encoding(Self) -> InputEncoding
  decode(Bytes, Int) -> Int
}

///|
impl DecodeFunction with input_encoding(self) -> InputEncoding {
  ignore(self)
  Custom
}

///|
pub(all) enum InputEncoding {
  UTF8
  UTF16LE
  UTF16BE
  Custom
}

///|
impl DecodeFunction for InputEncoding with input_encoding(self) -> InputEncoding {
  self
}

///|
impl DecodeFunction for InputEncoding with decode(bytes, byte_index) -> Int {
  ignore(bytes)
  ignore(byte_index)
  -1
}

///|
fn InputEncoding::to_int(self : InputEncoding) -> Int {
  match self {
    UTF8 => 0
    UTF16LE => 1
    UTF16BE => 2
    Custom => 3
  }
}

///|
struct Point {
  row : Int
  column : Int
}

///|
trait Input {
  read(Self, Int, Point) -> Bytes
}

///|
priv extern type Input_

///|
extern "c" fn Input_::new_(
  payload : Nullable[Unit],
  read : FuncRef[(Nullable[Unit], Int, Point) -> Bytes],
  encoding : Int,
  decode : Nullable[FuncRef[(Bytes, Int) -> Int]]
) -> Input_ = "moonbit_ts_input_new"

///|
fn Input_::new[T : Input, Encoding : DecodeFunction](
  input : T,
  encoding : Encoding
) -> Input_ {
  let input_encoding = encoding.input_encoding()
  Input_::new_(
    Nullable::some(input).cast(),
    fn(payload, byte_index, position) {
      T::read(payload.cast().unwrap(), byte_index, position)
    },
    input_encoding.to_int(),
    match input_encoding {
      Custom => Nullable::some(encoding).cast()
      _ => Nullable::none()
    },
  )
}

///|
pub fn Parser::parse[Input : Input, Encoding : DecodeFunction](
  self : Parser,
  input : Input,
  encoding : Encoding
) -> Tree {
  let input_ = Input_::new(input, encoding)
  self._parse(Nullable::none(), input_)
}

fn string_to_ntbs(string : String) -> Bytes {
  let buf = @buffer.new()
  buf.write_bytes(@encoding.encode(UTF8, string))
  buf.write_byte(0)
  buf.contents()
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
  row : UInt
  column : UInt
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

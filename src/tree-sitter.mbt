fn string_to_ntbs(string : String) -> Bytes {
  let buf = @buffer.new()
  buf.write_bytes(@encoding.encode(UTF8, string))
  buf.write_byte(0)
  buf.contents()
}

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

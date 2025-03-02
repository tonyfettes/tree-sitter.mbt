///|
struct Input[DecodeFunction] {
  read : (UInt, Point) -> Bytes
  decode : DecodeFunction
}

///|
pub fn Input::new[DecodeFunction](
  read : (UInt, Point) -> Bytes,
  decode : DecodeFunction
) -> Input[DecodeFunction] {
  { read, decode }
}

///|
type InputEdit FixedArray[UInt]

///|
pub fn InputEdit::new(
  start_byte : UInt,
  old_end_byte : UInt,
  new_end_byte : UInt,
  start_point : Point,
  old_end_point : Point,
  new_end_point : Point
) -> InputEdit {
  [
    start_byte,
    old_end_byte,
    new_end_byte,
    start_point.row(),
    start_point.column(),
    old_end_point.row(),
    old_end_point.column(),
    new_end_point.row(),
    new_end_point.column(),
  ]
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
fn InputEncoding::to_uint(self : InputEncoding) -> UInt {
  match self {
    UTF8 => 0
    UTF16LE => 1
    UTF16BE => 2
    Custom => 3
  }
}

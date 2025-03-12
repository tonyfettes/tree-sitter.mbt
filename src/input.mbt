///|
struct Input[DecodeFunction] {
  read : (UInt, Point) -> Bytes
  decode : DecodeFunction
}

///|
pub fn Input::new[DecodeFunction](
  read : (Int, Point) -> Bytes,
  decode : DecodeFunction
) -> Input[DecodeFunction] {
  {
    read: fn(byte, point) {
      let byte = uint_to_int(byte)
      read(byte, point)
    },
    decode,
  }
}

///|
type InputEdit FixedArray[UInt]

///|
fn InputEdit::_new(
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
    start_point._row(),
    start_point._column(),
    old_end_point._row(),
    old_end_point._column(),
    new_end_point._row(),
    new_end_point._column(),
  ]
}

///|
pub fn InputEdit::new(
  start_byte : Int,
  old_end_byte : Int,
  new_end_byte : Int,
  start_point : Point,
  old_end_point : Point,
  new_end_point : Point
) -> InputEdit {
  let start_byte = int_to_uint(start_byte)
  let old_end_byte = int_to_uint(old_end_byte)
  let new_end_byte = int_to_uint(new_end_byte)
  InputEdit::_new(
    start_byte, old_end_byte, new_end_byte, start_point, old_end_point, new_end_point,
  )
}

pub(all) struct DecodeResult {
  code_point : Int
  bytes_read : Int
}

///|
/// This function signature reads one code point from the given bytes,
/// returning the number of bytes consumed and the code point
/// to the `code_point` pointer. If the input is valid, return `None`.
pub(open) trait DecodeFunction {
  input_encoding(Self) -> InputEncoding
  decode(Bytes) -> DecodeResult?
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
impl DecodeFunction for InputEncoding with decode(bytes) -> DecodeResult? {
  ignore(bytes)
  None
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

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
    start_point.row,
    start_point.column,
    old_end_point.row,
    old_end_point.column,
    new_end_point.row,
    new_end_point.column,
  ]
}

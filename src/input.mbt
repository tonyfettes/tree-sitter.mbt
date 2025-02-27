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

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

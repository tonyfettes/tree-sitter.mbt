///|
type Range FixedArray[UInt]

///|
pub fn Range::new(
  start_point : Point,
  end_point : Point,
  start_byte : UInt,
  end_byte : UInt
) -> Range {
  [
    start_point.row(),
    start_point.column(),
    end_point.row(),
    end_point.column(),
    start_byte,
    end_byte,
  ]
}

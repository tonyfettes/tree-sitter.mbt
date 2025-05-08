///|
type Range FixedArray[UInt]

///|
pub impl Show for Range with output(self : Range, logger : &@builtin.Logger) -> Unit {
  logger.write_object(self.start_point())
  logger.write_string(" - ")
  logger.write_object(self.end_point())
}

///|
fn Range::_new(
  start_point : Point,
  end_point : Point,
  start_byte : UInt,
  end_byte : UInt
) -> Range {
  [
    start_point._row(),
    start_point._column(),
    end_point._row(),
    end_point._column(),
    start_byte,
    end_byte,
  ]
}

///|
pub fn Range::new(
  start_pointer : Point,
  end_pointer : Point,
  start_byte : Int,
  end_byte : Int
) -> Range {
  let start_byte = int_to_uint(start_byte)
  let end_byte = int_to_uint(end_byte)
  Range::_new(start_pointer, end_pointer, start_byte, end_byte)
}

///|
pub fn Range::start_point(self : Range) -> Point {
  Point::_new(self._[0], self._[1])
}

///|
pub fn Range::end_point(self : Range) -> Point {
  Point::_new(self._[2], self._[3])
}

///|
fn Range::_start_byte(self : Range) -> UInt {
  self._[4]
}

///|
pub fn Range::start_byte(self : Range) -> Int {
  uint_to_int(self._start_byte())
}

///|
fn Range::_end_byte(self : Range) -> UInt {
  self._[5]
}

///|
pub fn Range::end_byte(self : Range) -> Int {
  uint_to_int(self._end_byte())
}

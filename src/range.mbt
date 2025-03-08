///|
type Range FixedArray[UInt]

///|
pub impl Show for Range with output(self : Range, logger : &Logger) -> Unit {
  logger.write_object(self.start_point())
  logger.write_string(" - ")
  logger.write_object(self.end_point())
}

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

///|
pub fn Range::start_point(self : Range) -> Point {
  Point::new(self._[0], self._[1])
}

///|
pub fn Range::end_point(self : Range) -> Point {
  Point::new(self._[2], self._[3])
}

///|
pub fn Range::start_byte(self : Range) -> UInt {
  self._[4]
}

///|
pub fn Range::end_byte(self : Range) -> UInt {
  self._[5]
}

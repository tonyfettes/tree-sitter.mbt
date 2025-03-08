///|
type Point FixedArray[UInt]

///|
pub impl Show for Point with output(self : Point, logger : &Logger) -> Unit {
  logger.write_string("(")
  logger.write_string(self.row().to_string())
  logger.write_string(", ")
  logger.write_string(self.column().to_string())
  logger.write_string(")")
}

///|
pub fn Point::new(row : UInt, column : UInt) -> Point {
  [row, column]
}

///|
pub fn Point::row(self : Point) -> UInt {
  self._[0]
}

///|
pub fn Point::column(self : Point) -> UInt {
  self._[1]
}

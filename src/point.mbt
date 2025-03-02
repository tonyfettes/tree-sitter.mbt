///|
type Point FixedArray[UInt]

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

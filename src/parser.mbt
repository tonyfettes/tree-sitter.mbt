///|
extern type Parser

///|
pub extern "c" fn Parser::new() -> Parser = "moonbit_ts_parser_new"

///|
pub extern "c" fn Parser::delete(self : Parser) = "moonbit_ts_parser_delete"

///|
pub extern "c" fn Parser::set_language(
  self : Parser,
  language : Language
) -> Unit = "moonbit_ts_parser_set_language"

///|
pub fn Parser::parse_string(
  self : Parser,
  old_tree : Tree?,
  string : String
) -> Tree {
  self._parse_bytes(Nullable::of(old_tree), @encoding.encode(UTF8, string))
}

///|
extern "c" fn Parser::_parse_bytes(
  self : Parser,
  old_tree : Nullable[Tree],
  string : Bytes
) -> Tree = "moonbit_ts_parser_parse_string"

///|
extern "c" fn Parser::_parse(
  self : Parser,
  old_tree : Nullable[Tree],
  input : Input_
) -> Tree = "moonbit_ts_parser_parse"

///|
pub extern "c" fn Parser::_set_included_ranges(
  self : Parser,
  ranges : FixedArray[UInt]
) -> Unit = "moonbit_ts_parser_set_included_ranges"

///|
pub fn Parser::set_included_ranges(
  self : Parser,
  ranges : Array[Range]
) -> Unit {
  let flatten_ranges = FixedArray::make(ranges.length() * 6, 0U)
  for i, range in ranges {
    flatten_ranges[i * 6] = range._[0]
    flatten_ranges[i * 6 + 1] = range._[1]
    flatten_ranges[i * 6 + 2] = range._[2]
    flatten_ranges[i * 6 + 3] = range._[3]
    flatten_ranges[i * 6 + 4] = range._[4]
    flatten_ranges[i * 6 + 5] = range._[5]
  }
  self._set_included_ranges(flatten_ranges)
}

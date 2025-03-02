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

///|
extern "c" fn Parser::_included_ranges(self : Parser) -> FixedArray[UInt] = "moonbit_ts_parser_included_ranges"

///|
pub fn Parser::included_ranges(self : Parser) -> Array[Range] {
  let flatten_ranges = self._included_ranges()
  Array::makei(flatten_ranges.length() / 6, fn(i) {
    Range::new(
      Point::new(flatten_ranges[i * 6], flatten_ranges[i * 6 + 1]),
      Point::new(flatten_ranges[i * 6 + 2], flatten_ranges[i * 6 + 3]),
      flatten_ranges[i * 6 + 4],
      flatten_ranges[i * 6 + 5],
    )
  })
}

///|
extern "c" fn Parser::_parse(
  self : Parser,
  old_tree : Nullable[Tree],
  input : (UInt, Point) -> Bytes,
  encoding : InputEncoding,
  decode : Nullable[FuncRef[(Bytes, Int) -> Int]]
) -> Tree = "moonbit_ts_parser_parse"

///|
pub struct ParseState {
  current_byte_offset : UInt
  has_error : Bool
}

///|
struct ParseOptions {
  progress_callback : (ParseState) -> Bool
}

///|
pub fn ParseOptions::new(
  progress_callback : (ParseState) -> Bool
) -> ParseOptions {
  ParseOptions::{ progress_callback, }
}

///|
extern "c" fn Parser::_parse_with_options(
  self : Parser,
  old_tree : Nullable[Tree],
  input : (UInt, Point) -> Bytes,
  encoding : UInt,
  decode : Nullable[FuncRef[(Bytes, Int) -> Int]],
  progress_callback : (UInt, Bool) -> Bool
) -> Tree = "moonbit_ts_parser_parse_with_options"

///|
pub fn Parser::parse[Encoding : DecodeFunction](
  self : Parser,
  old_tree : Tree?,
  input : Input[Encoding],
  options? : ParseOptions
) -> Tree {
  let input_encoding = input.decode.input_encoding()
  let decode : Nullable[FuncRef[(Bytes, Int) -> Int]] = match input_encoding {
    Custom =>
      Nullable::some(fn(bytes, offset) { Encoding::decode(bytes, offset) })
    _ => Nullable::none()
  }
  guard options is Some(options) else {
    return self._parse(
      Nullable::of(old_tree),
      input.read,
      input_encoding,
      decode,
    )
  }
  self._parse_with_options(
    Nullable::of(old_tree),
    input.read,
    input_encoding.to_uint(),
    decode,
    fn(current_byte_offset, has_error) {
      (options.progress_callback)({ current_byte_offset, has_error })
    },
  )
}

///|
extern "c" fn Parser::_parse_bytes(
  self : Parser,
  old_tree : Nullable[Tree],
  string : Bytes
) -> Tree = "moonbit_ts_parser_parse_string"

///|
extern "c" fn Parser::_parse_bytes_encoding(
  self : Parser,
  old_tree : Nullable[Tree],
  string : Bytes,
  encoding : UInt
) -> Tree = "moonbit_ts_parser_parse_string_encoding"

///|
pub fn Parser::parse_bytes(
  self : Parser,
  old_tree : Tree?,
  bytes : Bytes,
  encoding : InputEncoding?
) -> Tree {
  let old_tree = Nullable::of(old_tree)
  match encoding {
    None => self._parse_bytes(old_tree, bytes)
    Some(encoding) =>
      self._parse_bytes_encoding(old_tree, bytes, encoding.to_uint())
  }
}

///|
pub fn Parser::parse_string(
  self : Parser,
  old_tree : Tree?,
  string : String
) -> Tree {
  self._parse_bytes(Nullable::of(old_tree), @encoding.encode(UTF8, string))
}

///|
pub extern "c" fn Parser::reset(self : Parser) = "moonbit_ts_parser_reset"

///|
pub enum LogType {
  Parse
  Lex
}

///|
fn LogType::to_uint(self : LogType) -> UInt {
  match self {
    Parse => 0
    Lex => 1
  }
}

///|
fn LogType::of_uint(value : UInt) -> LogType {
  match value {
    0 => Parse
    1 => Lex
    value => abort("Invalid log type: \{value}")
  }
}

///|
type Logger (UInt, Bytes) -> Unit

///|
fn Logger::new(log : (LogType, String) -> Unit) -> Logger {
  fn(log_type, message) {
    log(
      LogType::of_uint(log_type),
      @encoding.decode_lossy(UTF8, message).to_string(),
    )
  }
}

///|
pub extern "c" fn Parser::set_logger(self : Parser, logger : Logger) = "moonbit_ts_parser_set_logger"

///|
pub extern "c" fn Parser::logger(self : Parser) -> Logger = "moonbit_ts_parser_logger"

///|
extern type Parser

///|
/// Create a new parser.
pub extern "c" fn Parser::new() -> Parser = "moonbit_ts_parser_new"

///|
/// Delete the parser, freeing all of the memory that it used.
pub extern "c" fn Parser::delete(self : Parser) = "moonbit_ts_parser_delete"

///|
/// Set the language that the parser should use for parsing.
///
/// Returns a boolean indicating whether or not the language was successfully
/// assigned. True means assignment succeeded. False means there was a version
/// mismatch: the language was generated with an incompatible version of the
/// Tree-sitter CLI.
pub extern "c" fn Parser::set_language(
  self : Parser,
  language : Language
) -> Unit = "moonbit_ts_parser_set_language"

///|
extern "c" fn Parser::_set_included_ranges(
  self : Parser,
  ranges : FixedArray[UInt]
) -> Unit = "moonbit_ts_parser_set_included_ranges"

///|
/// Set the ranges of text that the parser should include when parsing.
///
/// By default, the parser will always include entire documents. This function
/// allows you to parse only a *portion* of a document but still return a syntax
/// tree whose ranges match up with the document as a whole. You can also pass
/// multiple disjoint ranges.
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
/// Get the ranges of text that the parser will include when parsing.
///
/// The returned pointer is owned by the parser. The caller should not free it
/// or write to it.
pub fn Parser::included_ranges(self : Parser) -> Array[Range] {
  let flatten_ranges = self._included_ranges()
  Array::makei(flatten_ranges.length() / 6, fn(i) {
    Range::_new(
      Point::_new(flatten_ranges[i * 6], flatten_ranges[i * 6 + 1]),
      Point::_new(flatten_ranges[i * 6 + 2], flatten_ranges[i * 6 + 3]),
      flatten_ranges[i * 6 + 4],
      flatten_ranges[i * 6 + 5],
    )
  })
}

///|
extern "c" fn Parser::_parse(
  self : Parser,
  old_tree : @c.Nullable[Tree],
  input : (UInt, Point) -> Bytes,
  encoding : InputEncoding,
  decode : @c.Nullable[FuncRef[(Bytes, @c.Pointer[Int]) -> Int]]
) -> Tree = "moonbit_ts_parser_parse"

///|
pub struct ParseState {
  current_byte_offset : Int
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
  old_tree : @c.Nullable[Tree],
  input : (UInt, Point) -> Bytes,
  encoding : UInt,
  decode : @c.Nullable[FuncRef[(Bytes, @c.Pointer[Int]) -> Int]],
  progress_callback : (UInt, Bool) -> Bool
) -> Tree = "moonbit_ts_parser_parse_with_options"

///|
/// Use the parser to parse some source code and create a syntax tree.
///
/// If you are parsing this document for the first time, pass `None` for the
/// `old_tree` parameter. Otherwise, if you have already parsed an earlier
/// version of this document and the document has since been edited, pass the
/// previous syntax tree so that the unchanged parts of it can be reused.
/// This will save time and memory.
pub fn Parser::parse[Encoding : DecodeFunction](
  self : Parser,
  old_tree : Tree?,
  input : Input[Encoding],
  options? : ParseOptions
) -> Tree {
  let input_encoding = input.decode.input_encoding()
  let decode : @c.Nullable[FuncRef[(Bytes, @c.Pointer[Int]) -> Int]] = match
    input_encoding {
    Custom =>
      @c.Nullable::some(fn(bytes, code_point) {
        match Encoding::decode(bytes) {
          Some(result) => {
            code_point.store(result.code_point)
            result.bytes_read
          }
          None => -1
        }
      })
    _ => @c.Nullable::none()
  }
  guard options is Some(options) else {
    return self._parse(
      @c.Nullable::of(old_tree),
      input.read,
      input_encoding,
      decode,
    )
  }
  self._parse_with_options(
    @c.Nullable::of(old_tree),
    input.read,
    input_encoding.to_uint(),
    decode,
    fn(current_byte_offset, has_error) {
      let current_byte_offset = uint_to_int(current_byte_offset)
      (options.progress_callback)({ current_byte_offset, has_error })
    },
  )
}

///|
extern "c" fn Parser::_parse_bytes(
  self : Parser,
  old_tree : @c.Nullable[Tree],
  string : Bytes
) -> Tree = "moonbit_ts_parser_parse_string"

///|
extern "c" fn Parser::_parse_bytes_encoding(
  self : Parser,
  old_tree : @c.Nullable[Tree],
  string : Bytes,
  encoding : UInt
) -> Tree = "moonbit_ts_parser_parse_string_encoding"

///|
/// Use the parser to parse some source code stored in one contiguous buffer with
/// a given encoding. The first three parameters work the same as in the
/// `parse` method. The final parameter indicates whether
/// the text is encoded as UTF8 or UTF16.
pub fn Parser::parse_bytes(
  self : Parser,
  old_tree : Tree?,
  bytes : Bytes,
  encoding? : InputEncoding
) -> Tree {
  let old_tree = @c.Nullable::of(old_tree)
  match encoding {
    None => self._parse_bytes(old_tree, bytes)
    Some(encoding) =>
      self._parse_bytes_encoding(old_tree, bytes, encoding.to_uint())
  }
}

///|
/// Use the parser to parse some source code stored in one contiguous string buffer.
/// The first two parameters are the same as in the `parse` function.
pub fn Parser::parse_string(
  self : Parser,
  old_tree : Tree?,
  string : String
) -> Tree {
  self._parse_bytes(@c.Nullable::of(old_tree), @encoding.encode(UTF8, string))
}

///|
/// Instruct the parser to start the next parse from the beginning.
///
/// If the parser previously failed because of a timeout or a cancellation, then
/// by default, it will resume where it left off on the next call to
/// `parse` or other parsing functions. If you don't want to resume,
/// and instead intend to use this parser to parse some other document, you must
/// call `reset` first.
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
      @encoding.decoder(UTF8).decode_lossy(message),
    )
  }
}

///|
/// Set the logger that a parser should use during parsing.
///
/// The parser does not take ownership over the logger payload. If a logger was
/// previously assigned, the caller is responsible for releasing any memory
/// owned by the previous logger.
pub extern "c" fn Parser::set_logger(self : Parser, logger : Logger) = "moonbit_ts_parser_set_logger"

///|
/// Get the parser's current logger.
pub extern "c" fn Parser::logger(self : Parser) -> Logger = "moonbit_ts_parser_logger"

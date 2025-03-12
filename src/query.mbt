///|
extern type Query

///|
type! QueryError {
  Syntax(UInt)
  NodeType(UInt)
  Field(UInt)
  Capture(UInt)
  Structure(UInt)
  Language(UInt)
} derive(Show)

///|
fn QueryError::offset(self : QueryError) -> UInt {
  match self {
    QueryError::Syntax(offset) => offset
    QueryError::NodeType(offset) => offset
    QueryError::Field(offset) => offset
    QueryError::Capture(offset) => offset
    QueryError::Structure(offset) => offset
    QueryError::Language(offset) => offset
  }
}

///|
fn QueryError::from(offset : UInt, type_ : UInt) -> QueryError {
  match type_ {
    1 => QueryError::Syntax(offset)
    2 => QueryError::NodeType(offset)
    3 => QueryError::Field(offset)
    4 => QueryError::Capture(offset)
    5 => QueryError::Structure(offset)
    6 => QueryError::Language(offset)
    type_ => abort("Invalid QueryError type: \{type_}")
  }
}

///|
extern "c" fn Query::_new(
  language : Language,
  source : Bytes,
  error : FixedArray[UInt]
) -> Query = "moonbit_ts_query_new"

///|
pub fn Query::new(language : Language, source : String) -> Query!QueryError {
  let error = FixedArray::make(2, 0U)
  let source = @encoding.encode(UTF8, source)
  let query = Query::_new(language, source, error)
  if error[1] == 0 {
    query
  } else {
    raise QueryError::from(error[0], error[1])
  }
}

///|
pub extern "c" fn Query::delete(self : Query) = "moonbit_ts_query_delete"

///|
extern "c" fn Query::_pattern_count(self : Query) -> UInt = "moonbit_ts_query_pattern_count"

///|
pub fn Query::pattern_count(self : Query) -> Int {
  uint_to_int(self._pattern_count())
}

///|
extern "c" fn Query::_capture_count(self : Query) -> UInt = "moonbit_ts_query_capture_count"

///|
pub fn Query::capture_count(self : Query) -> Int {
  uint_to_int(self._capture_count())
}

///|
extern "c" fn Query::_string_count(self : Query) -> UInt = "moonbit_ts_query_string_count"

///|
pub fn Query::string_count(self : Query) -> Int {
  uint_to_int(self._string_count())
}

///|
extern "c" fn Query::_start_byte_for_pattern(
  self : Query,
  pattern_index : UInt
) -> UInt = "moonbit_ts_query_start_byte_for_pattern"

///|
pub fn Query::start_byte_for_pattern(self : Query, pattern_index : Int) -> Int {
  let pattern_index = int_to_uint(pattern_index)
  self._start_byte_for_pattern(pattern_index) |> uint_to_int()
}

///|
extern "c" fn Query::_end_byte_for_pattern(
  self : Query,
  pattern_index : UInt
) -> UInt = "moonbit_ts_query_end_byte_for_pattern"

///|
pub fn Query::end_byte_for_pattern(self : Query, pattern_index : Int) -> Int {
  let pattern_index = int_to_uint(pattern_index)
  self._end_byte_for_pattern(pattern_index) |> uint_to_int()
}

///|
extern "c" fn Query::_predicates_for_pattern(
  self : Query,
  pattern_index : UInt
) -> FixedArray[UInt] = "moonbit_ts_query_predicates_for_pattern"

///|
pub enum QueryPredicateStepType {
  Done
  Capture
  String
}

///|
fn QueryPredicateStepType::of_uint(value : UInt) -> QueryPredicateStepType {
  match value {
    0 => QueryPredicateStepType::Done
    1 => QueryPredicateStepType::Capture
    2 => QueryPredicateStepType::String
    value => abort("Invalid QueryPredicateStepType: \{value}")
  }
}

///|
pub struct QueryPredicateStep {
  type_ : QueryPredicateStepType
  value : Int
}

///|
pub fn Query::predicates_for_pattern(
  self : Query,
  pattern_index : Int
) -> Array[QueryPredicateStep] {
  let pattern_index = int_to_uint(pattern_index)
  let flatten_predicates = Query::_predicates_for_pattern(self, pattern_index)
  Array::makei(flatten_predicates.length() / 2, fn(i) {
    let value = flatten_predicates[i * 2 + 1]
    let value = uint_to_int(value)
    QueryPredicateStep::{
      type_: QueryPredicateStepType::of_uint(flatten_predicates[i * 2]),
      value,
    }
  })
}

///|
extern "c" fn Query::_is_pattern_rooted(
  self : Query,
  pattern_index : UInt
) -> Bool = "moonbit_ts_query_is_pattern_rooted"

///|
pub fn Query::is_pattern_rooted(self : Query, pattern_index : Int) -> Bool {
  self._is_pattern_rooted(int_to_uint(pattern_index))
}

///|
extern "c" fn Query::_is_pattern_non_local(
  self : Query,
  pattern_index : UInt
) -> Bool = "moonbit_ts_query_is_pattern_non_local"

///|
pub fn Query::is_pattern_non_local(self : Query, pattern_index : Int) -> Bool {
  self._is_pattern_non_local(int_to_uint(pattern_index))
}

///|
extern "c" fn Query::_is_pattern_guaranteed_at_step(
  self : Query,
  byte_offset : UInt
) -> Bool = "moonbit_ts_query_is_pattern_guaranteed_at_step"

///|
pub fn Query::is_pattern_guaranteed_at_step(
  self : Query,
  byte_offset : Int
) -> Bool {
  self._is_pattern_guaranteed_at_step(int_to_uint(byte_offset))
}

///|
extern "c" fn Query::_capture_name_for_id(
  self : Query,
  capture_id : UInt
) -> Bytes = "moonbit_ts_query_capture_name_for_id"

///|
pub fn Query::capture_name_for_id(self : Query, capture_id : Int) -> String {
  let capture_id = int_to_uint(capture_id)
  let name = Query::_capture_name_for_id(self, capture_id)
  @encoding.decoder(UTF8).decode_lossy(name)
}

///|
pub enum Quantifier {
  Zero
  ZeroOrOne
  ZeroOrMore
  One
  OneOrMore
}

///|
fn Quantifier::of_uint(value : UInt) -> Quantifier {
  match value {
    0 => Quantifier::Zero
    1 => Quantifier::ZeroOrOne
    2 => Quantifier::ZeroOrMore
    3 => Quantifier::One
    4 => Quantifier::OneOrMore
    value => abort("Invalid Quantifier: \{value}")
  }
}

///|
extern "c" fn Query::_capture_quantifier_for_id(
  self : Query,
  pattern_index : UInt,
  capture_index : UInt
) -> UInt = "moonbit_ts_query_capture_quantifier_for_id"

///|
pub fn Query::capture_quantifier_for_id(
  self : Query,
  pattern_index : Int,
  capture_index : Int
) -> Quantifier {
  let pattern_index = int_to_uint(pattern_index)
  let capture_index = int_to_uint(capture_index)
  Quantifier::of_uint(
    Query::_capture_quantifier_for_id(self, pattern_index, capture_index),
  )
}

///|
extern "c" fn Query::_string_value_for_id(
  self : Query,
  string_id : UInt
) -> Bytes = "moonbit_ts_query_string_value_for_id"

///|
pub fn Query::string_value_for_id(self : Query, string_id : Int) -> String {
  let string_id = int_to_uint(string_id)
  let value = Query::_string_value_for_id(self, string_id)
  @encoding.decoder(UTF8).decode_lossy(value)
}

///|
extern "c" fn Query::_disable_capture(self : Query, name : Bytes) = "moonbit_ts_query_disable_capture"

///|
pub fn Query::disable_capture(self : Query, name : String) -> Unit {
  let name = @encoding.encode(UTF8, name)
  Query::_disable_capture(self, name)
}

///|
extern "c" fn Query::_disable_pattern(self : Query, pattern_index : UInt) = "moonbit_ts_query_disable_pattern"

///|
pub fn Query::disable_pattern(self : Query, pattern_index : Int) -> Unit {
  self._disable_pattern(int_to_uint(pattern_index))
}

///|
extern type QueryCursor

///|
pub extern "c" fn QueryCursor::new() -> QueryCursor = "moonbit_ts_query_cursor_new"

///|
pub extern "c" fn QueryCursor::delete(self : QueryCursor) = "moonbit_ts_query_cursor_delete"

///|
extern "c" fn QueryCursor::_exec(
  self : QueryCursor,
  query : Query,
  node : Node
) = "moonbit_ts_query_cursor_exec"

///|
extern "c" fn QueryCursor::_exec_with_options(
  self : QueryCursor,
  query : Query,
  node : Node,
  progress_callback : (UInt) -> Unit
) = "moonbit_ts_query_cursor_exec_with_options"

///|
pub struct QueryCursorState {
  current_byte_offset : Int
}

///|
pub(all) struct QueryCursorOptions {
  progress_callback : (QueryCursorState) -> Unit
}

///|
pub fn QueryCursor::exec(
  self : QueryCursor,
  query : Query,
  node : Node,
  options? : QueryCursorOptions
) -> Unit {
  match options {
    None => QueryCursor::_exec(self, query, node)
    Some(options) =>
      QueryCursor::_exec_with_options(self, query, node, fn(
        current_byte_offset
      ) {
        let current_byte_offset = uint_to_int(current_byte_offset)
        (options.progress_callback)(QueryCursorState::{ current_byte_offset, })
      })
  }
}

///|
pub extern "c" fn QueryCursor::did_exceed_match_limit(
  self : QueryCursor
) -> Bool = "moonbit_ts_query_cursor_did_exceed_match_limit"

///|
extern "c" fn QueryCursor::_match_limit(self : QueryCursor) -> UInt = "moonbit_ts_query_cursor_match_limit"

///|
pub fn QueryCursor::match_limit(self : QueryCursor) -> Int {
  uint_to_int(self._match_limit())
}

///|
extern "c" fn QueryCursor::_set_match_limit(self : QueryCursor, limit : UInt) = "moonbit_ts_query_cursor_set_match_limit"

///|
pub fn QueryCursor::set_match_limit(self : QueryCursor, limit : Int) -> Unit {
  self._set_match_limit(int_to_uint(limit))
}

///|
extern "c" fn QueryCursor::_set_byte_range(
  self : QueryCursor,
  start_byte : UInt,
  end_byte : UInt
) = "moonbit_ts_query_cursor_set_byte_range"

///|
pub fn QueryCursor::set_byte_range(
  self : QueryCursor,
  start_byte : Int,
  end_byte : Int
) -> Unit {
  let start_byte = int_to_uint(start_byte)
  let end_byte = int_to_uint(end_byte)
  self._set_byte_range(start_byte, end_byte)
}

///|
pub extern "c" fn QueryCursor::set_point_range(
  self : QueryCursor,
  start_point : Point,
  end_point : Point
) = "moonbit_ts_query_cursor_set_point_range"

///|
pub struct QueryCapture {
  node : Node
  index : Int
} derive(Show)

///|
pub struct QueryMatch {
  id : Int
  pattern_index : Int
  captures : FixedArray[QueryCapture]
}

///|
priv type QueryMatch_ Bytes

///|
fn init {
  ignore(QueryMatch_)
}

///|
extern "c" fn QueryMatch_::id(self : QueryMatch_) -> UInt = "moonbit_ts_query_match_id"

///|
extern "c" fn QueryMatch_::pattern_index(self : QueryMatch_) -> UInt = "moonbit_ts_query_match_pattern_index"

///|
extern "c" fn QueryMatch_::capture_count(self : QueryMatch_) -> UInt16 = "moonbit_ts_query_match_capture_count"

///|
extern "c" fn QueryMatch_::captures_get_node(
  self : QueryMatch_,
  index : UInt
) -> Node = "moonbit_ts_query_match_captures_get_node"

///|
extern "c" fn QueryMatch_::captures_get_index(
  self : QueryMatch_,
  index : UInt
) -> UInt = "moonbit_ts_query_match_captures_get_index"

///|
extern "c" fn QueryCursor::_next_match(
  self : QueryCursor
) -> @c.Nullable[QueryMatch_] = "moonbit_ts_query_cursor_next_match"

///|
pub fn QueryCursor::next_match(self : QueryCursor) -> QueryMatch? {
  let match_ = QueryCursor::_next_match(self).to()
  guard match_ is Some(match_) else { return None }
  let capture_count = QueryMatch_::capture_count(match_)
  let captures = FixedArray::makei(capture_count.to_int(), fn(i) {
    let i = i.reinterpret_as_uint()
    let node = QueryMatch_::captures_get_node(match_, i)
    let index = QueryMatch_::captures_get_index(match_, i)
    let index = uint_to_int(index)
    QueryCapture::{ node, index }
  })
  let id = uint_to_int(QueryMatch_::id(match_))
  let pattern_index = uint_to_int(QueryMatch_::pattern_index(match_))
  Some(QueryMatch::{ id, pattern_index, captures })
}

///|
extern "c" fn QueryCursor::_remove_match(self : QueryCursor, match_id : UInt) = "moonbit_ts_query_cursor_remove_match"

///|
pub fn QueryCursor::remove_match(self : QueryCursor, match_id : Int) -> Unit {
  self._remove_match(int_to_uint(match_id))
}

///|
extern "c" fn QueryCursor::_next_capture(
  self : QueryCursor,
  match_id : FixedArray[UInt]
) -> @c.Nullable[QueryMatch_] = "moonbit_ts_query_cursor_next_capture"

///|
pub fn QueryCursor::next_capture(self : QueryCursor) -> QueryCapture? {
  let match_id = FixedArray::make(1, 0U)
  let match_ = QueryCursor::_next_capture(self, match_id).to()
  guard match_ is Some(match_) else { return None }
  let node = QueryMatch_::captures_get_node(match_, 0)
  let index = QueryMatch_::captures_get_index(match_, 0)
  let index = uint_to_int(index)
  Some(QueryCapture::{ node, index })
}

///|
extern "c" fn QueryCursor::_set_max_start_depth(
  self : QueryCursor,
  max_start_depth : UInt
) = "moonbit_ts_query_cursor_set_max_start_depth"

///|
pub fn QueryCursor::set_max_start_depth(
  self : QueryCursor,
  max_start_depth : Int
) -> Unit {
  self._set_max_start_depth(int_to_uint(max_start_depth))
}

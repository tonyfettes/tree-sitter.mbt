///|
extern type Query

///|
type! QueryError {
  Syntax(UInt)
  NodeType(UInt)
  Field(UInt)
  Capture(UInt)
} derive(Show)

///|
fn QueryError::offset(self : QueryError) -> UInt {
  match self {
    QueryError::Syntax(offset) => offset
    QueryError::NodeType(offset) => offset
    QueryError::Field(offset) => offset
    QueryError::Capture(offset) => offset
  }
}

///|
fn QueryError::from(offset : UInt, type_ : UInt) -> QueryError {
  match type_ {
    1 => QueryError::Syntax(offset)
    2 => QueryError::NodeType(offset)
    3 => QueryError::Field(offset)
    4 => QueryError::Capture(offset)
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
pub extern "c" fn Query::pattern_count(self : Query) -> UInt = "moonbit_ts_query_pattern_count"

///|
pub extern "c" fn Query::capture_count(self : Query) -> UInt = "moonbit_ts_query_capture_count"

///|
pub extern "c" fn Query::string_count(self : Query) -> UInt = "moonbit_ts_query_string_count"

///|
pub extern "c" fn Query::start_byte_for_pattern(
  self : Query,
  pattern_index : UInt
) -> UInt = "moonbit_ts_query_start_byte_for_pattern"

///|
pub extern "c" fn Query::end_byte_for_pattern(
  self : Query,
  pattern_index : UInt
) -> UInt = "moonbit_ts_query_end_byte_for_pattern"

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
  value : UInt
}

///|
pub fn Query::predicates_for_pattern(
  self : Query,
  pattern_index : UInt
) -> Array[QueryPredicateStep] {
  let flatten_predicates = Query::_predicates_for_pattern(self, pattern_index)
  Array::makei(flatten_predicates.length() / 2, fn(i) {
    QueryPredicateStep::{
      type_: QueryPredicateStepType::of_uint(flatten_predicates[i * 2]),
      value: flatten_predicates[i * 2 + 1],
    }
  })
}

///|
pub extern "c" fn Query::is_pattern_rooted(
  self : Query,
  pattern_index : UInt
) -> Bool = "moonbit_ts_query_is_pattern_rooted"

///|
pub extern "c" fn Query::is_pattern_non_local(
  self : Query,
  pattern_index : UInt
) -> Bool = "moonbit_ts_query_is_pattern_non_local"

///|
pub extern "c" fn Query::is_pattern_guaranteed_at_step(
  self : Query,
  byte_offset : UInt
) -> Bool = "moonbit_ts_query_is_pattern_guaranteed_at_step"

///|
extern "c" fn Query::_capture_name_for_id(
  self : Query,
  capture_id : UInt
) -> Bytes = "moonbit_ts_query_capture_name_for_id"

///|
pub fn Query::capture_name_for_id(self : Query, capture_id : UInt) -> String {
  let name = Query::_capture_name_for_id(self, capture_id)
  @encoding.decode_strict(UTF8, name).to_string?().unwrap()
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
  pattern_index : UInt,
  capture_index : UInt
) -> Quantifier {
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
pub fn Query::string_value_for_id(self : Query, string_id : UInt) -> String {
  let value = Query::_string_value_for_id(self, string_id)
  @encoding.decode_strict(UTF8, value).to_string?().unwrap()
}

///|
extern "c" fn Query::_disable_capture(self : Query, name : Bytes) = "moonbit_ts_query_disable_capture"

///|
pub fn Query::disable_capture(self : Query, name : String) -> Unit {
  let name = @encoding.encode(UTF8, name)
  Query::_disable_capture(self, name)
}

///|
pub extern "c" fn Query::disable_pattern(self : Query, pattern_index : UInt) = "moonbit_ts_query_disable_pattern"

///|
extern type QueryCursor

///|
pub extern "c" fn QueryCursor::new() -> QueryCursor = "moonbit_ts_query_cursor_new"

///|
pub extern "c" fn QueryCursor::exec(
  self : QueryCursor,
  query : Query,
  node : Node
) = "moonbit_ts_query_cursor_exec"

///|
pub struct QueryCapture {
  node : Node
  index : UInt
}

///|
pub struct QueryMatch {
  id : UInt
  pattern_index : UInt
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
) -> Nullable[QueryMatch_] = "moonbit_ts_query_cursor_next_match"

///|
pub fn QueryCursor::next_match(self : QueryCursor) -> QueryMatch? {
  let match_ = QueryCursor::_next_match(self)
  if match_.is_none() {
    return None
  }
  let match_ = match_.unwrap()
  let capture_count = QueryMatch_::capture_count(match_)
  let captures = FixedArray::makei(capture_count.to_int(), fn(i) {
    let i = i.reinterpret_as_uint()
    let node = QueryMatch_::captures_get_node(match_, i)
    let index = QueryMatch_::captures_get_index(match_, i)
    QueryCapture::{ node, index }
  })
  Some(QueryMatch::{
    id: QueryMatch_::id(match_),
    pattern_index: QueryMatch_::pattern_index(match_),
    captures,
  })
}

///|
pub extern "c" fn QueryCursor::delete(self : QueryCursor) = "moonbit_ts_query_cursor_delete"

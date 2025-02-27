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
type QueryMatch_ Bytes

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

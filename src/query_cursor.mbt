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

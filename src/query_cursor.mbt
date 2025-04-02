///|
/// A cursor for executing a query on a syntax tree.
type QueryCursor

///|
/// Create a new cursor for executing a given query.
///
/// The cursor stores the state that is needed to iteratively search
/// for matches. To use the query cursor, first call QueryCursor::exec
/// to start running a given query on a given syntax node. Then, there are
/// two options for consuming the results of the query:
/// 1. Repeatedly call QueryCursor::next_match to iterate over all of the
///    *matches* in the order that they were found. Each match contains the
///    index of the pattern that matched, and an array of captures. Because
///    multiple patterns can match the same set of nodes, one match may contain
///    captures that appear *before* some of the captures from a previous match.
/// 2. Repeatedly call QueryCursor::next_capture to iterate over all of the
///    individual *captures* in the order that they appear. This is useful if
///    don't care about which pattern matched, and just want a single ordered
///    sequence of captures.
///
/// If you don't care about consuming all of the results, you can stop calling
/// QueryCursor::next_match or QueryCursor::next_capture at any point.
/// You can then start executing another query on another node by calling
/// QueryCursor::exec again.
pub extern "c" fn QueryCursor::new() -> QueryCursor = "moonbit_ts_query_cursor_new"

///|
#borrow(self)
extern "c" fn QueryCursor::_exec(
  self : QueryCursor,
  query : Query,
  node : Node
) = "moonbit_ts_query_cursor_exec"

///|
#borrow(self)
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
/// Start running a given query on a given node, with optional options.
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
/// Check if the query cursor exceeded its match limit.
///
/// Query cursors have an optional maximum capacity for storing lists of
/// in-progress captures. If this capacity is exceeded, then the
/// earliest-starting match will silently be dropped to make room for further
/// matches. This maximum capacity is optional — by default, query cursors allow
/// any number of pending matches, dynamically allocating new space for them as
/// needed as the query is executed.
#borrow(self)
pub extern "c" fn QueryCursor::did_exceed_match_limit(
  self : QueryCursor
) -> Bool = "moonbit_ts_query_cursor_did_exceed_match_limit"

///|
#borrow(self)
extern "c" fn QueryCursor::_match_limit(self : QueryCursor) -> UInt = "moonbit_ts_query_cursor_match_limit"

///|
/// Get the maximum number of in-progress matches allowed by this query cursor.
///
/// See `QueryCursor::did_exceed_match_limit`.
pub fn QueryCursor::match_limit(self : QueryCursor) -> Int {
  uint_to_int(self._match_limit())
}

///|
#borrow(self)
extern "c" fn QueryCursor::_set_match_limit(self : QueryCursor, limit : UInt) = "moonbit_ts_query_cursor_set_match_limit"

///|
/// Set the maximum number of in-progress matches allowed by this query cursor.
///
/// See `QueryCursor::did_exceed_match_limit`.
pub fn QueryCursor::set_match_limit(self : QueryCursor, limit : Int) -> Unit {
  self._set_match_limit(int_to_uint(limit))
}

///|
#borrow(self)
extern "c" fn QueryCursor::_set_byte_range(
  self : QueryCursor,
  start_byte : UInt,
  end_byte : UInt
) = "moonbit_ts_query_cursor_set_byte_range"

///|
/// Set the range of bytes in which the query will be executed.
///
/// The query cursor will return matches that intersect with the given byte range.
/// This means that a match may be returned even if some of its captures fall
/// outside the specified range, as long as at least part of the match
/// overlaps with the range.
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
/// Set the range of (row, column) positions in which the query will be executed.
///
/// The query cursor will return matches that intersect with the given point range.
/// This means that a match may be returned even if some of its captures fall
/// outside the specified range, as long as at least part of the match
/// overlaps with the range.
#borrow(self, start_point, end_point)
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
priv type QueryMatch_

///|
#borrow(self)
extern "c" fn QueryMatch_::id(self : QueryMatch_) -> UInt = "moonbit_ts_query_match_id"

///|
#borrow(self)
extern "c" fn QueryMatch_::pattern_index(self : QueryMatch_) -> UInt = "moonbit_ts_query_match_pattern_index"

///|
#borrow(self)
extern "c" fn QueryMatch_::capture_count(self : QueryMatch_) -> UInt16 = "moonbit_ts_query_match_capture_count"

///|
extern "c" fn QueryMatch_::captures_get_node(
  self : QueryMatch_,
  index : UInt
) -> Node = "moonbit_ts_query_match_captures_get_node"

///|
#borrow(self)
extern "c" fn QueryMatch_::captures_get_index(
  self : QueryMatch_,
  index : UInt
) -> UInt = "moonbit_ts_query_match_captures_get_index"

///|
extern "c" fn QueryCursor::_next_match(
  self : QueryCursor
) -> @c.Nullable[QueryMatch_] = "moonbit_ts_query_cursor_next_match"

///|
/// Advance to the next match of the currently running query.
///
/// If there is a match, returns Some(match).
/// Otherwise, returns None.
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
#borrow(self)
extern "c" fn QueryCursor::_remove_match(self : QueryCursor, match_id : UInt) = "moonbit_ts_query_cursor_remove_match"

///|
/// Remove a match from the query cursor's results.
pub fn QueryCursor::remove_match(self : QueryCursor, match_id : Int) -> Unit {
  self._remove_match(int_to_uint(match_id))
}

///|
extern "c" fn QueryCursor::_next_capture(
  self : QueryCursor,
  match_id : FixedArray[UInt]
) -> @c.Nullable[QueryMatch_] = "moonbit_ts_query_cursor_next_capture"

///|
/// Advance to the next capture of the currently running query.
///
/// If there is a capture, returns Some(capture).
/// Otherwise, returns None.
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
#borrow(self)
extern "c" fn QueryCursor::_set_max_start_depth(
  self : QueryCursor,
  max_start_depth : UInt
) = "moonbit_ts_query_cursor_set_max_start_depth"

///|
/// Set the maximum start depth for a query cursor.
///
/// This prevents cursors from exploring children nodes at a certain depth.
/// Note if a pattern includes many children, then they will still be checked.
///
/// The zero max start depth value can be used as a special behavior and
/// it helps to destructure a subtree by staying on a node and using captures
/// for interested parts. Note that the zero max start depth only limit a search
/// depth for a pattern's root node but other nodes that are parts of the pattern
/// may be searched at any depth what defined by the pattern structure.
///
/// Set to `@uint.max_value` to remove the maximum start depth.
pub fn QueryCursor::set_max_start_depth(
  self : QueryCursor,
  max_start_depth : Int
) -> Unit {
  self._set_max_start_depth(int_to_uint(max_start_depth))
}

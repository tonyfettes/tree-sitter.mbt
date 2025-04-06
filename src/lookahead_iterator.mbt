///|
extern type LookaheadIterator

///|
extern "c" fn LookaheadIterator::_new(
  language : Language,
  state : StateId
) -> @c.Nullable[LookaheadIterator] = "moonbit_ts_lookahead_iterator_new"

///|
/// Create a new lookahead iterator for the given language and parse state.
///
/// This returns `None` if state is invalid for the language.
///
/// Repeatedly using `LookaheadIterator::next` and
/// `LookaheadIterator::current_symbol` will generate valid symbols in the
/// given parse state. Newly created lookahead iterators will contain the
/// `ERROR` symbol.
///
/// Lookahead iterators can be useful to generate suggestions and improve syntax
/// error diagnostics. To get symbols valid in an ERROR node, use the lookahead
/// iterator on its first leaf node state. For `MISSING` nodes, a lookahead
/// iterator created on the previous non-extra leaf node may be appropriate.
pub fn LookaheadIterator::new(
  language : Language,
  state : StateId
) -> LookaheadIterator? {
  LookaheadIterator::_new(language, state).to()
}

///|
/// Delete a lookahead iterator freeing all the memory used.
pub extern "c" fn LookaheadIterator::delete(self : LookaheadIterator) = "moonbit_ts_lookahead_iterator_delete"

///|
/// Reset the lookahead iterator to another state.
///
/// This returns `true` if the iterator was reset to the given state and `false`
/// otherwise.
pub extern "c" fn LookaheadIterator::reset_state(
  self : LookaheadIterator,
  state : StateId
) -> Bool = "moonbit_ts_lookahead_iterator_reset_state"

///|
/// Reset the lookahead iterator.
///
/// This returns `true` if the language was set successfully and `false`
/// otherwise.
pub extern "c" fn LookaheadIterator::reset(
  self : LookaheadIterator,
  language : Language,
  state : StateId
) -> Bool = "moonbit_ts_lookahead_iterator_reset"

///|
/// Get the current language of the lookahead iterator.
pub extern "c" fn LookaheadIterator::language(
  self : LookaheadIterator
) -> Language = "moonbit_ts_lookahead_iterator_language"

///|
/// Advance the lookahead iterator to the next symbol.
///
/// This returns `true` if there is a new symbol and `false` otherwise.
pub extern "c" fn LookaheadIterator::next(self : LookaheadIterator) -> Bool = "moonbit_ts_lookahead_iterator_next"

///|
/// Get the current symbol of the lookahead iterator.
pub extern "c" fn LookaheadIterator::current_symbol(
  self : LookaheadIterator
) -> Symbol = "moonbit_ts_lookahead_iterator_current_symbol"

///|
extern "c" fn LookaheadIterator::_current_symbol_name(
  self : LookaheadIterator
) -> @c.Pointer[Byte] = "moonbit_ts_lookahead_iterator_current_symbol_name"

///|
/// Get the current symbol type of the lookahead iterator as a string.
pub fn LookaheadIterator::current_symbol_name(
  self : LookaheadIterator
) -> String? {
  let bytes = LookaheadIterator::_current_symbol_name(self)
  decode_c_string(bytes)
}

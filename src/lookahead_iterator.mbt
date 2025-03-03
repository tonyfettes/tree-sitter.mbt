///|
extern type LookaheadIterator

///|
pub extern "c" fn LookaheadIterator::new(
  language : Language,
  state : StateId
) -> LookaheadIterator = "moonbit_ts_lookahead_iterator_new"

///|
pub extern "c" fn LookaheadIterator::delete(self : LookaheadIterator) = "moonbit_ts_lookahead_iterator_delete"

///|
pub extern "c" fn LookaheadIterator::reset_state(
  self : LookaheadIterator,
  state : StateId
) = "moonbit_ts_lookahead_iterator_reset_state"

///|
pub extern "c" fn LookaheadIterator::reset(
  self : LookaheadIterator,
  language : Language,
  state : StateId
) = "moonbit_ts_lookahead_iterator_reset"

///|
pub extern "c" fn LookaheadIterator::language(
  self : LookaheadIterator
) -> Language = "moonbit_ts_lookahead_iterator_language"

///|
pub extern "c" fn LookaheadIterator::next(self : LookaheadIterator) -> Bool = "moonbit_ts_lookahead_iterator_next"

///|
pub extern "c" fn LookaheadIterator::current_symbol(
  self : LookaheadIterator
) -> Symbol = "moonbit_ts_lookahead_iterator_current_symbol"

///|
extern "c" fn LookaheadIterator::_current_symbol_name(
  self : LookaheadIterator
) -> Bytes = "moonbit_ts_lookahead_iterator_current_symbol_name"

///|
pub fn LookaheadIterator::current_symbol_name(
  self : LookaheadIterator
) -> String {
  let bytes = LookaheadIterator::_current_symbol_name(self)
  @encoding.decode_strict(UTF8, bytes).to_string?().unwrap()
}

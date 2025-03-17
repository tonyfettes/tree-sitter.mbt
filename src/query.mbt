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
priv enum QueryPredicateStepType {
  Done
  Capture
  String
} derive(Show)

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
pub enum QueryPredicateStep {
  Capture(String)
  String(String)
} derive(Show)

///|
pub typealias QueryPredicate = Array[QueryPredicateStep]

///|
pub fn Query::predicates_for_pattern(
  self : Query,
  pattern_index : Int
) -> Array[QueryPredicate] {
  let pattern_index = int_to_uint(pattern_index)
  let flatten_predicates = Query::_predicates_for_pattern(self, pattern_index)
  let predicates = []
  let mut predicate = []
  for i in 0..<(flatten_predicates.length() / 2) {
    let value = flatten_predicates[i * 2 + 1]
    let value = uint_to_int(value)
    let type_ = QueryPredicateStepType::of_uint(flatten_predicates[i * 2])
    match type_ {
      Capture => {
        let name = Query::capture_name_for_id(self, value)
        predicate.push(QueryPredicateStep::Capture(name))
      }
      String => {
        let value = Query::string_value_for_id(self, value)
        predicate.push(QueryPredicateStep::String(value))
      }
      Done => {
        predicates.push(predicate)
        predicate = []
      }
    }
  }
  predicates
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
} derive(Show)

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

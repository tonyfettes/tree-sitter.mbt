///|
test "exp" {
  start!(fn() { test_query_language_exp!(@tree_sitter_moonbit.language()) })
}

///|
test "top" {
  start!(fn() { test_query_language_top!(@tree_sitter_moonbit.language()) })
}

///|
test "fn-ambiguity" {
  start!(fn() {
    test_query_language_fn_ambiguity!(@tree_sitter_moonbit.language())
  })
}

///|
test "concat" {
  start!(fn() { test_query_language_concat!(@tree_sitter_moonbit.language()) })
}

///|
test "ty" {
  start!(fn() { test_query_language_ty!(@tree_sitter_moonbit.language()) })
}

///|
test "id" {
  start!(fn() { test_query_language_id!(@tree_sitter_moonbit.language()) })
}

///|
test "quantifier" {
  start!(fn() {
    test_query_language_quantifier!(@tree_sitter_moonbit.language())
  })
}

///|
test "group" {
  start!(fn() { test_query_language_group!(@tree_sitter_moonbit.language()) })
}

///|
test "case" {
  start!(fn() { test_query_language_case!(@tree_sitter_moonbit.language()) })
}

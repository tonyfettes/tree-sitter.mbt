///|
test "language" {
  let language : @tree_sitter.Language = @tree_sitter_moonbit.language()
  inspect!(language.name(), content="None")
  inspect!(language.abi_version(), content="14")
  assert_true!(language.abi_version() > 0)
  assert_true!(language.symbol_count() > 0)
}

// ///|
// test "language basics" {
//   // Test the basic properties of a language
//   let json_language : @tree_sitter.Language = @tree_sitter_json.language()
//   let moonbit_language : @tree_sitter.Language = @tree_sitter_moonbit.language()

//   // Check language names
//   let json_name = json_language.name()
//   let moonbit_name = moonbit_language.name()
//   inspect!(json_name is Some(_), content="true")
//   inspect!(moonbit_name is Some(_), content="true")

//   // Check symbol counts
//   let json_symbol_count = json_language.symbol_count()
//   let moonbit_symbol_count = moonbit_language.symbol_count()

//   // The exact counts may change with language updates, but they should be positive
//   // and reasonable numbers
//   inspect!(json_symbol_count > 0, content="true")
//   inspect!(moonbit_symbol_count > 0, content="true")

//   // Try getting a symbol name
//   let json_symbol_name = json_language.symbol_name(1)
//   inspect!(json_symbol_name is Some(_), content="true")
// }

// ///|
// test "language field counts and names" {
//   let json_language : @tree_sitter.Language = @tree_sitter_json.language()

//   // Check field count
//   let field_count = json_language.field_count()
//   inspect!(field_count >= 0, content="true") // Should be a reasonable number

//   // If there are fields, check a field name
//   if field_count > 0 {
//     let field_name = json_language.field_name_for_id(1)
//     if field_name is Some(name) {
//       // Test field id for name (reverse lookup)
//       let field_id = json_language.field_id_for_name(name)
//       inspect!(field_id >= 0, content="true")
//     }
//   }
// }

// ///|
// test "language metadata and version" {
//   let language : @tree_sitter.Language = @tree_sitter_json.language()

//   // Test ABI version
//   let abi_version = language.abi_version()
//   inspect!(abi_version > 0, content="true")

//   // Test metadata
//   let metadata = language.metadata()
//   inspect!(metadata.major_version() >= 0, content="true")
//   inspect!(metadata.minor_version() >= 0, content="true")
//   inspect!(metadata.patch_version() >= 0, content="true")
// }

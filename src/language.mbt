///|
pub(all) type Language @tree_sitter_language.Language

///|
/// Get another reference to the given language.
pub extern "c" fn Language::copy(self : Language) -> Language = "moonbit_ts_language_copy"

///|
/// Free any dynamically-allocated resources for this language, if
/// this is the last reference.
pub extern "c" fn Language::delete(self : Language) -> Unit = "moonbit_ts_language_delete"

///|
extern "c" fn Language::_symbol_count(self : Language) -> UInt = "moonbit_ts_language_symbol_count"

///|
/// Get the number of distinct node types in the language.
pub fn Language::symbol_count(self : Language) -> Int {
  uint_to_int(self._symbol_count())
}

///|
extern "c" fn Language::_state_count(self : Language) -> UInt = "moonbit_ts_language_state_count"

///|
/// Get the number of valid states in this language.
pub fn Language::state_count(self : Language) -> Int {
  uint_to_int(self._state_count())
}

///|
type Symbol UInt16

///|
/// Get the numerical id for the given node type string.
#borrow(name)
extern "c" fn Language::symbol_for_name_(
  self : Language,
  name : Bytes
) -> Symbol = "moonbit_ts_language_symbol_for_name"

///|
/// Get the numerical id for the given node type string.
pub fn Language::symbol_for_name(self : Language, name : String) -> Symbol {
  let name_bytes = @encoding.encode(UTF8, name)
  return Language::symbol_for_name_(self, name_bytes)
}

///|
type FieldId UInt16

///|
/// Get the number of distinct field names in the language.
extern "c" fn Language::field_count(self : Language) -> Int = "moonbit_ts_language_field_count"

///|
/// Get the field name string for the given numerical id.
extern "c" fn Language::_field_name_for_id(
  self : Language,
  id : FieldId
) -> @c.Pointer[Byte] = "moonbit_ts_language_field_name_for_id"

///|
fn decode_c_string(c_string : @c.Pointer[Byte], length? : Int) -> String? {
  if c_string.is_null() {
    return None
  }
  let buffer = @buffer.new()
  match length {
    None =>
      for i = 0; c_string[i] != 0; i = i + 1 {
        buffer.write_byte(c_string[i])
      }
    Some(length) =>
      for i = 0; i < length; i = i + 1 {
        buffer.write_byte(c_string[i])
      }
  }
  let name = buffer.contents()
  let name = @encoding.decoder(UTF8).decode_lossy(name)
  Some(name)
}

///|
pub fn Language::field_name_for_id(self : Language, id : FieldId) -> String? {
  let name = Language::_field_name_for_id(self, id)
  return decode_c_string(name)
}

///|
/// Get the numerical id for the given field name string.
#borrow(name)
extern "c" fn Language::_field_id_for_name(
  self : Language,
  name : Bytes
) -> UInt = "moonbit_ts_language_field_id_for_name"

///|
/// Get the numerical id for the given field name string.
pub fn Language::field_id_for_name(self : Language, name : String) -> Int {
  let name_bytes = @encoding.encode(UTF8, name)
  Language::_field_id_for_name(self, name_bytes) |> uint_to_int()
}

///|
/// Get a list of all supertype symbols for the language.
pub extern "c" fn Language::supertypes(self : Language) -> Array[Symbol] = "moonbit_ts_language_supertypes"

///|
/// Get a list of all subtype symbol ids for a given supertype symbol.
///
/// See `Language::supertypes` for fetching all supertype symbols.
pub extern "c" fn Language::subtypes(self : Language) -> Array[Symbol] = "moonbit_ts_language_subtypes"

///|
/// Get a node type string for the given numerical id.
extern "c" fn Language::symbol_name_(
  self : Language,
  symbol : Symbol
) -> @c.Pointer[Byte] = "moonbit_ts_language_symbol_name"

///|
/// Get a node type string for the given numerical id.
pub fn Language::symbol_name(self : Language, symbol : Symbol) -> String {
  let name_bytes = Language::symbol_name_(self, symbol)
  return decode_c_string(name_bytes).unwrap()
}

///|
/// Check whether the given node type id belongs to named nodes, anonymous nodes,
/// or a hidden nodes.
enum SymbolType {
  Regular
  Anonymous
  Supertype
  Auxiliary
}

///|
fn SymbolType::of_int(value : UInt) -> SymbolType {
  match value {
    0 => SymbolType::Regular
    1 => SymbolType::Anonymous
    2 => SymbolType::Supertype
    3 => SymbolType::Auxiliary
    value => abort("Invalid SymbolType: \{value}")
  }
}

///|
fn SymbolType::to_int(self : SymbolType) -> UInt {
  match self {
    SymbolType::Regular => 0
    SymbolType::Anonymous => 1
    SymbolType::Supertype => 2
    SymbolType::Auxiliary => 3
  }
}

///|
extern "c" fn Language::symbol_type_(self : Language, symbol : Symbol) -> UInt = "moonbit_ts_language_symbol_type"

///|
/// Check whether the given node type id belongs to named nodes, anonymous nodes,
/// or a hidden nodes.
///
/// See also `Node::is_named`. Hidden nodes are never returned from the API.
pub fn Language::symbol_type(self : Language, symbol : Symbol) -> SymbolType {
  return SymbolType::of_int(Language::symbol_type_(self, symbol))
}

///|
extern "c" fn Language::_version(self : Language) -> UInt = "moonbit_ts_language_version"

///|
/// Get the ABI version number for this language. This version number is used
/// to ensure that languages were generated by a compatible version of
/// Tree-sitter.
///
/// See also `Parser::set_language`.
#deprecated("Use `Language::abi_version` instead")
pub fn Language::version(self : Language) -> Int {
  uint_to_int(self._version())
}

///|
extern "c" fn Language::_abi_version(self : Language) -> UInt = "moonbit_ts_language_abi_version"

///|
/// Get the ABI version number for this language. This version number is used
/// to ensure that languages were generated by a compatible version of
/// Tree-sitter.
///
/// See also `Parser::set_language`.
pub fn Language::abi_version(self : Language) -> Int {
  uint_to_int(self._abi_version())
}

///|
/// The metadata associated with a language.
///
/// Currently, this metadata can be used to check the [Semantic Version](https://semver.org/)
/// of the language. This version information should be used to signal if a given parser might
/// be incompatible with existing queries when upgrading between major versions, or minor versions
/// if it's in zerover.
type LanguageMetadata Bytes

///|
pub fn LanguageMetadata::major_version(self : LanguageMetadata) -> Byte {
  self._[0]
}

///|
pub fn LanguageMetadata::minor_version(self : LanguageMetadata) -> Byte {
  self._[1]
}

///|
pub fn LanguageMetadata::patch_version(self : LanguageMetadata) -> Byte {
  self._[2]
}

///|
/// Get the metadata for this language. This information is generated by the
/// CLI, and relies on the language author providing the correct metadata in
/// the language's `tree-sitter.json` file.
///
/// See also `LanguageMetadata`.
pub extern "c" fn Language::metadata(self : Language) -> LanguageMetadata = "moonbit_ts_language_metadata"

///|
type StateId UInt16

///|
/// Get the next parse state. Combine this with lookahead iterators to generate
/// completion suggestions or valid symbols in error nodes. Use
/// `Node::grammar_symbol` for valid symbols.
pub extern "c" fn Language::next_state(
  self : Language,
  state : StateId,
  symbol : Symbol
) -> StateId = "moonbit_ts_language_next_state"

///|
extern "c" fn Language::_name(
  self : @tree_sitter_language.Language
) -> @c.Pointer[Byte] = "moonbit_ts_language_name"

///|
/// Get the name of this language. This returns `None` in older parsers.
pub fn Language::name(self : Language) -> String? {
  let name = Language::_name(self._)
  return decode_c_string(name)
}

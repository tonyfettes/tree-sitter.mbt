///|
extern type Language

///|
extern "c" fn Language::_load(
  pathname : Bytes,
  symbol : Bytes
) -> Nullable[Language] = "moonbit_ts_language_load"

///|
pub fn Language::load(path : String, name : String) -> Language? {
  let pathname = @buffer.new()
  pathname.write_bytes(@encoding.encode(UTF8, path))
  pathname.write_byte(0)
  let symbol = @buffer.new()
  symbol.write_bytes(b"tree_sitter_")
  symbol.write_bytes(@encoding.encode(UTF8, name))
  symbol.write_byte(0)
  Language::_load(pathname.contents(), symbol.contents()).to()
}

///|
pub extern "c" fn Language::copy(self : Language) -> Language = "moonbit_ts_language_copy"

///|
pub extern "c" fn Language::delete(self : Language) -> Unit = "moonbit_ts_language_delete"

///|
pub extern "c" fn Language::symbol_count(self : Language) -> UInt = "moonbit_ts_language_symbol_count"

///|
pub extern "c" fn Language::state_count(self : Language) -> UInt = "moonbit_ts_language_state_count"

///|
type Symbol UInt16

///|
extern "c" fn Language::symbol_for_name_(
  self : Language,
  name : Bytes
) -> Symbol = "moonbit_ts_language_symbol_for_name"

///|
pub fn Language::symbol_for_name(self : Language, name : String) -> Symbol {
  let name_bytes = @encoding.encode(UTF8, name)
  return Language::symbol_for_name_(self, name_bytes)
}

///|
type FieldId UInt16

///|
extern "c" fn Language::field_count(self : Language) -> Int = "moonbit_ts_language_field_count"

///|
extern "c" fn Language::field_name_for_id(
  self : Language,
  id : FieldId
) -> Bytes = "moonbit_ts_language_field_name_for_id"

///|
extern "c" fn Language::_field_id_for_name(
  self : Language,
  name : Bytes
) -> UInt = "moonbit_ts_language_field_id_for_name"

///|
pub fn Language::field_id_for_name(self : Language, name : String) -> UInt {
  let name_bytes = @encoding.encode(UTF8, name)
  return Language::_field_id_for_name(self, name_bytes)
}

///|
pub extern "c" fn Language::supertypes(self : Language) -> Array[Symbol] = "moonbit_ts_language_supertypes"

///|
pub extern "c" fn Language::subtypes(self : Language) -> Array[Symbol] = "moonbit_ts_language_subtypes"

///|
extern "c" fn Language::symbol_name_(self : Language, symbol : Symbol) -> Bytes = "moonbit_ts_language_symbol_name"

///|
pub fn Language::symbol_name(self : Language, symbol : Symbol) -> String {
  let name_bytes = Language::symbol_name_(self, symbol)
  return @encoding.decode_lossy(UTF8, name_bytes).to_string()
}

///|
enum SymbolType {
  Regular
  Anonymous
  Supertype
  Auxiliary
}

///|
pub fn SymbolType::of_int(value : Int) -> SymbolType {
  match value {
    0 => SymbolType::Regular
    1 => SymbolType::Anonymous
    2 => SymbolType::Supertype
    3 => SymbolType::Auxiliary
    value => abort("Invalid SymbolType: \{value}")
  }
}

///|
pub fn SymbolType::to_int(self : SymbolType) -> Int {
  match self {
    SymbolType::Regular => 0
    SymbolType::Anonymous => 1
    SymbolType::Supertype => 2
    SymbolType::Auxiliary => 3
  }
}

///|
pub extern "c" fn Language::symbol_type(
  self : Language,
  symbol : Symbol
) -> SymbolType = "moonbit_ts_language_symbol_type"

///|
pub extern "c" fn Language::version(self : Language) -> UInt = "moonbit_ts_language_version"

///|
pub extern "c" fn Language::abi_version(self : Language) -> UInt = "moonbit_ts_language_abi_version"

///|
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
extern "c" fn Language::metadata(self : Language) -> LanguageMetadata = "moonbit_ts_language_metadata"

///|
type StateId UInt16

///|
extern "c" fn Language::next_state(
  self : Language,
  state : StateId,
  symbol : Symbol
) -> StateId = "moonbit_ts_language_next_state"

///|
fn Language::name_(self : Language) -> Bytes = "moonbit_ts_language_name"

///|
pub fn Language::name(self : Language) -> String {
  let name_bytes = Language::name_(self)
  return @encoding.decode_lossy(UTF8, name_bytes).to_string()
}

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
extern "c" fn Language::field_count(self : Language) -> Int = "moonbit_ts_language_field_count"

///|
type FieldId UInt16

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
  let name_bytes = string_to_ntbs(name)
  return Language::_field_id_for_name(self, name_bytes)
}

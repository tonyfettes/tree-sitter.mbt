///|
extern "c" fn moonbit_ffi_make_closure(
  code : Nullable[Unit],
  data : Nullable[Unit]
) -> Nullable[Unit] = "moonbit_ffi_make_closure"

///|
fn init {
  ignore(moonbit_ffi_make_closure)
}

///|
priv extern type Nullable[_]

///|
fn Nullable::some[T](value : T) -> Nullable[T] = "%identity"

///|
fn Nullable::of[T](option : T?) -> Nullable[T] {
  match option {
    Some(value) => Nullable::some(value)
    None => Nullable::none()
  }
}

///|
fn Nullable::cast[T, U](self : Nullable[T]) -> Nullable[U] = "%identity"

///|
extern "c" fn Nullable::null() -> Nullable[Unit] = "moonbit_c_null"

///|
fn Nullable::none[T]() -> Nullable[T] {
  Nullable::null().cast()
}

///|
fn Nullable::unwrap[T](self : Nullable[T]) -> T = "%identity"

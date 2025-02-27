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
extern "c" fn Nullable::is_null(self : Nullable[Unit]) -> Bool = "moonbit_c_is_null"

///|
fn Nullable::none[T]() -> Nullable[T] {
  Nullable::null().cast()
}

///|
fn Nullable::is_none[T](self : Nullable[T]) -> Bool {
  self.cast().is_null()
}

///|
fn Nullable::unwrap[T](self : Nullable[T]) -> T = "%identity"

///|
fn Nullable::to[T](self : Nullable[T]) -> T? {
  if self.is_none() {
    None
  } else {
    Some(self.unwrap())
  }
}

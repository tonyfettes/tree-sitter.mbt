///|
fn async_run(f : () -> Unit!Async) -> Unit = "%async.run"

///|
pub fn start(f : () -> Unit!Async + Error) -> Unit!Error {
  let uv = @uv.Loop::new!()
  let mut error = None
  async_run(fn() {
    try {
      f!()
    } catch {
      e => error = Some(e)
    }
  })
  uv.run!(Default)
  uv.stop()
  uv.close!()
  if error is Some(error) {
    raise error
  }
}

///|
let moonbit_value : Ref[@pattern.Language?] = Ref::new(None)

///|
fn moonbit() -> @pattern.Language!Async + Error {
  if moonbit_value.val is Some(parser) {
    return parser
  }
  let contexts : Map[String, @pattern.Context] = {
    "exp": @pattern.Context::new!(
      #|fn main {
      #|  $
      #|}
      ,
      strip=true,
      selector=
        #|(structure
        #| (structure_item
        #|  (function_definition
        #|   (block_expression
        #|    "{"
        #|    (statement_expression
        #|     (_) @exp)
        #|    "}"))))
      ,
    ),
    "top": @pattern.Context::new!(
      "$",
      selector=
        #|(structure_item) @top
      ,
    ),
    "pat": @pattern.Context::new!(
      #|fn main {
      #|  match x {
      #|    $ => y
      #|  }
      #|}
      ,
      selector=
        #|(pattern)
      ,
    ),
    "ty": @pattern.Context::new!(
      #|let x : $ = 42
      ,
      selector=
        #|(type)
      ,
    ),
    "case": @pattern.Context::new!(
      #|fn main {
      #|  match x {
      #|    $
      #|  }
      #|}
      ,
      selector=
        #|(case_clause) @case
      ,
    ),
    "matrix": @pattern.Context::new!(
      #|fn main {
      #|  loop a, b {
      #|    $
      #|  }
      #|}
      ,
      selector=
        #|(matrix_case_clause) @matrix
      ,
    ),
  }
  let entries : Map[String, @pattern.Entry] = {
    "exp": @pattern.Entry::new(
      matches=
        #|[
        #|  (expression)
        #|  (pipeline_expression)
        #|  (compound_expression)
        #|  (match_expression)
        #|  (named_matrix_expression)
        #|  (guard_expression)
        #|  (statement_expression)
        #|  (simple_expression)
        #|] @exp
      ,
      placeholder="{ ... }",
    ),
    "top": @pattern.Entry::new(
      matches=
        #|[
        #|  (structure_item)
        #|] @top
      ,
      placeholder=
        #|type! A Int
      ,
    ),
    "pat": @pattern.Entry::new(
      matches=
        #|[
        #|  (pattern)
        #|  (simple_pattern)
        #|] @pat
      ,
      placeholder="_",
    ),
    "id": @pattern.Entry::new(
      matches=
        #|[
        #|  (identifier)
        #|  (lowercase_identifier)
        #|  (uppercase_identifier)
        #|  (qualified_identifier)
        #|  (constructor_expression)
        #|] @id
      ,
      placeholder="id",
    ),
    "ty": @pattern.Entry::new(
      matches=
        #|[
        #|  (type)
        #|  (return_type)
        #|] @ty
      ,
      placeholder="A",
    ),
  }
  let extras = ["semicolon"]
  let language : @tree_sitter_language.Language = @tree_sitter_moonbit.language()
  let parser = @pattern.Language::new(language, contexts~, entries~, extras~)
  moonbit_value.val = Some(parser)
  return parser
}

///|
struct Location {
  name : @string.View
  path : String
  start : @tree_sitter.Point
  end : @tree_sitter.Point
  text : @string.View
}

///|
pub impl ToJson for Location with to_json(self : Location) -> Json {
  let start : Json = {
    "row": self.start.row().to_json(),
    "column": self.start.column().to_json(),
  }
  let end : Json = {
    "row": self.end.row().to_json(),
    "column": self.end.column().to_json(),
  }
  return {
    "path": self.path.to_json(),
    "name": self.name.to_json(),
    "start": start,
    "end": end,
    "text": self.text.to_json(),
  }
}

///|
fn read_to(
  uv : @uv.Loop,
  file : @uv.File,
  decoder : @encoding.Decoder,
  buffer : StringBuilder,
  on_read : () -> Unit,
  on_error : (Error) -> Unit
) -> Unit {
  let bytes = Bytes::make(1024, 0)
  try {
    uv.fs_read!(
      file,
      [bytes],
      fn(_, count) {
        if count == 0 {
          try {
            uv.fs_close!(file, fn(_) {  })
          } catch {
            e => on_error(e)
          }
          on_read()
          return
        }
        try {
          decoder.decode_to!(bytes[:count], buffer, stream=true)
          read_to(uv, file, decoder, buffer, on_read, on_error)
        } catch {
          e => on_error(e)
        }
      },
      fn(_, e) { on_error(e) },
    )
  } catch {
    e => on_error(e)
  }
}

///|
fn read_path(
  uv : @uv.Loop,
  path : String,
  on_read : (String) -> Unit,
  on_error : (Error) -> Unit
) -> Unit {
  let decoder = @encoding.decoder(@encoding.UTF8)
  let content = StringBuilder::new()
  try {
    uv.fs_open!(
      path,
      @uv.OpenFlags::read(),
      0o644,
      fn(_, file) {
        read_to(
          uv,
          file,
          decoder,
          content,
          fn() {
            let content = content.to_string()
            on_read(content)
          },
          on_error,
        )
      },
      fn(_, e) { on_error(e) },
    )
  } catch {
    e => on_error(e)
  }
}

///|
fn walk_directory(
  uv : @uv.Loop,
  path : String,
  on_file : (String) -> Unit,
  on_error : (Error) -> Unit
) -> Unit {
  try {
    uv.fs_stat!(
      path,
      fn(_, stat) {
        if stat.is_file() {
          on_file(path)
          return
        } else if stat.is_directory() {
          try {
            uv.fs_scandir!(
              path,
              0,
              fn(req) {
                while true {
                  let dirent = try {
                    @uv.fs_scandir_next!(req)
                  } catch {
                    @uv.Errno(EOF) => break
                    e => {
                      on_error(e)
                      break
                    }
                  }
                  let name = dirent.name()
                  if name == ".mooncakes" || name == "target" {
                    continue
                  }
                  let path = "\{path}/\{name}"
                  match dirent.type_() {
                    Dir => walk_directory(uv, path, on_file, on_error)
                    File => on_file(path)
                    _ => ()
                  }
                }
              },
              fn(_, e) { on_error(e) },
            )
          } catch {
            e => on_error(e)
          }
        }
      },
      fn(_, e) { on_error(e) },
    )
  } catch {
    e => on_error(e)
  }
}

///|
fn search(
  path : String,
  content~ : String,
  query~ : @pattern.Query,
  on_found : (Location) -> Unit,
  on_error : (Error) -> Unit
) -> Unit {
  try {
    let matches = query.search!(content)
    for matched in matches {
      for name, nodes in matched {
        for node in nodes {
          on_found(Location::{
            name,
            path,
            start: node.start_point(),
            end: node.end_point(),
            text: content.view(
              start_offset=node.start_byte(),
              end_offset=node.end_byte(),
            ),
          })
        }
      }
    }
  } catch {
    e => on_error(e)
  }
}

///|
fn async_run(f : () -> Unit!Async) -> Unit = "%async.run"

///|
fn start(path~ : String, query~ : String) -> Unit! {
  fn send_error(error : Error) {
    let message : Json = { "error": error.to_string().to_json() }
    println(message.stringify())
  }

  let uv = @uv.Loop::new!()
  async_run(fn() {
    try {
      let language = moonbit!()
      let query = language.compile!(query)
      walk_directory(
        uv,
        path,
        fn(file) {
          if not(file.has_suffix(".mbt")) {
            return
          }
          read_path(
            uv,
            file,
            fn(content) {
              search(
                file,
                content~,
                query~,
                fn(location) { println(location.to_json().stringify()) },
                send_error,
              )
            },
            send_error,
          )
        },
        send_error,
      )
    } catch {
      e => send_error(e)
    }
  })
  uv.run!(Default) |> ignore()
  uv.stop()
  uv.close!()
}

///|
fn help(exec : @string.View) -> String {
  $|Usage: \{exec} <query> [path]
}

///|
fn main {
  try {
    let args = @uv.args()
    match args {
      [] => abort("No arguments provided")
      [exec] => println(help(exec))
      [_, query] => start!(path=@uv.cwd!(), query~)
      [_, query, path] => start!(path~, query~)
      [exec, ..] => println(help(exec))
    }
  } catch {
    e => println("Error: \{e}")
  }
}

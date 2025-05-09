///|
let moonbit_parser_value : Ref[@query_language.Parser?] = Ref::new(None)

///|
let moonbit_language : @tree_sitter_language.Language = @tree_sitter_moonbit.language()

///|
fn moonbit_parser() -> @query_language.Parser!Async + Error {
  if moonbit_parser_value.val is Some(parser) {
    return parser
  }
  let language = @tree_sitter.Language::load!(moonbit_language)
  let contexts : Map[String, @query_language.Context] = {
    "exp": @query_language.Context::new!(
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
    "top": @query_language.Context::new!(
      "$",
      selector=
        #|(structure_item) @top
      ,
    ),
    "pat": @query_language.Context::new!(
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
    "ty": @query_language.Context::new!(
      #|let x : $ = 42
      ,
      selector=
        #|(type)
      ,
    ),
    "case": @query_language.Context::new!(
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
    "matrix": @query_language.Context::new!(
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
  let entries : Map[String, @query_language.Entry] = {
    "exp": @query_language.Entry::new(
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
    "top": @query_language.Entry::new(
      matches=
        #|[
        #|  (structure_item)
        #|] @top
      ,
      placeholder=
        #|type! A Int
      ,
    ),
    "pat": @query_language.Entry::new(
      matches=
        #|[
        #|  (pattern)
        #|  (simple_pattern)
        #|] @pat
      ,
      placeholder="_",
    ),
    "id": @query_language.Entry::new(
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
    "ty": @query_language.Entry::new(
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
  let parser = @query_language.Parser::new(
    language,
    contexts~,
    entries~,
    extras~,
  )
  moonbit_parser_value.val = Some(parser)
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
  parser~ : @tree_sitter.Parser,
  content~ : String,
  query~ : String,
  on_found : (Location) -> Unit,
  on_error : (Error) -> Unit
) -> Unit {
  try {
    let tree = parser.parse_string!(content)
    let query_cursor = tree.query!(query)
    for capture in query_cursor.captures() {
      let name = capture.name()
      let node = capture.node()
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
      let parser = moonbit_parser!()
      let query = parser.parse!(query)
      let parser = parser.parser()
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
                parser~,
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

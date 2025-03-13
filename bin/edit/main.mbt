///|
struct Edit {
  name : String
  search : String
  replace : String
}

///|
fn main {
  try {
    let args = @sys.get_cli_args()
    guard args is [_, source_path] else {
      println("Usage: \{args[0]} <source_path>")
      return
    }
    let mut source = @fs.read_file_to_bytes!(source_path)
    let language = @tree_sitter_moonbit.language()
    let parser = @tree_sitter.Parser::new()
    parser.set_language(language)
    let edits : Array[Edit] = [
      {
        name: "trivially-true",
        search: #|((binary_expression (_) @left "==" (_) @right)
        #| (#eq? @left @right))
        ,
        replace: "true",
      },
      {
        name: "if-true",
        search: #|(if_expression (block_expression (_) @body))
        ,
        replace: #|@body
        ,
      },
    ]
    for edit in edits {
      while true {
        let source_tree = parser.parse_bytes(
          None,
          source,
          encoding=@tree_sitter.InputEncoding::UTF8,
        )
        let source_root = source_tree.root_node()
        let search = edit.search
        let query = @tree_sitter.Query::new!(
          language,
          search + " @\{edit.name}",
        )
        let query_cursor = @tree_sitter.QueryCursor::new()
        query_cursor.exec(query, source_root)
        guard query_cursor.next_match() is Some(match_) else { break }
        let captures_nodes = {}
        let captures_texts = {}
        for capture in match_.captures {
          let node = capture.node
          let bytes = source[node.start_byte():node.end_byte()]
          let text = @encoding.decoder(UTF8).decode!([..bytes])
          captures_nodes[query.capture_name_for_id(capture.index)] = node
          captures_texts[query.capture_name_for_id(capture.index)] = text
        }
        let buffer = StringBuilder::new()
        replace~: loop edit.replace[:] {
          ['@', .. replace] => {
            let name = StringBuilder::new()
            name~: loop replace {
              [char, .. replace] =>
                if char.is_ascii_alphabetic() {
                  name.write_char(char)
                  continue name~ replace
                } else {
                  match captures_texts[name.to_string()] {
                    Some(value) => {
                      buffer.write_string(value)
                      continue replace~ replace
                    }
                    None => {
                      println("Error: unknown capture: \{name}")
                      @sys.exit(1)
                    }
                  }
                }
              replace => {
                match captures_texts[name.to_string()] {
                  Some(value) => {
                    buffer.write_string(value)
                    continue replace~ replace
                  }
                  None => {
                    println("Error: unknown capture: \{name}")
                    @sys.exit(1)
                  }
                }
                continue replace~ replace
              }
            }
          }
          [char, .. replace] => {
            buffer.write_char(char)
            continue replace~ replace
          }
          [] => break
        }
        guard captures_nodes[edit.name] is Some(node) else {
          println("Error: unknown capture: \{edit.name}")
          @sys.exit(1)
        }
        let start = node.start_byte()
        let end = node.end_byte()
        let replace = @encoding.encode(UTF8, buffer.to_string())
        source = [..source[:start], ..replace, ..source[end:]]
      }
    }
    println(@encoding.decoder(UTF8).decode!(source))
  } catch {
    error => println("Error: \{error}")
  }
}

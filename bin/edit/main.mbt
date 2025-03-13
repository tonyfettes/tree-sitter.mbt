///|
struct Edit {
  name : String
  search : String
  replace : String
} derive(Show)

///|
fn parse_rules(source : Bytes) -> Array[Edit]! {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_yaml.language()
  parser.set_language(language)
  let source_tree = parser.parse_bytes(
    None,
    source,
    encoding=@tree_sitter.InputEncoding::UTF8,
  )
  let source_root = source_tree.root_node()
  let query_source =
    #|(block_mapping_pair
    #| key: (_) @name
    #| value:
    #| (block_node
    #|  (block_mapping
    #|   (block_mapping_pair
    #|    key: (_) @_search
    #|    value: (_) @search)
    #|   (#eq? @_search "search")
    #|   (block_mapping_pair
    #|    key: (_) @_replace
    #|    value: (_) @replace)
    #|   (#eq? @_replace "replace"))))
  let query = @tree_sitter.Query::new!(language, query_source)
  let query_cursor = @tree_sitter.QueryCursor::new()
  query_cursor.exec(query, source_root)
  let edits : Array[Edit] = []
  while true {
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
    guard captures_texts["name"] is Some(name) else {
      println("Error: missing name")
      @sys.exit(1)
    }
    guard captures_texts["search"] is Some(search) else {
      println("Error: missing search")
      @sys.exit(1)
    }
    let search : String = match search.trim_space() {
      ['|', '\n', .. search] => [..search]
      search => search
    }
    guard captures_texts["replace"] is Some(replace) else {
      println("Error: missing replace")
      @sys.exit(1)
    }
    let replace : String = match replace.trim_space() {
      ['|', '\n', .. replace] => [..replace]
      replace => replace
    }
    edits.push(Edit::{
      name,
      search: search.trim_space(),
      replace: replace.trim_space(),
    })
  }
  return edits
}

///|
fn main {
  try {
    let args = @sys.get_cli_args()
    guard args is [_, ruleset_path, source_path] else {
      println("Usage: \{args[0]} <ruleset_path> <source_path>")
      return
    }
    let ruleset = @fs.read_file_to_bytes!(ruleset_path)
    let edits = parse_rules!(ruleset)
    let mut source = @fs.read_file_to_bytes!(source_path)
    let language = @tree_sitter_moonbit.language()
    let parser = @tree_sitter.Parser::new()
    parser.set_language(language)
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

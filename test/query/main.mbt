///|
fn main {
  try {
    let args = @sys.get_cli_args()
    guard args is [_, json_path, query_path, source_path] else {
      println("Usage: parse_json <path> <query> <source>")
      return
    }
    guard @ts.Language::load(json_path, "json") is Some(json) else {
      println("Failed to load language")
      return
    }
    let source = @fs.read_file_to_string!(source_path)
    let query = @fs.read_file_to_string!(query_path)
    let parser = @ts.Parser::new()
    parser.set_language(json)
    let tree = parser.parse_string(None, source)
    let root_node = tree.root_node()
    println("Syntax tree: \{root_node.string()}")
    let query = @ts.Query::new!(json, query)
    let cursor = @ts.QueryCursor::new()
    cursor.exec(query, root_node)
    while cursor.next_match() is Some(match_) {
      println("Matched query at: \{match_.captures[0].node.string()}")
    }
    cursor.delete()
    tree.delete()
    parser.delete()
  } catch {
    error => println("Error: \{error}")
  }
}

///|
fn main {
  try {
    let args = @sys.get_cli_args()
    guard args is [_, lang_path, lang, source_path] else {
      println("Usage: parse <path> <lang> <source>")
      return
    }
    guard @ts.Language::load(lang_path, lang) is Some(lang) else {
      println("Failed to load language")
      return
    }
    let source = @fs.read_file_to_string!(source_path)
    let parser = @ts.Parser::new()
    parser.set_language(lang)
    let tree = parser.parse_string(None, source)
    let root_node = tree.root_node()
    println("Syntax tree: \{root_node.string()}")
    tree.delete()
    parser.delete()
  } catch {
    error => println("Error: \{error}")
  }
}

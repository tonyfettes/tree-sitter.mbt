///|
fn main {
  try {
    let args = @sys.get_cli_args()
    if args.length() != 5 {
      #|Usage: multi_lang <erb> <html> <ruby> <text>
      #|  Parse a text file containing ERB, HTML, and Ruby code.
      |> println()
      return
    }
    guard @ts.Language::load(args[1], "embedded_template") is Some(erb) &&
      @ts.Language::load(args[2], "html") is Some(html) &&
      @ts.Language::load(args[3], "ruby") is Some(ruby) else {
      println("Failed to load language")
      return
    }
    let text = @fs.read_file_to_string!(args[4])
    let parser = @ts.Parser::new()
    parser.set_language(erb)
    let erb_tree = parser.parse_string(None, text)
    let erb_root_node = erb_tree.root_node()
    let html_ranges = []
    let ruby_ranges = []
    let child_count = erb_root_node.child_count()
    for i in 0..<child_count {
      let node = erb_root_node.child(i).unwrap()
      let type_ = node.type_()
      if type_ == "content" {
        html_ranges.push(
          @ts.Range::new(
            node.start_point(),
            node.end_point(),
            node.start_byte(),
            node.end_byte(),
          ),
        )
      } else {
        let code_node = node.named_child(0).unwrap()
        ruby_ranges.push(
          @ts.Range::new(
            code_node.start_point(),
            code_node.end_point(),
            code_node.start_byte(),
            code_node.end_byte(),
          ),
        )
      }
    }
    parser.set_language(html)
    parser.set_included_ranges(html_ranges)
    let html_tree = parser.parse_string(None, text)
    let html_root_node = html_tree.root_node()
    parser.set_language(ruby)
    parser.set_included_ranges(ruby_ranges)
    let ruby_tree = parser.parse_string(None, text)
    let ruby_root_node = ruby_tree.root_node()
    let erb_sexp = erb_root_node.string()
    let html_sexp = html_root_node.string()
    let ruby_sexp = ruby_root_node.string()
    println("ERB: \{erb_sexp}")
    println("HTML: \{html_sexp}")
    println("Ruby: \{ruby_sexp}")
    ruby_tree.delete()
    html_tree.delete()
    erb_tree.delete()
    parser.delete()
  } catch {
    error => println("Error: \{error}")
  }
}

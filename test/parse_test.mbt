///|
test "json" {
  let json = @tree_sitter_json.language()
  let parser = @tree_sitter.Parser::new()
  parser.set_language(json)
  let source =
    #|{
    #|  "name": "John Doe",
    #|  "age": 43
    #|}
  let tree = parser.parse_string(None, source)
  let root_node = tree.root_node()
  inspect!(
    root_node.string(),
    content="(document (object (pair key: (string (string_content)) value: (string (string_content))) (pair key: (string (string_content)) value: (number))))",
  )
  let root_sexp = @sexp.parse!(root_node.string())
  @json.inspect!(root_sexp, content=[
    [
      "document",
      [
        "object",
        [
          "pair",
          { "key": ["string", ["string_content"]] },
          { "value": ["string", ["string_content"]] },
        ],
        [
          "pair",
          { "key": ["string", ["string_content"]] },
          { "value": ["number"] },
        ],
      ],
    ],
  ])
  let root_node_first_child = root_node.child(0).map(@tree_sitter.Node::string)
  inspect!(
    root_node_first_child,
    content=
      #|Some("(object (pair key: (string (string_content)) value: (string (string_content))) (pair key: (string (string_content)) value: (number)))")
    ,
  )
}

///|
test "moonbit" {
  let moonbit = @tree_sitter_moonbit.language()
  let parser = @tree_sitter.Parser::new()
  parser.set_language(moonbit)
  let source =
    #|fn main {
    #|  println("Hello, World!")
    #|}
    #|
    #|/// # Heading
    #|///
    #|/// Paragraph with *italic* and **bold** text.
    #|fn fib(a : Int) -> Int {
    #|  if a < 2 {
    #|    a
    #|  } else {
    #|    fib(a - 1) + fib(a - 2)
    #|  }
    #|}
  let tree = parser.parse_string(None, source)
  let root_node = tree.root_node()
  let comment_document = []
  let query = @tree_sitter.Query::new!(moonbit, "(comment) @comment")
  let cursor = @tree_sitter.QueryCursor::new()
  cursor.exec(query, root_node)
  while cursor.next_match() is Some(match_) {
    let comment_node = match_.captures[0].node
    let start_byte = comment_node.start_byte().reinterpret_as_int()
    let end_byte = comment_node.end_byte().reinterpret_as_int()
    let comment = source[start_byte:end_byte]
    match comment {
      [.. "/// ", .. comment_content] =>
        comment_document.push(comment_content.to_string())
      [.. "///"] => comment_document.push("")
      _ => continue
    }
  }
  let comment_document = comment_document.join("\n")
  inspect!(
    comment_document.to_string(),
    content=
      #|# Heading
      #|
      #|Paragraph with *italic* and **bold** text.
    ,
  )
  parser.set_language(@tree_sitter_markdown.language())
  let markdown_tree = parser.parse_string(None, comment_document.to_string())
  let markdown_root_node = markdown_tree.root_node()
  inspect!(
    markdown_root_node,
    content="(document (section (atx_heading (atx_h1_marker) heading_content: (inline)) (paragraph (inline))))",
  )
}

///|
test "markdown" {
  let moonbit = @tree_sitter_moonbit.language()
  let markdown = @tree_sitter_markdown.language()
  let parser = @tree_sitter.Parser::new()
  parser.set_language(markdown)
  let source =
    #|# Heading
    #|
    #|Paragraph with *italic* and **bold** text.
    #|
    #|```moonbit
    #|fn main {
    #|  println("Hello, World!")
    #|}
    #|```
  let tree = parser.parse_string(None, source)
  let root_node = tree.root_node()
  let root_sexp = @sexp.parse!(root_node.string())
  guard root_node.children().collect() is [document]
  guard document.children().collect() is [_, _, fenced_code_block]
  let moonbit_ranges = []
  for node in fenced_code_block.children() {
    if node.type_() == "code_fence_content" {
      let node_range = @tree_sitter.Range::new(
        node.start_point(),
        node.end_point(),
        node.start_byte(),
        node.end_byte(),
      )
      moonbit_ranges.push(node_range)
    } else {
      continue
    }
  }
  guard not(moonbit_ranges.is_empty())
  parser.set_language(moonbit)
  parser.set_included_ranges(moonbit_ranges)
  let moonbit_tree = parser.parse_string(None, source)
  let moonbit_root_node = moonbit_tree.root_node()
  inspect!(
    @sexp.parse!(moonbit_root_node.string()),
    content="(structure (structure_item (function_definition (function_identifier (lowercase_identifier)) (block_expression (statement_expression (expression (pipeline_expression (compound_expression (simple_expression (apply_expression (simple_expression (qualified_identifier (lowercase_identifier))) (argument (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment)))))))))))))))) (semicolon (automatic_semicolon))))) (semicolon (automatic_semicolon)) (ERROR (UNEXPECTED '`')))",
  )
  @json.inspect!(root_sexp, content=[
    [
      "document",
      [
        "section",
        ["atx_heading", ["atx_h1_marker"], { "heading_content": ["inline"] }],
        ["paragraph", ["inline"]],
        [
          "fenced_code_block",
          ["fenced_code_block_delimiter"],
          ["info_string", ["language"]],
          ["block_continuation"],
          [
            "code_fence_content",
            ["block_continuation"],
            ["block_continuation"],
            ["block_continuation"],
          ],
        ],
      ],
    ],
  ])
}

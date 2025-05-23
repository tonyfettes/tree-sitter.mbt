///|
test "c" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_c.language()
  parser.set_language(language)
}

///|
test "cpp" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_cpp.language()
  parser.set_language(language)
}

///|
test "css" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_css.language()
  parser.set_language(language)
}

///|
test "flow" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_flow.language()
  parser.set_language(language)
}

///|
test "go" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_go.language()
  parser.set_language(language)
}

///|
test "html" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_html.language()
  parser.set_language(language)
}

///|
test "java" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_java.language()
  parser.set_language(language)
}

///|
test "javascript" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_javascript.language()
  parser.set_language(language)
}

///|
test "json" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_json.language()
  parser.set_language(language)
}

///|
test "markdown" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_markdown.language()
  parser.set_language(language)
}

///|
test "markdown_inline" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_markdown_inline.language()
  parser.set_language(language)
}

///|
test "moonbit" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_moonbit.language()
  parser.set_language(language)
}

///|
test "ocaml" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_ocaml.language()
  parser.set_language(language)
}

///|
test "ocaml_interface" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_ocaml_interface.language()
  parser.set_language(language)
}

///|
test "ocaml_type" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_ocaml_type.language()
  parser.set_language(language)
}

///|
test "python" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_python.language()
  parser.set_language(language)
}

///|
test "query" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_query.language()
  parser.set_language(language)
}

///|
test "rust" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_rust.language()
  parser.set_language(language)
}

///|
test "tsx" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_tsx.language()
  parser.set_language(language)
}

///|
test "typescript" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_typescript.language()
  parser.set_language(language)
}

///|
test "yaml" {
  let parser = @tree_sitter.Parser::new()
  let language = @tree_sitter_yaml.language()
  parser.set_language(language)
}

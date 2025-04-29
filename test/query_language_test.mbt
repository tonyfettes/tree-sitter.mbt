///|
let moonbit_parser_value : Ref[@query_language.Parser?] = Ref::new(None)

///|
let moonbit_language : @tree_sitter.Language = @tree_sitter_moonbit.language()

///|
fn moonbit_parser() -> @query_language.Parser! {
  if moonbit_parser_value.val is Some(parser) {
    return parser
  }
  let contexts : Map[String, @query_language.Context] = {
    "exp": @query_language.Context::new!(
      #|fn main {
      #|  $
      #|}
      ,
      selector=
        #|(structure
        #| (structure_item
        #|  (function_definition
        #|   (block_expression
        #|    "{" (_) @exp "}"))))
      ,
    ),
    "top": @query_language.Context::new!(
      "$",
      selector=
        #|(structure_item)
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
  }
  let entries : Map[String, @query_language.Entry] = {
    "exp": @query_language.Entry::new(
      matches=
        #|[
        #|  (pipeline_expression)
        #|  (compound_expression)
        #|  (match_expression)
        #|  (expression)
        #|] @exp
      ,
      placeholder=
        #|{ ... }
      ,
    ),
    "top": @query_language.Entry::new(
      matches=
        #|[
        #|  (structure_item)
        #|]
      ,
      placeholder=
        #|fn main {
        #|}
      ,
    ),
    "pat": @query_language.Entry::new(
      matches=
        #|[
        #|  (pattern)
        #|]
      ,
      placeholder=
        #|_
      ,
    ),
    "id": @query_language.Entry::new(
      matches=
        #|[
        #|  (identifier)
        #|  (lowercase_identifier)
        #|  (uppercase_identifier)
        #|] @id
      ,
      placeholder=
        #|_
      ,
    ),
    "ty": @query_language.Entry::new(
      matches=
        #|[
        #|  (type)
        #|  (return_type)
        #|]
      ,
      placeholder=
        #|A
      ,
    ),
  }
  let extras = ["semicolon"]
  let parser = @query_language.Parser::new(
    moonbit_language,
    contexts~,
    entries~,
    extras~,
  )
  moonbit_parser_value.val = Some(parser)
  return parser
}

///|
test "exp" {
  let query =
    #|$a:exp == $b:exp
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; exp
      #|((statement_expression
      #|  (expression
      #|   (pipeline_expression
      #|    (compound_expression
      #|     (binary_expression
      #|      (compound_expression) @a
      #|      ("==")
      #|      (compound_expression) @b))))))
    ,
  )
  let parser = @tree_sitter.parser(moonbit_language)
  let source =
    #|fn main {
    #|  1 == 2
    #|}
  let tree = parser.parse_string!(source)
  let query_cursor = tree.query!(query)
  let captures : Map[String, Array[@string.View]] = {}
  for matched in query_cursor.matches() {
    for capture in matched.captures() {
      match captures[capture.name().to_string()] {
        Some(captures) => captures.push(capture.node().text())
        None => captures[capture.name().to_string()] = [capture.node().text()]
      }
    }
  }
  @json.inspect!(captures, content={ "a": ["1"], "b": ["2"] })
}

///|
test "top" {
  let query =
    #|fn main {
    #|  println($a:exp)
    #|}
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; top
      #|(structure
      #| (structure_item
      #|  (function_definition
      #|   ("fn")
      #|   (function_identifier
      #|    (lowercase_identifier))
      #|   (block_expression
      #|    ("{")
      #|    (statement_expression
      #|     (expression
      #|      (pipeline_expression
      #|       (compound_expression
      #|        (simple_expression
      #|         (apply_expression
      #|          (simple_expression
      #|           (qualified_identifier
      #|            (lowercase_identifier)))
      #|          ("(")
      #|          (argument
      #|           (expression)) @a
      #|          (")")))))))
      #|    ("}")))))
    ,
  )
}

///|
test "fn-ambiguity" {
  let query =
    #|fn $a:id {
    #|  $case:pat => $body:exp
    #|}
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; exp
      #|((statement_expression
      #|  (named_matrix_expression
      #|   ("fn")
      #|   (lowercase_identifier) @a
      #|   ("{")
      #|   (matrix_case_clause
      #|    (pattern) @case
      #|    ("=>")
      #|    (statement_expression
      #|     (expression)) @body)
      #|   ("}"))))
    ,
  )
  let source =
    #|fn f(x : Int) -> Unit {
    #|  fn x {
    #|  }
    #|}
    #|
    #|fn main {
    #|}
  let parser = @tree_sitter.parser(moonbit_language)
  let tree = parser.parse_string!(source)
  let query_cursor = tree.query!(query)
  let captures = {}
  for matched in query_cursor.matches() {
    for capture in matched.captures() {
      captures[capture.name().to_string()] = capture.node().text()
    }
  }
  @json.inspect!(captures, content={})
}

///|
test "concat" {
  let query =
    #|match $a:exp {
    #|  $b:pat => $c:exp
    #|}
    #|return $d:exp
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; exp
      #|((statement_expression
      #|  (expression
      #|   (match_expression
      #|    ("match")
      #|    (compound_expression) @a
      #|    ("{")
      #|    (case_clause
      #|     (pattern) @b
      #|     ("=>")
      #|     (statement_expression
      #|      (expression)) @c)
      #|    ("}"))))
      #| (semicolon)*
      #| (statement_expression
      #|  (return_expression
      #|   ("return")
      #|   (expression) @d)))
    ,
  )
  let parser = @tree_sitter.parser(moonbit_language)
  let source =
    #|fn main {
    #|  match x {
    #|    y => z
    #|  }
    #|  println("a")
    #|  return 3
    #|}
  let tree = parser.parse_string!(source)
  let query_cursor = tree.query!(query)
  let captures = {}
  for capture in query_cursor.captures() {
    captures[capture.name().to_string()] = capture.node().text()
  }
  @json.inspect!(captures, content={ "a": "x", "b": "y", "c": "z", "d": "3" })
}

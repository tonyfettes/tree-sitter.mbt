///|
let moonbit_contexts : Map[String, String] = {
  "exp": #|fn main {
  #|  $
  #|}
  ,
  "top": "$",
  "pat": #|fn main {
  #|  match x {
  #|    $ => y
  #|  }
  #|}
  ,
  "ty": #|let x : $ = 42
  ,
}

///|
let moonbit_entries : Map[String, @query_language.Entry] = {
  "exp": @query_language.Entry::new(
    query=
      #|[
      #|  (compound_expression)
      #|  (statement_expression)
      #|  (expression)
      #|]
    ,
    placeholder=
      #|{ ... }
    ,
  ),
  "top": @query_language.Entry::new(
    query=
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
    query=
      #|[
      #|  (pattern)
      #|]
    ,
    placeholder=
      #|_
    ,
  ),
  "id": @query_language.Entry::new(
    query=
      #|[
      #|  (identifier)
      #|  (lowercase_identifier)
      #|  (uppercase_identifier)
      #|]
    ,
    placeholder=
      #|_
    ,
  ),
  "ty": @query_language.Entry::new(
    query=
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

///|
let moonbit_language : @tree_sitter.Language = @tree_sitter_moonbit.language()

///|
let moonbit_extras = ["semicolon"]

///|
test "exp" {
  let query =
    #|$a:exp == $b:exp
  let parser = @query_language.Parser::new!(
    moonbit_language,
    contexts=moonbit_contexts,
    entries=moonbit_entries,
    extras=moonbit_extras,
  )
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; exp
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
      #|        (binary_expression
      #|         ([(compound_expression)
      #|           (statement_expression)
      #|           (expression)]) @a
      #|         ("==")
      #|         ([(compound_expression)
      #|           (statement_expression)
      #|           (expression)]) @b)))))
      #|    ("}")))))
    ,
  )
  let parser = @tree_sitter.parser(moonbit_language)
  let source =
    #|fn main {
    #|  1 == 2
    #|}
  let tree = parser.parse_string!(source)
  let query_cursor = tree.query!(query)
  let captures = {}
  for matched in query_cursor.matches() {
    for capture in matched.captures() {
      captures[capture.name().to_string()] = capture.node()
    }
  }
  inspect!(
    captures["a"].or_error!(Failure("Missing a")),
    content=
      #|(compound_expression
      #| (simple_expression
      #|  (atomic_expression
      #|   (literal
      #|    (integer_literal)))))
    ,
  )
  inspect!(
    captures["b"].or_error!(Failure("Missing b")),
    content=
      #|(compound_expression
      #| (simple_expression
      #|  (atomic_expression
      #|   (literal
      #|    (integer_literal)))))
    ,
  )
}

///|
test "top" {
  let query =
    #|fn main {
    #|  println($a:exp)
    #|}
  let parser = @query_language.Parser::new!(
    moonbit_language,
    contexts=moonbit_contexts,
    entries=moonbit_entries,
    extras=moonbit_extras,
  )
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
      #|          ([(compound_expression)
      #|            (statement_expression)
      #|            (expression)]) @a
      #|          (")")))))))
      #|    ("}")))))
    ,
  )
}

///|
test "fn-ambiguity" {
  let query =
    #|fn $a:id {
    #|}
  let parser = @query_language.Parser::new!(
    moonbit_language,
    contexts=moonbit_contexts,
    entries=moonbit_entries,
    extras=moonbit_extras,
  )
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; exp
      #|(structure
      #| (structure_item
      #|  (function_definition
      #|   ("fn")
      #|   (function_identifier
      #|    (lowercase_identifier))
      #|   (block_expression
      #|    ("{")
      #|    (statement_expression
      #|     (named_matrix_expression
      #|      ("fn")
      #|      ([(identifier)
      #|        (lowercase_identifier)
      #|        (uppercase_identifier)]) @a
      #|      ("{")
      #|      ("}")))
      #|    ("}"))))) ;; top
      #|(structure
      #| (structure_item
      #|  (function_definition
      #|   ("fn")
      #|   ([(identifier)
      #|     (lowercase_identifier)
      #|     (uppercase_identifier)]) @a
      #|   (block_expression
      #|    ("{")
      #|    ("}")))))
    ,
  )
}

///|
test "pattern" {
  let query =
    #|match $a:exp {
    #|  $b:pat => $c:exp
    #|}
  let parser = @query_language.Parser::new!(
    moonbit_language,
    contexts=moonbit_contexts,
    entries=moonbit_entries,
    extras=moonbit_extras,
  )
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; exp
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
      #|      (match_expression
      #|       ("match")
      #|       ([(compound_expression)
      #|         (statement_expression)
      #|         (expression)]) @a
      #|       ("{")
      #|       (case_clause
      #|        ([(pattern)]) @b
      #|        ("=>")
      #|        ([(compound_expression)
      #|          (statement_expression)
      #|          (expression)]) @c)
      #|       ("}"))))
      #|    ("}")))))
    ,
  )
  let parser = @tree_sitter.parser(moonbit_language)
  let source =
    #|fn main {
    #|  match x {
    #|    y => z
    #|  }
    #|}
  let tree = parser.parse_string!(source)
  let query_cursor = tree.query!(query)
  let captures = {}
  for capture in query_cursor.captures() {
    captures[capture.name().to_string()] = capture.node().text()
  }
  @json.inspect!(captures, content={ "a": "x", "b": "y", "c": "z" })
}

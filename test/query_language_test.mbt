///|
let moonbit_entries : Map[String, @query_language.Entry] = {
  "exp": @query_language.Entry::new(
    context=
      #|fn main {
      #|  $
      #|}
    ,
    query=
      #|[
      #|  (compound_expression)
      #|  (expression)
      #|]
    ,
    placeholder=
      #|{ ... }
    ,
  ),
  "top": @query_language.Entry::new(
    context="$",
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
    context=
      #|fn main {
      #|  match x {
      #|    $ => y
      #|  }
      #|}
    ,
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
    context=
      #|fn main {
      #|  $
      #|}
    ,
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
    context=
      #|let x : $ = 42
    ,
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
  let parser = @query_language.Parser::new(
    moonbit_language,
    entries=moonbit_entries,
    extras=moonbit_extras,
  )
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.pretty!(),
    content=
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
      #|           (expression)]) @a
      #|         ("==")
      #|         ([(compound_expression)
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
    #|  println("Hello, world!")
    #|}
  let parser = @query_language.Parser::new(
    moonbit_language,
    entries=moonbit_entries,
    extras=moonbit_extras,
  )
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.pretty!(),
    content=
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
      #|           (expression
      #|            (pipeline_expression
      #|             (compound_expression
      #|              (simple_expression
      #|               (atomic_expression
      #|                (literal
      #|                 (string_literal
      #|                  ("\"")
      #|                  (string_fragment
      #|                   (unescaped_string_fragment))
      #|                  ("\"")))))))))
      #|          (")")))))))
      #|    ("}")))))
    ,
  )
}

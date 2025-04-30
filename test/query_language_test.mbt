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
      strip=true,
      selector=
        #|(structure
        #| (structure_item
        #|  (function_definition
        #|   (block_expression
        #|    "{"
        #|    (statement_expression
        #|     (_) @exp)
        #|    "}"))))
      ,
    ),
    "top": @query_language.Context::new!(
      "$",
      selector=
        #|(structure_item) @top
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
        #|  (expression)
        #|  (pipeline_expression)
        #|  (compound_expression)
        #|  (match_expression)
        #|  (named_matrix_expression)
        #|  (guard_expression)
        #|  (statement_expression)
        #|  (simple_expression)
        #|] @exp
      ,
      placeholder="{ ... }",
    ),
    "top": @query_language.Entry::new(
      matches=
        #|[
        #|  (structure_item)
        #|] @top
      ,
      placeholder=
        #|type! A Int
      ,
    ),
    "pat": @query_language.Entry::new(
      matches=
        #|[
        #|  (pattern)
        #|  (simple_pattern)
        #|] @pat
      ,
      placeholder="_",
    ),
    "id": @query_language.Entry::new(
      matches=
        #|[
        #|  (identifier)
        #|  (lowercase_identifier)
        #|  (uppercase_identifier)
        #|  (qualified_identifier)
        #|  (constructor_expression)
        #|] @id
      ,
      placeholder="id",
    ),
    "ty": @query_language.Entry::new(
      matches=
        #|[
        #|  (type)
        #|  (return_type)
        #|] @ty
      ,
      placeholder="A",
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
      #|(binary_expression
      #| ((compound_expression) @a)
      #| .
      #| ("==")
      #| .
      #| ((compound_expression) @b))
    ,
  )
  let parser = @tree_sitter.parser(moonbit_language)
  let source =
    #|fn main {
    #|  1 == 2
    #|}
    #|
    #|let a : Bool = 3 == 4
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
  @json.inspect!(captures, content={ "a": ["1", "3"], "b": ["2", "4"] })
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
      #|(structure_item
      #| (function_definition
      #|  ("fn")
      #|  .
      #|  (function_identifier
      #|   (lowercase_identifier))
      #|  .
      #|  (block_expression
      #|   ("{")
      #|   .
      #|   (statement_expression
      #|    (expression
      #|     (pipeline_expression
      #|      (compound_expression
      #|       (simple_expression
      #|        (apply_expression
      #|         (simple_expression
      #|          (qualified_identifier
      #|           (lowercase_identifier)))
      #|         .
      #|         ("(")
      #|         .
      #|         (argument
      #|          ((expression) @a))
      #|         .
      #|         (")")))))))
      #|   .
      #|   (semicolon)*
      #|   .
      #|   ("}"))))
    ,
  )
}

///|
test "fn-ambiguity" {
  let query =
    #|fn $a:id {
    #|}
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    @sexp.prettify!(query),
    content=
      #|;; exp
      #|(named_matrix_expression
      #| ("fn")
      #| .
      #| ((lowercase_identifier) @a)
      #| .
      #| ("{")
      #| .
      #| ("}"))
      #|;; top
      #|(structure_item
      #| (function_definition
      #|  ("fn")
      #|  .
      #|  (function_identifier
      #|   ((lowercase_identifier) @a))
      #|  .
      #|  (block_expression
      #|   ("{")
      #|   .
      #|   ("}"))))
    ,
  )
  let source =
    #|fn f(x : Int) -> Unit {
    #|  fn fx {
    #|  }
    #|}
    #|
    #|let a : Int = {
    #|  fn fa {
    #|  }
    #|}
    #|
    #|fn main {
    #|}
  let parser = @tree_sitter.parser(moonbit_language)
  let tree = parser.parse_string!(source)
  let query_cursor = tree.query!(query)
  let captures : Map[@string.View, Array[@string.View]] = {}
  for matched in query_cursor.matches() {
    for capture in matched.captures() {
      let name = capture.name()
      if captures[name] is Some(captures) {
        captures.push(capture.node().text())
      } else {
        captures[name] = [capture.node().text()]
      }
    }
  }
  @json.inspect!(captures, content={ "a": ["fx", "fa", "main"] })
}

///|
test "concat" {
  let query =
    #|match $a:exp {
    #|  $b:pat => $c:exp
    #|}
    #|$d:exp
    #|return $f:exp
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
      #|    .
      #|    ((compound_expression) @a)
      #|    .
      #|    ("{")
      #|    .
      #|    (case_clause
      #|     ((pattern) @b)
      #|     .
      #|     ("=>")
      #|     .
      #|     ((statement_expression) @c))
      #|    .
      #|    (semicolon)*
      #|    .
      #|    ("}"))))
      #| .
      #| (semicolon)*
      #| .
      #| ((statement_expression) @d)
      #| .
      #| (semicolon)*
      #| .
      #| (statement_expression
      #|  (return_expression
      #|   ("return")
      #|   .
      #|   ((expression) @f))))
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
  @json.inspect!(captures, content={
    "a": "x",
    "b": "y",
    "c": "z",
    "d": "println(\"a\")",
    "f": "3",
  })
}

///|
test "ty" {
  let query =
    #|let $a:id : $b:ty = $c:exp
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    @sexp.prettify!(query),
    content=
      #|;; exp
      #|(let_expression
      #| ("let")
      #| .
      #| (pattern
      #|  (simple_pattern
      #|   ((lowercase_identifier) @a)))
      #| .
      #| (type_annotation
      #|  (colon)
      #|  .
      #|  ((type) @b))
      #| .
      #| ("=")
      #| .
      #| ((expression) @c))
      #|;; top
      #|(structure_item
      #| (value_definition
      #|  ("let")
      #|  .
      #|  ((lowercase_identifier) @a)
      #|  .
      #|  (type_annotation
      #|   (colon)
      #|   .
      #|   ((type) @b))
      #|  .
      #|  ("=")
      #|  .
      #|  ((expression) @c)))
    ,
  )
  let source =
    #|let a : Int = 42
    #|
    #|fn main {
    #|  let b : Bool = true
    #|}
  let parser = @tree_sitter.parser(moonbit_language)
  let tree = parser.parse_string!(source)
  let query_cursor = tree.query!(query)
  let captures : Map[@string.View, Array[@string.View]] = {}
  for capture in query_cursor.captures() {
    if captures[capture.name()] is Some(captures) {
      captures.push(capture.node().text())
    } else {
      captures[capture.name()] = [capture.node().text()]
    }
  }
  @json.inspect!(captures, content={
    "a": ["a", "b"],
    "b": ["Int", "Bool"],
    "c": ["42", "true"],
  })
}

///|
test "id" {
  let query =
    #|match a {
    #|  $a:id => $b:exp
    #|}
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    @sexp.prettify!(query),
    content=
      #|;; exp
      #|(match_expression
      #| ("match")
      #| .
      #| (compound_expression
      #|  (simple_expression
      #|   (qualified_identifier
      #|    (lowercase_identifier))))
      #| .
      #| ("{")
      #| .
      #| (case_clause
      #|  (pattern
      #|   (simple_pattern
      #|    ((lowercase_identifier) @a)))
      #|  .
      #|  ("=>")
      #|  .
      #|  ((statement_expression) @b))
      #| .
      #| (semicolon)*
      #| .
      #| ("}"))
    ,
  )
  let source =
    #|fn main {
    #|  match a {
    #|    A => 1
    #|  }
    #|  match a {
    #|    a => 1
    #|  }
    #|}
  let parser = @tree_sitter.parser(moonbit_language)
  let tree = parser.parse_string!(source)
  let query_cursor = tree.query!(query)
  let captures : Map[@string.View, Array[@string.View]] = {}
  for matched in query_cursor.matches() {
    for capture in matched.captures() {
      let name = capture.name()
      if captures[name] is Some(captures) {
        captures.push(capture.node().text())
      } else {
        captures[name] = [capture.node().text()]
      }
    }
  }
  @json.inspect!(captures, content={ "a": ["a"], "b": ["1"] })
}

///|
test "quantifier-semicolon" {
  let query =
    #|guard $a:exp is $b:pat else {
    #|  $_:{
    #|    $c:exp
    #|  $}*
    #|  return $d:exp
    #|}
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; exp
      #|(guard_expression
      #| ("guard")
      #| .
      #| (compound_expression
      #|  (postfix_expression
      #|   (is_expression
      #|    ((simple_expression) @a)
      #|    .
      #|    (is_keyword)
      #|    .
      #|    ((simple_pattern) @b))))
      #| .
      #| (guard_else_expression
      #|  ("else")
      #|  .
      #|  (block_expression
      #|   ("{")
      #|   .
      #|   ((statement_expression
      #|     ((expression) @c))
      #|    .
      #|    (semicolon)*)*
      #|   .
      #|   (statement_expression
      #|    (return_expression
      #|     ("return")
      #|     .
      #|     ((expression) @d)))
      #|   .
      #|   (semicolon)*
      #|   .
      #|   ("}"))))

    ,
  )
  let source =
    #|fn main {
    #|  guard a is None else {
    #|    return 3
    #|  }
    #|  guard a is Some else {
    #|    println("a")
    #|    return 4
    #|  }
    #|  guard a is Some else {
    #|    println("a")
    #|    println("b")
    #|    return 5
    #|  }
    #|}
  let parser = @tree_sitter.parser(moonbit_language)
  let tree = parser.parse_string!(source)
  let query_cursor = tree.query!(query)
  let matches = []
  for matched in query_cursor.matches() {
    let captures : Map[@string.View, Array[@string.View]] = {}
    for capture in matched.captures() {
      let name = capture.name()
      if captures[name] is Some(captures) {
        captures.push(capture.node().text())
      } else {
        captures[name] = [capture.node().text()]
      }
    }
    matches.push(captures)
  }
  @json.inspect!(matches, content=[{"a":["a"],"b":["None"],"d":["3"]},{"a":["a"],"b":["Some"],"c":["println(\"a\")"],"d":["4"]},{"a":["a"],"b":["Some"],"c":["println(\"a\")","println(\"b\")"],"d":["5"]}])
}

///|
test "group" {
  let query =
    #|[
    #|  $_:{
    #|    $x:exp,
    #|  $}+
    #|  $x:exp
    #|]
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; exp
      #|(array_expression
      #| ("[")
      #| .
      #| ((expression
      #|   ((pipeline_expression) @x))
      #|  .
      #|  (","))+
      #| .
      #| ((expression) @x)
      #| .
      #| ("]"))
    ,
  )
  let source =
    #|fn main {
    #|  [1, 2, 3, 4]
    #|}
  let parser = @tree_sitter.parser(moonbit_language)
  let tree = parser.parse_string!(source)
  let query_cursor = tree.query!(query)
  let captures : Map[@string.View, Array[@string.View]] = {}
  for capture in query_cursor.captures() {
    let name = capture.name()
    if captures[name] is Some(captures) {
      captures.push(capture.node().text())
    } else {
      captures[name] = [capture.node().text()]
    }
  }
  @json.inspect!(captures, content={ "x": ["1", "2", "3", "4"] })
}

///|
fn moonbit_parser() -> @tsql.Parser! {
  let language = @tree_sitter_moonbit.language()
  let contexts : Map[String, @tsql.Context] = {
    "exp": @tsql.Context::new!(
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
    "top": @tsql.Context::new!(
      "$",
      selector=
        #|(structure_item) @top
      ,
    ),
    "pat": @tsql.Context::new!(
      #|fn main {
      #|  match x {
      #|    $ => y
      #|  }
      #|}
      ,
      selector=
        #|(pattern) @pat
      ,
    ),
    "ty": @tsql.Context::new!(
      #|let x : $ = 42
      ,
      selector=
        #|(type) @ty
      ,
    ),
    "case": @tsql.Context::new!(
      #|fn main {
      #|  match x {
      #|    $
      #|  }
      #|}
      ,
      selector=
        #|(case_clause) @case
      ,
    ),
    "matrix": @tsql.Context::new!(
      #|fn main {
      #|  loop a, b {
      #|    $
      #|  }
      #|}
      ,
      selector=
        #|(matrix_case_clause) @matrix
      ,
    ),
  }
  let entries : Map[String, @tsql.Entry] = {
    "exp": @tsql.Entry::new(
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
      placeholder="{...}",
    ),
    "top": @tsql.Entry::new(
      matches=
        #|[
        #|  (structure_item)
        #|] @top
      ,
      placeholder=
        #|type! A Int
      ,
    ),
    "pat": @tsql.Entry::new(
      matches=
        #|[
        #|  (pattern)
        #|  (simple_pattern)
        #|] @pat
      ,
      placeholder="_",
    ),
    "id": @tsql.Entry::new(
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
    "ty": @tsql.Entry::new(
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
  let parser = @tsql.Parser::new(language, contexts~, entries~, extras~)
  return parser
}

///|
test "exp" {
  let query =
    #|$exp:a == $exp:b
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
  let language = parser.language()
  let parser = parser.parser()
  let source =
    #|fn main {
    #|  1 == 2
    #|}
    #|
    #|let a : Bool = 3 == 4
  let tree = parser.parse_string!(source)
  let query_cursor = @tree_sitter.Query::new!(language, query)
  let captures : Map[String, Array[@string.View]] = {}
  for matched in query_cursor.matches(tree.root_node()) {
    for capture in matched.captures() {
      match captures.get(capture.name().to_string()) {
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
    #|  println($exp:a)
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
      #|   ((lowercase_identifier) @_id_0
      #|    (#eq? @_id_0
      #|     "main")))
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
      #|           ((lowercase_identifier) @_id_1
      #|            (#eq? @_id_1
      #|             "println"))))
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
test "fn_ambiguity" {
  let query =
    #|fn $id:a {
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
  let language = parser.language()
  let parser = parser.parser()
  let tree = parser.parse_string!(source)
  let query = @tree_sitter.Query::new!(language, query)
  let captures : Map[@string.View, Array[@string.View]] = {}
  for matched in query.matches(tree.root_node()) {
    for capture in matched.captures() {
      let name = capture.name()
      if captures.get(name) is Some(captures) {
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
    #|match $exp:a {
    #|  $pat:b => $exp:c
    #|}
    #|$exp:d
    #|return $exp:f
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
  let language = parser.language()
  let parser = parser.parser()
  let source =
    #|fn main {
    #|  match x {
    #|    y => z
    #|  }
    #|  println("a")
    #|  return 3
    #|}
  let tree = parser.parse_string!(source)
  let query_cursor = @tree_sitter.Query::new!(language, query)
  let captures = {}
  for capture in query_cursor.captures(tree.root_node()) {
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
    #|let $id:a : $ty:b = $exp:c
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
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
      #|  ((colon) @_id_0
      #|   (#eq? @_id_0
      #|    ":"))
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
      #|   ((colon) @_id_1
      #|    (#eq? @_id_1
      #|     ":"))
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
  let language = parser.language()
  let parser = parser.parser()
  let tree = parser.parse_string!(source)
  let query_cursor = @tree_sitter.Query::new!(language, query)
  let captures : Map[@string.View, Array[@string.View]] = {}
  for capture in query_cursor.captures(tree.root_node()) {
    if captures.get(capture.name()) is Some(captures) {
      captures.push(capture.node().text())
    } else {
      captures[capture.name()] = [capture.node().text()]
    }
  }
  @json.inspect!(captures, content={
    "a": ["a", "b"],
    "_id_1": [":"],
    "b": ["Int", "Bool"],
    "c": ["42", "true"],
    "_id_0": [":"],
  })
}

///|
test "id" {
  let query =
    #|match a {
    #|  $id:a => $exp:b
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
      #|    ((lowercase_identifier) @_id_0
      #|     (#eq? @_id_0
      #|      "a")))))
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
  let language = parser.language()
  let parser = parser.parser()
  let tree = parser.parse_string!(source)
  let query_cursor = @tree_sitter.Query::new!(language, query)
  let captures : Map[@string.View, Array[@string.View]] = {}
  for matched in query_cursor.matches(tree.root_node()) {
    for capture in matched.captures() {
      let name = capture.name()
      if captures.get(name) is Some(captures) {
        captures.push(capture.node().text())
      } else {
        captures[name] = [capture.node().text()]
      }
    }
  }
  @json.inspect!(captures, content={ "_id_0": ["a"], "a": ["a"], "b": ["1"] })
}

///|
test "quantifier" {
  let query =
    #|guard $exp:a is $pat:b else {
    #|  ${
    #|    $exp:c
    #|  }*
    #|  return $exp:d
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
      #|    ((is_keyword) @_id_0
      #|     (#eq? @_id_0
      #|      "is"))
      #|    .
      #|    ((simple_pattern) @b))))
      #| .
      #| (guard_else_expression
      #|  ("else")
      #|  .
      #|  (block_expression
      #|   ("{")
      #|   .
      #|   (((statement_expression) @c
      #|     (semicolon))
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
  let language = parser.language()
  let parser = parser.parser()
  let tree = parser.parse_string!(source)
  let query_cursor = @tree_sitter.Query::new!(language, query)
  let matches = []
  for matched in query_cursor.matches(tree.root_node()) {
    let captures : Map[@string.View, Array[@string.View]] = {}
    for capture in matched.captures() {
      let name = capture.name()
      if captures.get(name) is Some(captures) {
        captures.push(capture.node().text())
      } else {
        captures[name] = [capture.node().text()]
      }
    }
    matches.push(captures)
  }
  @json.inspect!(matches, content=[
    { "a": ["a"], "_id_0": ["is"], "b": ["None"], "d": ["3"] },
    {
      "a": ["a"],
      "_id_0": ["is"],
      "b": ["Some"],
      "c": ["println(\"a\")"],
      "d": ["4"],
    },
    {
      "a": ["a"],
      "_id_0": ["is"],
      "b": ["Some"],
      "c": ["println(\"a\")", "println(\"b\")"],
      "d": ["5"],
    },
  ])
}

///|
test "group" {
  let query =
    #|[${ $exp:x, }+ $exp:x]
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; exp
      #|(array_expression
      #| ("[")
      #| .
      #| (((expression) @x)
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
    #|  [0]
    #|  [0, 1]
    #|  [0, 1, 2]
    #|}
  let language = parser.language()
  let parser = parser.parser()
  let tree = parser.parse_string!(source)
  let query_cursor = @tree_sitter.Query::new!(language, query)
  let matches = []
  for matched in query_cursor.matches(tree.root_node()) {
    let captures : Map[@string.View, Array[@string.View]] = {}
    for capture in matched.captures() {
      let name = capture.name()
      if captures.get(name) is Some(captures) {
        captures.push(capture.node().text())
      } else {
        captures[name] = [capture.node().text()]
      }
    }
    matches.push(captures)
  }
  @json.inspect!(matches, content=[
    { "x": ["0", "1"] },
    { "x": ["0", "1", "2"] },
  ])
}

///|
test "case" {
  let query =
    #|${ $pat:a, }* $pat:a => $exp:b
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    @sexp.prettify!(query),
    content=
      #|;; matrix
      #|(matrix_case_clause
      #| (((pattern) @a)
      #|  .
      #|  (","))*
      #| .
      #| ((pattern) @a)
      #| .
      #| ("=>")
      #| .
      #| ((statement_expression) @b))
    ,
  )
  let source =
    #|fn main {
    #|  match a {
    #|    A => 1
    #|  }
    #|  fn b {
    #|    B => 2
    #|  }
    #|  loop c, d {
    #|    C, D => 3
    #|  }
    #|}
  let language = parser.language()
  let parser = parser.parser()
  let tree = parser.parse_string!(source)
  let query_cursor = @tree_sitter.Query::new!(language, query)
  let matches = []
  for matched in query_cursor.matches(tree.root_node()) {
    let captures : Map[@string.View, Array[@string.View]] = {}
    for capture in matched.captures() {
      let name = capture.name()
      if captures.get(name) is Some(captures) {
        captures.push(capture.node().text())
      } else {
        captures[name] = [capture.node().text()]
      }
    }
    matches.push(captures)
  }
  @json.inspect!(matches, content=[
    { "a": ["B"], "b": ["2"] },
    { "a": ["C", "D"], "b": ["3"] },
  ])
}

///|
test "escape" {
  let query =
    #|${
    #|fn init \{
    #|  ${
    #|    $exp:a
    #|  }*
    #|\}
    #|}+
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; top
      #|((structure_item
      #|  (function_definition
      #|   ("fn")
      #|   .
      #|   (function_identifier
      #|    ((lowercase_identifier) @_id_0
      #|     (#eq? @_id_0
      #|      "init")))
      #|   .
      #|   (block_expression
      #|    ("{")
      #|    .
      #|    (((statement_expression) @a
      #|      (semicolon))
      #|     .
      #|     (semicolon)*)*
      #|    .
      #|    ("}")))))+
    ,
  )
}

///|
test "match_id" {
  let query =
    #|match a {
    #|  $pat:p => $exp:e
    #|}
  let parser = moonbit_parser!()
  let query = parser.parse!(query)
  inspect!(
    query |> @sexp.prettify!(),
    content=
      #|;; exp
      #|(match_expression
      #| ("match")
      #| .
      #| (compound_expression
      #|  (simple_expression
      #|   (qualified_identifier
      #|    ((lowercase_identifier) @_id_0
      #|     (#eq? @_id_0
      #|      "a")))))
      #| .
      #| ("{")
      #| .
      #| (case_clause
      #|  ((pattern) @p)
      #|  .
      #|  ("=>")
      #|  .
      #|  ((statement_expression) @e))
      #| .
      #| (semicolon)*
      #| .
      #| ("}"))
    ,
  )
  let source =
    #|fn main {
    #|  match a {
    #|    _ => 1
    #|  }
    #|  match b {
    #|    _ => 1
    #|  }
    #|}
  let parser = parser.parser()
  let tree = parser.parse_string!(source)
  let query_cursor = @tree_sitter.Query::new!(parser.language().unwrap(), query)
  let captures : Map[@string.View, Array[@string.View]] = {}
  for matched in query_cursor.matches(tree.root_node()) {
    for capture in matched.captures() {
      let name = capture.name()
      if captures.get(name) is Some(captures) {
        captures.push(capture.node().text())
      } else {
        captures[name] = [capture.node().text()]
      }
    }
  }
  @json.inspect!(captures, content={
    "_id_0": ["a", "b"],
    "p": ["_", "_"],
    "e": ["1", "1"],
  })
}

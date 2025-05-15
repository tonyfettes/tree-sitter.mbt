///|
fn moonbit() -> @pattern.Language! {
  let language = @tree_sitter_moonbit.language()
  let contexts : Map[String, @pattern.Context] = {
    "exp": @pattern.Context::new!(
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
    "top": @pattern.Context::new!(
      "$",
      selector=
        #|(structure_item) @top
      ,
    ),
    "pat": @pattern.Context::new!(
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
    "ty": @pattern.Context::new!(
      #|let x : $ = 42
      ,
      selector=
        #|(type) @ty
      ,
    ),
    "case": @pattern.Context::new!(
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
    "matrix": @pattern.Context::new!(
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
  let entries : Map[String, @pattern.Entry] = {
    "exp": @pattern.Entry::new(
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
    "top": @pattern.Entry::new(
      matches=
        #|[
        #|  (structure_item)
        #|] @top
      ,
      placeholder=
        #|type! A Int
      ,
    ),
    "pat": @pattern.Entry::new(
      matches=
        #|[
        #|  (pattern)
        #|  (simple_pattern)
        #|] @pat
      ,
      placeholder="_",
    ),
    "id": @pattern.Entry::new(
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
    "ty": @pattern.Entry::new(
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
  @pattern.Language::new(language, contexts~, entries~, extras~)
}

///|
test "exp" {
  let query =
    #|$exp:a == $exp:b
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|fn main {
    #|  1 == 2
    #|}
    #|
    #|let a : Bool = 3 == 4
    ,
  )
  @json.inspect!(matches, content=[
    { "a": ["1"], "b": ["2"] },
    { "a": ["3"], "b": ["4"] },
  ])
}

///|
test "top" {
  let query =
    #|fn main {
    #|  println($exp:a)
    #|}
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|fn main {
    #|  println("Hello, world!")
    #|}
    #|
    #|fn foo {
    #|  println("Hello, world!")
    #|}
    ,
  )
  @json.inspect!(matches, content=[{ "a": ["\"Hello, world!\""] }])
}

///|
test "fn_ambiguity" {
  let query =
    #|fn $id:a {
    #|}
  let query = moonbit!().compile!(query)
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
  let matches = query.search!(source)
  @json.inspect!(matches, content=[
    { "a": ["fx"] },
    { "a": ["fa"] },
    { "a": ["main"] },
  ])
}

///|
test "concat" {
  let query =
    #|match $exp:a {
    #|  $pat:b => $exp:c
    #|}
    #|$exp:d
    #|return $exp:f
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|fn main {
    #|  match x {
    #|    y => z
    #|  }
    #|  println("a")
    #|  return 3
    #|}
    ,
  )
  @json.inspect!(matches, content=[
    { "a": ["x"], "b": ["y"], "c": ["z"], "d": ["println(\"a\")"], "f": ["3"] },
  ])
}

///|
test "ty" {
  let query =
    #|let $id:a : $ty:b = $exp:c
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|let a : Int = 42
    #|
    #|fn main {
    #|  let b : Bool = true
    #|}
    ,
  )
  @json.inspect!(matches, content=[
    { "a": ["a"], "b": ["Int"], "c": ["42"] },
    { "a": ["b"], "b": ["Bool"], "c": ["true"] },
  ])
}

///|
test "id" {
  let query =
    #|match a {
    #|  $id:a => $exp:b
    #|}
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|fn main {
    #|  match a {
    #|    A => 1
    #|  }
    #|  match a {
    #|    a => 2
    #|  }
    #|}
    ,
  )
  @json.inspect!(matches, content=[{ "a": ["a"], "b": ["2"] }])
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
  let query = moonbit!().compile!(query)
  let matches = query.search!(
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
    ,
  )
  @json.inspect!(matches, content=[
    { "a": ["a"], "b": ["None"], "d": ["3"] },
    { "a": ["a"], "b": ["Some"], "c": ["println(\"a\")"], "d": ["4"] },
    {
      "a": ["a"],
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
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|fn main {
    #|  [0]
    #|  [0, 1]
    #|  [0, 1, 2]
    #|}
    ,
  )
  @json.inspect!(matches, content=[
    { "x": ["0", "1"] },
    { "x": ["0", "1", "2"] },
  ])
}

///|
test "case" {
  let query =
    #|${ $pat:a, }* $pat:a => $exp:b
  let query = moonbit!().compile!(query)
  let matches = query.search!(
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
    ,
  )
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
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|fn init {
    #|  println("Hello")
    #|}
    #|
    #|fn init {
    #|  println("World")
    #|  println("!")
    #|}
    ,
  )
  @json.inspect!(matches, content=[
    { "a": ["println(\"Hello\")"] },
    { "a": ["println(\"World\")", "println(\"!\")"] },
  ])
}

///|
test "match_id" {
  let query =
    #|match a {
    #|  $pat:p => $exp:e
    #|}
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|fn main {
    #|  match a {
    #|    _ => 1
    #|  }
    #|  match b {
    #|    _ => 1
    #|  }
    #|}
    ,
  )
  @json.inspect!(matches, content=[{ "p": ["_"], "e": ["1"] }])
}

///|
test "multiple_patterns" {
  let query =
    #|match a {
    #|  $pat:p1 | $pat:p2 => $exp:e
    #|}
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|fn main {
    #|  match a {
    #|    1 | 2 => "number"
    #|  }
    #|}
    ,
  )
  @json.inspect!(matches, content=[
    { "p1": ["1"], "p2": ["2"], "e": ["\"number\""] },
  ])
}

///|
test "guard_condition" {
  let query =
    #|match a {
    #|  $pat:p if $exp:condition => $exp:e
    #|}
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|fn main {
    #|  match a {
    #|    x if x > 0 => "positive"
    #|  }
    #|}
    ,
  )
  @json.inspect!(matches, content=[
    { "p": ["x"], "condition": ["x > 0"], "e": ["\"positive\""] },
  ])
}

///|
test "loop_expression" {
  let query =
    #|loop $id:var {
    #|  $pat:p => $exp:e
    #|}
  let query = moonbit!().compile!(query)
  let matches = query.search!(
    #|fn main {
    #|  loop state {
    #|    Empty => 0
    #|    Node(value, next) => value + next
    #|  }
    #|}
    ,
  )
  @json.inspect!(matches, content=[])
}

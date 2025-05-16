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
  @pattern.Language::new!(language, contexts~, entries~, extras~)
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 1, "column": 2 },
        "end": { "row": 1, "column": 8 },
      },
      "captures": {
        "a": [
          {
            "node": "(compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))",
            "text": "1",
            "range": {
              "start": { "row": 1, "column": 2 },
              "end": { "row": 1, "column": 3 },
            },
          },
        ],
        "b": [
          {
            "node": "(compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))",
            "text": "2",
            "range": {
              "start": { "row": 1, "column": 7 },
              "end": { "row": 1, "column": 8 },
            },
          },
        ],
      },
    },
    {
      "range": {
        "start": { "row": 4, "column": 15 },
        "end": { "row": 4, "column": 21 },
      },
      "captures": {
        "a": [
          {
            "node": "(compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))",
            "text": "3",
            "range": {
              "start": { "row": 4, "column": 15 },
              "end": { "row": 4, "column": 16 },
            },
          },
        ],
        "b": [
          {
            "node": "(compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))",
            "text": "4",
            "range": {
              "start": { "row": 4, "column": 20 },
              "end": { "row": 4, "column": 21 },
            },
          },
        ],
      },
    },
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 0, "column": 0 },
        "end": { "row": 2, "column": 1 },
      },
      "captures": {
        "a": [
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment)))))))))",
            "text": "\"Hello, world!\"",
            "range": {
              "start": { "row": 1, "column": 10 },
              "end": { "row": 1, "column": 25 },
            },
          },
        ],
      },
    },
  ])
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 1, "column": 2 },
        "end": { "row": 2, "column": 3 },
      },
      "captures": {
        "a": [
          {
            "node": "(lowercase_identifier)",
            "text": "fx",
            "range": {
              "start": { "row": 1, "column": 5 },
              "end": { "row": 1, "column": 7 },
            },
          },
        ],
      },
    },
    {
      "range": {
        "start": { "row": 6, "column": 2 },
        "end": { "row": 7, "column": 3 },
      },
      "captures": {
        "a": [
          {
            "node": "(lowercase_identifier)",
            "text": "fa",
            "range": {
              "start": { "row": 6, "column": 5 },
              "end": { "row": 6, "column": 7 },
            },
          },
        ],
      },
    },
    {
      "range": {
        "start": { "row": 10, "column": 0 },
        "end": { "row": 11, "column": 1 },
      },
      "captures": {
        "a": [
          {
            "node": "(lowercase_identifier)",
            "text": "main",
            "range": {
              "start": { "row": 10, "column": 3 },
              "end": { "row": 10, "column": 7 },
            },
          },
        ],
      },
    },
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 1, "column": 2 },
        "end": { "row": 5, "column": 10 },
      },
      "captures": {
        "a": [
          {
            "node": "(compound_expression (simple_expression (qualified_identifier (lowercase_identifier))))",
            "text": "x",
            "range": {
              "start": { "row": 1, "column": 8 },
              "end": { "row": 1, "column": 9 },
            },
          },
        ],
        "b": [
          {
            "node": "(pattern (simple_pattern (lowercase_identifier)))",
            "text": "y",
            "range": {
              "start": { "row": 2, "column": 4 },
              "end": { "row": 2, "column": 5 },
            },
          },
        ],
        "c": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (qualified_identifier (lowercase_identifier)))))))",
            "text": "z",
            "range": {
              "start": { "row": 2, "column": 9 },
              "end": { "row": 2, "column": 10 },
            },
          },
        ],
        "d": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (apply_expression (simple_expression (qualified_identifier (lowercase_identifier))) (argument (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment))))))))))))))))",
            "text": "println(\"a\")",
            "range": {
              "start": { "row": 4, "column": 2 },
              "end": { "row": 4, "column": 14 },
            },
          },
        ],
        "f": [
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))",
            "text": "3",
            "range": {
              "start": { "row": 5, "column": 9 },
              "end": { "row": 5, "column": 10 },
            },
          },
        ],
      },
    },
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 0, "column": 0 },
        "end": { "row": 0, "column": 16 },
      },
      "captures": {
        "a": [
          {
            "node": "(lowercase_identifier)",
            "text": "a",
            "range": {
              "start": { "row": 0, "column": 4 },
              "end": { "row": 0, "column": 5 },
            },
          },
        ],
        "b": [
          {
            "node": "(type (apply_type (qualified_type_identifier (identifier (uppercase_identifier)))))",
            "text": "Int",
            "range": {
              "start": { "row": 0, "column": 8 },
              "end": { "row": 0, "column": 11 },
            },
          },
        ],
        "c": [
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))",
            "text": "42",
            "range": {
              "start": { "row": 0, "column": 14 },
              "end": { "row": 0, "column": 16 },
            },
          },
        ],
      },
    },
    {
      "range": {
        "start": { "row": 3, "column": 2 },
        "end": { "row": 3, "column": 21 },
      },
      "captures": {
        "a": [
          {
            "node": "(lowercase_identifier)",
            "text": "b",
            "range": {
              "start": { "row": 3, "column": 6 },
              "end": { "row": 3, "column": 7 },
            },
          },
        ],
        "b": [
          {
            "node": "(type (apply_type (qualified_type_identifier (identifier (uppercase_identifier)))))",
            "text": "Bool",
            "range": {
              "start": { "row": 3, "column": 10 },
              "end": { "row": 3, "column": 14 },
            },
          },
        ],
        "c": [
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (boolean_literal)))))))",
            "text": "true",
            "range": {
              "start": { "row": 3, "column": 17 },
              "end": { "row": 3, "column": 21 },
            },
          },
        ],
      },
    },
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 4, "column": 2 },
        "end": { "row": 6, "column": 3 },
      },
      "captures": {
        "a": [
          {
            "node": "(lowercase_identifier)",
            "text": "a",
            "range": {
              "start": { "row": 5, "column": 4 },
              "end": { "row": 5, "column": 5 },
            },
          },
        ],
        "b": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal))))))))",
            "text": "2",
            "range": {
              "start": { "row": 5, "column": 9 },
              "end": { "row": 5, "column": 10 },
            },
          },
        ],
      },
    },
  ])
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 1, "column": 2 },
        "end": { "row": 3, "column": 3 },
      },
      "captures": {
        "a": [
          {
            "node": "(simple_expression (qualified_identifier (lowercase_identifier)))",
            "text": "a",
            "range": {
              "start": { "row": 1, "column": 8 },
              "end": { "row": 1, "column": 9 },
            },
          },
        ],
        "b": [
          {
            "node": "(simple_pattern (constructor_pattern (constructor_expression (uppercase_identifier))))",
            "text": "None",
            "range": {
              "start": { "row": 1, "column": 13 },
              "end": { "row": 1, "column": 17 },
            },
          },
        ],
        "d": [
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))",
            "text": "3",
            "range": {
              "start": { "row": 2, "column": 11 },
              "end": { "row": 2, "column": 12 },
            },
          },
        ],
      },
    },
    {
      "range": {
        "start": { "row": 4, "column": 2 },
        "end": { "row": 7, "column": 3 },
      },
      "captures": {
        "a": [
          {
            "node": "(simple_expression (qualified_identifier (lowercase_identifier)))",
            "text": "a",
            "range": {
              "start": { "row": 4, "column": 8 },
              "end": { "row": 4, "column": 9 },
            },
          },
        ],
        "b": [
          {
            "node": "(simple_pattern (constructor_pattern (constructor_expression (uppercase_identifier))))",
            "text": "Some",
            "range": {
              "start": { "row": 4, "column": 13 },
              "end": { "row": 4, "column": 17 },
            },
          },
        ],
        "c": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (apply_expression (simple_expression (qualified_identifier (lowercase_identifier))) (argument (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment))))))))))))))))",
            "text": "println(\"a\")",
            "range": {
              "start": { "row": 5, "column": 4 },
              "end": { "row": 5, "column": 16 },
            },
          },
        ],
        "d": [
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))",
            "text": "4",
            "range": {
              "start": { "row": 6, "column": 11 },
              "end": { "row": 6, "column": 12 },
            },
          },
        ],
      },
    },
    {
      "range": {
        "start": { "row": 8, "column": 2 },
        "end": { "row": 12, "column": 3 },
      },
      "captures": {
        "a": [
          {
            "node": "(simple_expression (qualified_identifier (lowercase_identifier)))",
            "text": "a",
            "range": {
              "start": { "row": 8, "column": 8 },
              "end": { "row": 8, "column": 9 },
            },
          },
        ],
        "b": [
          {
            "node": "(simple_pattern (constructor_pattern (constructor_expression (uppercase_identifier))))",
            "text": "Some",
            "range": {
              "start": { "row": 8, "column": 13 },
              "end": { "row": 8, "column": 17 },
            },
          },
        ],
        "c": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (apply_expression (simple_expression (qualified_identifier (lowercase_identifier))) (argument (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment))))))))))))))))",
            "text": "println(\"a\")",
            "range": {
              "start": { "row": 9, "column": 4 },
              "end": { "row": 9, "column": 16 },
            },
          },
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (apply_expression (simple_expression (qualified_identifier (lowercase_identifier))) (argument (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment))))))))))))))))",
            "text": "println(\"b\")",
            "range": {
              "start": { "row": 10, "column": 4 },
              "end": { "row": 10, "column": 16 },
            },
          },
        ],
        "d": [
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))",
            "text": "5",
            "range": {
              "start": { "row": 11, "column": 11 },
              "end": { "row": 11, "column": 12 },
            },
          },
        ],
      },
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 2, "column": 2 },
        "end": { "row": 2, "column": 8 },
      },
      "captures": {
        "x": [
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))",
            "text": "0",
            "range": {
              "start": { "row": 2, "column": 3 },
              "end": { "row": 2, "column": 4 },
            },
          },
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))",
            "text": "1",
            "range": {
              "start": { "row": 2, "column": 6 },
              "end": { "row": 2, "column": 7 },
            },
          },
        ],
      },
    },
    {
      "range": {
        "start": { "row": 3, "column": 2 },
        "end": { "row": 3, "column": 11 },
      },
      "captures": {
        "x": [
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))",
            "text": "0",
            "range": {
              "start": { "row": 3, "column": 3 },
              "end": { "row": 3, "column": 4 },
            },
          },
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))",
            "text": "1",
            "range": {
              "start": { "row": 3, "column": 6 },
              "end": { "row": 3, "column": 7 },
            },
          },
          {
            "node": "(expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))",
            "text": "2",
            "range": {
              "start": { "row": 3, "column": 9 },
              "end": { "row": 3, "column": 10 },
            },
          },
        ],
      },
    },
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 5, "column": 4 },
        "end": { "row": 5, "column": 10 },
      },
      "captures": {
        "a": [
          {
            "node": "(pattern (simple_pattern (constructor_pattern (constructor_expression (uppercase_identifier)))))",
            "text": "B",
            "range": {
              "start": { "row": 5, "column": 4 },
              "end": { "row": 5, "column": 5 },
            },
          },
        ],
        "b": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal))))))))",
            "text": "2",
            "range": {
              "start": { "row": 5, "column": 9 },
              "end": { "row": 5, "column": 10 },
            },
          },
        ],
      },
    },
    {
      "range": {
        "start": { "row": 8, "column": 4 },
        "end": { "row": 8, "column": 13 },
      },
      "captures": {
        "a": [
          {
            "node": "(pattern (simple_pattern (constructor_pattern (constructor_expression (uppercase_identifier)))))",
            "text": "C",
            "range": {
              "start": { "row": 8, "column": 4 },
              "end": { "row": 8, "column": 5 },
            },
          },
          {
            "node": "(pattern (simple_pattern (constructor_pattern (constructor_expression (uppercase_identifier)))))",
            "text": "D",
            "range": {
              "start": { "row": 8, "column": 7 },
              "end": { "row": 8, "column": 8 },
            },
          },
        ],
        "b": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal))))))))",
            "text": "3",
            "range": {
              "start": { "row": 8, "column": 12 },
              "end": { "row": 8, "column": 13 },
            },
          },
        ],
      },
    },
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 0, "column": 0 },
        "end": { "row": 2, "column": 1 },
      },
      "captures": {
        "a": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (apply_expression (simple_expression (qualified_identifier (lowercase_identifier))) (argument (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment))))))))))))))))",
            "text": "println(\"Hello\")",
            "range": {
              "start": { "row": 1, "column": 2 },
              "end": { "row": 1, "column": 18 },
            },
          },
        ],
      },
    },
    {
      "range": {
        "start": { "row": 4, "column": 0 },
        "end": { "row": 7, "column": 1 },
      },
      "captures": {
        "a": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (apply_expression (simple_expression (qualified_identifier (lowercase_identifier))) (argument (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment))))))))))))))))",
            "text": "println(\"World\")",
            "range": {
              "start": { "row": 5, "column": 2 },
              "end": { "row": 5, "column": 18 },
            },
          },
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (apply_expression (simple_expression (qualified_identifier (lowercase_identifier))) (argument (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment))))))))))))))))",
            "text": "println(\"!\")",
            "range": {
              "start": { "row": 6, "column": 2 },
              "end": { "row": 6, "column": 14 },
            },
          },
        ],
      },
    },
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 1, "column": 2 },
        "end": { "row": 3, "column": 3 },
      },
      "captures": {
        "p": [
          {
            "node": "(pattern (simple_pattern))",
            "text": "_",
            "range": {
              "start": { "row": 2, "column": 4 },
              "end": { "row": 2, "column": 5 },
            },
          },
        ],
        "e": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (integer_literal))))))))",
            "text": "1",
            "range": {
              "start": { "row": 2, "column": 9 },
              "end": { "row": 2, "column": 10 },
            },
          },
        ],
      },
    },
  ])
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 1, "column": 2 },
        "end": { "row": 3, "column": 3 },
      },
      "captures": {
        "p1": [
          {
            "node": "(pattern (simple_pattern (literal (integer_literal))))",
            "text": "1",
            "range": {
              "start": { "row": 2, "column": 4 },
              "end": { "row": 2, "column": 5 },
            },
          },
        ],
        "p2": [
          {
            "node": "(pattern (simple_pattern (literal (integer_literal))))",
            "text": "2",
            "range": {
              "start": { "row": 2, "column": 8 },
              "end": { "row": 2, "column": 9 },
            },
          },
        ],
        "e": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment))))))))))",
            "text": "\"number\"",
            "range": {
              "start": { "row": 2, "column": 13 },
              "end": { "row": 2, "column": 21 },
            },
          },
        ],
      },
    },
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
  @json.inspect!(matches.collect(), content=[
    {
      "range": {
        "start": { "row": 1, "column": 2 },
        "end": { "row": 3, "column": 3 },
      },
      "captures": {
        "p": [
          {
            "node": "(pattern (simple_pattern (lowercase_identifier)))",
            "text": "x",
            "range": {
              "start": { "row": 2, "column": 4 },
              "end": { "row": 2, "column": 5 },
            },
          },
        ],
        "condition": [
          {
            "node": "(expression (pipeline_expression (compound_expression (binary_expression (compound_expression (simple_expression (qualified_identifier (lowercase_identifier)))) (compound_expression (simple_expression (atomic_expression (literal (integer_literal)))))))))",
            "text": "x > 0",
            "range": {
              "start": { "row": 2, "column": 9 },
              "end": { "row": 2, "column": 14 },
            },
          },
        ],
        "e": [
          {
            "node": "(statement_expression (expression (pipeline_expression (compound_expression (simple_expression (atomic_expression (literal (string_literal (string_fragment (unescaped_string_fragment))))))))))",
            "text": "\"positive\"",
            "range": {
              "start": { "row": 2, "column": 18 },
              "end": { "row": 2, "column": 28 },
            },
          },
        ],
      },
    },
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
  @json.inspect!(matches.collect(), content=[])
}

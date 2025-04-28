///|
test "parse" {
  @json.inspect!(
    @sexp.parse!(
      #|(structure
      #| (structure_item
      #|  (function_definition
      #|   (function_identifier
      #|    (lowercase_identifier)))))
      #|(ERROR (UNEXPECTED '`'))
      ,
    ),
    content=[
      [
        { "$tag": "Symbol", "0": "structure" },
        { "$tag": "Newline" },
        [
          { "$tag": "Symbol", "0": "structure_item" },
          { "$tag": "Newline" },
          [
            { "$tag": "Symbol", "0": "function_definition" },
            { "$tag": "Newline" },
            [
              { "$tag": "Symbol", "0": "function_identifier" },
              { "$tag": "Newline" },
              [{ "$tag": "Symbol", "0": "lowercase_identifier" }],
            ],
          ],
        ],
      ],
      { "$tag": "Newline" },
      [
        { "$tag": "Symbol", "0": "ERROR" },
        [
          { "$tag": "Symbol", "0": "UNEXPECTED" },
          { "$tag": "String", "0": "`" },
        ],
      ],
    ],
  )
}

///|
test "[]" {
  @json.inspect!(
    @sexp.parse!(
      #|[
      #|  (expression)
      #|  (compound_expression)
      #|]
      ,
    ),
    content=[
      [
        { "$tag": "Newline" },
        [{ "$tag": "Symbol", "0": "expression" }],
        { "$tag": "Newline" },
        [{ "$tag": "Symbol", "0": "compound_expression" }],
        { "$tag": "Newline" },
      ],
    ],
  )
}

///|
test "capture" {
  @json.inspect!(
    @sexp.parse!(
      #|(capture) @a
      ,
    ),
    content=[
      [{ "$tag": "Symbol", "0": "capture" }],
      { "$tag": "Capture", "0": "a" },
    ],
  )
}

///|
test "void" {
  @json.inspect!(
    @sexp.parse!(
      #|
      ,
    ),
    content=[],
  )
}

///|
test "unit" {
  @json.inspect!(
    @sexp.parse!(
      #|()
      ,
    ),
    content=[[]],
  )
}

///|
test "pair" {
  @json.inspect!(
    @sexp.parse!(
      #|(key: value)
      ,
    ),
    content=[[{ "key": { "$tag": "Symbol", "0": "value" } }]],
  )
}

///|
test "pair with multiple values" {
  @json.inspect!(
    @sexp.parse!(
      #|(key: value1 value2)
      ,
    ),
    content=[
      [
        { "key": { "$tag": "Symbol", "0": "value1" } },
        { "$tag": "Symbol", "0": "value2" },
      ],
    ],
  )
}

///|
test "comment" {
  @json.inspect!(
    @sexp.parse!(
      #|; comment
      ,
    ),
    content=[{ "$tag": "Comment", "0": " comment" }],
  )
}

///|
test "newline" {
  @json.inspect!(
    @sexp.parse!(
      #|
      #|
      #|(a
      #|
      #|  b)
      ,
    ),
    content=[
      { "$tag": "Newline" },
      { "$tag": "Newline" },
      [
        { "$tag": "Symbol", "0": "a" },
        { "$tag": "Newline" },
        { "$tag": "Newline" },
        { "$tag": "Symbol", "0": "b" },
      ],
    ],
  )
}

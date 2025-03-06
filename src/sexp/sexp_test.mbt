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
        "structure",
        [
          "structure_item",
          [
            "function_definition",
            ["function_identifier", ["lowercase_identifier"]],
          ],
        ],
      ],
      ["ERROR", ["UNEXPECTED", "\"'`'\""]],
    ],
  )
}

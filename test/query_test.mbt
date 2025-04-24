///|
test "query" {
  let parser = @tree_sitter.parser(@tree_sitter_moonbit.language())
  let source =
    #|fn main {
    #|  if 1 == 1 {
    #|    println("Hello, world!")
    #|  }
    #|  for i = 0; i < 10; i = i + 1 {
    #|    println("Hello, world!")
    #|  }
    #|}
  let source_tree = parser.parse_string!(source)
  let query =
    #|(for_expression) @forExpression
  let query_cursor = source_tree.query!(query)
  let captures = []
  for matched in query_cursor.matches() {
    for capture in matched.captures() {
      captures.push(capture)
    }
  }
  @json.inspect!(captures.length(), content=1)
  inspect!(captures[0].name(), content="forExpression")
  inspect!(
    captures[0].node(),
    content=
      #|(for_expression
      #| (for_keyword)
      #| (for_binder
      #|  (lowercase_identifier)
      #|  (expression
      #|   (pipeline_expression
      #|    (compound_expression
      #|     (simple_expression
      #|      (atomic_expression
      #|       (literal
      #|        (integer_literal))))))))
      #| (semicolon)
      #| (compound_expression
      #|  (binary_expression
      #|   (compound_expression
      #|    (simple_expression
      #|     (qualified_identifier
      #|      (lowercase_identifier))))
      #|   (compound_expression
      #|    (simple_expression
      #|     (atomic_expression
      #|      (literal
      #|       (integer_literal)))))))
      #| (semicolon)
      #| (for_binder
      #|  (lowercase_identifier)
      #|  (expression
      #|   (pipeline_expression
      #|    (compound_expression
      #|     (binary_expression
      #|      (compound_expression
      #|       (simple_expression
      #|        (qualified_identifier
      #|         (lowercase_identifier))))
      #|      (compound_expression
      #|       (simple_expression
      #|        (atomic_expression
      #|         (literal
      #|          (integer_literal))))))))))
      #| (block_expression
      #|  (statement_expression
      #|   (expression
      #|    (pipeline_expression
      #|     (compound_expression
      #|      (simple_expression
      #|       (apply_expression
      #|        (simple_expression
      #|         (qualified_identifier
      #|          (lowercase_identifier)))
      #|        (argument
      #|         (expression
      #|          (pipeline_expression
      #|           (compound_expression
      #|            (simple_expression
      #|             (atomic_expression
      #|              (literal
      #|               (string_literal
      #|                (string_fragment
      #|                 (unescaped_string_fragment))))))))))))))))
      #|  (semicolon
      #|   (automatic_semicolon))))
    ,
  )
}

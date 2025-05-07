///|
priv enum Atom {
  Wild
  Type(String)
} derive(Eq, ToJson, Show)

///|
fn Atom::matches(
  self : Atom,
  node : @tree_sitter.Node,
  matches : Array[Match]
) -> Bool {
  match self {
    Wild => {
      matches.push(Match::new(nodes=[node]))
      true
    }
    Type(type_) =>
      if node.type_() == type_ {
        matches.push(Match::new(nodes=[node]))
        true
      } else {
        false
      }
  }
}

///|
priv enum Expr {
  Empty
  Never
  Node(Atom, Expr)
  Concat(Expr, Expr)
  Choice(Expr, Expr)
  Repeat(Expr) // zero-or-more  (*)
  Capture(Expr, name~ : String)
} derive(Eq, ToJson, Show)

///|
priv struct Match {
  nodes : Array[@tree_sitter.Node]
  captures : Map[String, Array[Match]]
} derive(Eq, ToJson, Show)

///|
fn Match::new(
  nodes~ : Array[@tree_sitter.Node] = [],
  captures~ : Map[String, Array[Match]] = {}
) -> Match {
  Match::{ nodes, captures }
}

///|
fn Expr::nullable(self : Expr) -> Bool {
  match self {
    Empty => true
    Never => false
    Atom(_) => false
    Concat(a, b) => a.nullable() && b.nullable()
    Choice(a, b) => a.nullable() || b.nullable()
    Repeat(_) => true
    Capture(expr, name=_) => expr.nullable()
  }
}

///|
fn Expr::concat(self : Expr, other : Expr) -> Expr {
  match (self, other) {
    (Empty(_), result) | (result, Empty(_)) => result
    (Never, _) | (_, Never) => Never
    (Concat(self_0, self_1), other) => Concat(self_0, self_1.concat(other))
    (self, other) => Concat(self, other)
  }
}

///|
fn Expr::choice(self : Expr, other : Expr) -> Expr {
  match (self, other) {
    (Never, result) | (result, Never) => result
    (Choice(self_0, self_1), other) => Choice(self_0, self_1.choice(other))
    (self, other) if self == other => self
    (self, other) => Choice(self, other)
  }
}

///|
fn Expr::deriv(self : Expr, node : @tree_sitter.Node) -> Expr {
  match self {
    Empty => Never
    Never => Never
    Atom(atom) => if atom.matches(node, matches) { Empty } else { Never }
    Concat(e_0, e_1) => {
      let d_0 = e_0.deriv(node, matches)
      if e_0.nullable() {
        d_0.concat(e_1).choice(e_1.deriv(node, matches))
      } else {
        d_0.concat(e_1)
      }
    }
    Choice(e_0, e_1) =>
      e_0.deriv(node, matches).concat(e_1.deriv(node, matches))
    Repeat(e) => e.deriv(node, matches).concat(Repeat(e))
    Capture(e, name~) => {
      let node_matches = []
      let result = Capture(e.deriv(node, node_matches), name~)
      if captures[name] is Some(capture) {
        capture.push(Match::{ matches: node_matches, captures: node_captures })
      } else {
        captures[name] = [
          Match::{ matches: node_matches, captures: node_captures },
        ]
      }
      result
    }
  }
}

///|
fn Expr::matches(
  self : Expr,
  nodes : ArrayView[@tree_sitter.Node],
  matches : Array[Match]
) -> Bool {
  loop self, nodes {
    Never, _ => false
    Capture(deriv, name~), [node, .. nodes] => {
      let matches = []
      let node_captures = {}
      let deriv = deriv.deriv(node, matches, node_captures)
      if captures[name] is Some(capture) {
        capture.push(Capture::{ matches, captures: node_captures })
      } else {
        captures[name] = [Capture::{ matches, captures: node_captures }]
      }
      continue deriv, nodes
    }
    deriv, [node, .. nodes] => {
      let deriv = deriv.deriv(node, matches, captures)
      continue deriv, nodes
    }
    deriv, [] => deriv.nullable()
  }
}

///|
test "expr" {
  let source =
    #|fn main {
    #|  1 == 2
    #|  2 == 3
    #|}
  let parser = @tree_sitter.parser(@tree_sitter_moonbit.language())
  let tree = parser.parse_string!(source)
  let root = tree.root_node()
  inspect!(
    root.string() |> @sexp.prettify!(),
    content=
      #|(structure
      #| (structure_item
      #|  (function_definition
      #|   (function_identifier
      #|    (lowercase_identifier))
      #|   (block_expression
      #|    (statement_expression
      #|     (expression
      #|      (pipeline_expression
      #|       (compound_expression
      #|        (binary_expression
      #|         (compound_expression
      #|          (simple_expression
      #|           (atomic_expression
      #|            (literal
      #|             (integer_literal)))))
      #|         (compound_expression
      #|          (simple_expression
      #|           (atomic_expression
      #|            (literal
      #|             (integer_literal))))))))))
      #|    (semicolon
      #|     (automatic_semicolon))
      #|    (statement_expression
      #|     (expression
      #|      (pipeline_expression
      #|       (compound_expression
      #|        (binary_expression
      #|         (compound_expression
      #|          (simple_expression
      #|           (atomic_expression
      #|            (literal
      #|             (integer_literal)))))
      #|         (compound_expression
      #|          (simple_expression
      #|           (atomic_expression
      #|            (literal
      #|             (integer_literal))))))))))
      #|    (semicolon
      #|     (automatic_semicolon))))))
    ,
  )
  let expr = Expr::Atom(
    "structure",
    Atom(
      "structure_item",
      Capture(
        name="func",
        Atom(
          "function_definition",
          Concat(
            Atom("fn", Empty),
            Concat(
              Capture(name="id", Atom("function_identifier", Wild)),
              Repeat(Wild),
            ),
          ),
        ),
      ),
    ),
  )
  let matches = []
  let captures = {}
  @json.inspect!(expr.matches([root], matches, captures), content=true)
  @json.inspect!(matches, content=[
    {
      "structure": [
        {
          "structure_item": [
            {
              "function_definition": [
                "fn",
                { "function_identifier": ["lowercase_identifier"] },
                {
                  "block_expression": [
                    "{",
                    {
                      "statement_expression": [
                        {
                          "expression": [
                            {
                              "pipeline_expression": [
                                {
                                  "compound_expression": [
                                    {
                                      "binary_expression": [
                                        {
                                          "compound_expression": [
                                            {
                                              "simple_expression": [
                                                {
                                                  "atomic_expression": [
                                                    {
                                                      "literal": [
                                                        "integer_literal",
                                                      ],
                                                    },
                                                  ],
                                                },
                                              ],
                                            },
                                          ],
                                        },
                                        "==",
                                        {
                                          "compound_expression": [
                                            {
                                              "simple_expression": [
                                                {
                                                  "atomic_expression": [
                                                    {
                                                      "literal": [
                                                        "integer_literal",
                                                      ],
                                                    },
                                                  ],
                                                },
                                              ],
                                            },
                                          ],
                                        },
                                      ],
                                    },
                                  ],
                                },
                              ],
                            },
                          ],
                        },
                      ],
                    },
                    { "semicolon": ["automatic_semicolon"] },
                    {
                      "statement_expression": [
                        {
                          "expression": [
                            {
                              "pipeline_expression": [
                                {
                                  "compound_expression": [
                                    {
                                      "binary_expression": [
                                        {
                                          "compound_expression": [
                                            {
                                              "simple_expression": [
                                                {
                                                  "atomic_expression": [
                                                    {
                                                      "literal": [
                                                        "integer_literal",
                                                      ],
                                                    },
                                                  ],
                                                },
                                              ],
                                            },
                                          ],
                                        },
                                        "==",
                                        {
                                          "compound_expression": [
                                            {
                                              "simple_expression": [
                                                {
                                                  "atomic_expression": [
                                                    {
                                                      "literal": [
                                                        "integer_literal",
                                                      ],
                                                    },
                                                  ],
                                                },
                                              ],
                                            },
                                          ],
                                        },
                                      ],
                                    },
                                  ],
                                },
                              ],
                            },
                          ],
                        },
                      ],
                    },
                    { "semicolon": ["automatic_semicolon"] },
                    "}",
                  ],
                },
              ],
            },
          ],
        },
      ],
    },
  ])
  @json.inspect!(captures, content={
    "func": [
      {
        "matches": [
          {
            "function_definition": [
              "fn",
              { "function_identifier": ["lowercase_identifier"] },
              {
                "block_expression": [
                  "{",
                  {
                    "statement_expression": [
                      {
                        "expression": [
                          {
                            "pipeline_expression": [
                              {
                                "compound_expression": [
                                  {
                                    "binary_expression": [
                                      {
                                        "compound_expression": [
                                          {
                                            "simple_expression": [
                                              {
                                                "atomic_expression": [
                                                  {
                                                    "literal": [
                                                      "integer_literal",
                                                    ],
                                                  },
                                                ],
                                              },
                                            ],
                                          },
                                        ],
                                      },
                                      "==",
                                      {
                                        "compound_expression": [
                                          {
                                            "simple_expression": [
                                              {
                                                "atomic_expression": [
                                                  {
                                                    "literal": [
                                                      "integer_literal",
                                                    ],
                                                  },
                                                ],
                                              },
                                            ],
                                          },
                                        ],
                                      },
                                    ],
                                  },
                                ],
                              },
                            ],
                          },
                        ],
                      },
                    ],
                  },
                  { "semicolon": ["automatic_semicolon"] },
                  {
                    "statement_expression": [
                      {
                        "expression": [
                          {
                            "pipeline_expression": [
                              {
                                "compound_expression": [
                                  {
                                    "binary_expression": [
                                      {
                                        "compound_expression": [
                                          {
                                            "simple_expression": [
                                              {
                                                "atomic_expression": [
                                                  {
                                                    "literal": [
                                                      "integer_literal",
                                                    ],
                                                  },
                                                ],
                                              },
                                            ],
                                          },
                                        ],
                                      },
                                      "==",
                                      {
                                        "compound_expression": [
                                          {
                                            "simple_expression": [
                                              {
                                                "atomic_expression": [
                                                  {
                                                    "literal": [
                                                      "integer_literal",
                                                    ],
                                                  },
                                                ],
                                              },
                                            ],
                                          },
                                        ],
                                      },
                                    ],
                                  },
                                ],
                              },
                            ],
                          },
                        ],
                      },
                    ],
                  },
                  { "semicolon": ["automatic_semicolon"] },
                  "}",
                ],
              },
            ],
          },
        ],
        "captures": {
          "id": [
            {
              "matches": [{ "function_identifier": ["lowercase_identifier"] }],
              "captures": {},
            },
            { "matches": [], "captures": {} },
          ],
        },
      },
    ],
  })
}

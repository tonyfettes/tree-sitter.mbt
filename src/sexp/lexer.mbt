///|
struct Lexbuf {
  content : String
  mut pos : Int
}

///|
pub fn Lexbuf::from_string(content : String) -> Lexbuf {
  { content, pos: 0 }
}

// NOTE: MoonBit do have unboxed Option[Char] optimization
///|
fn next(self : Lexbuf) -> Char? {
  if self.pos < self.content.length() {
    let ch = self.content[self.pos]
    self.pos += 1
    Some(ch)
  } else {
    None
  }
}

///|
fn substring(self : Lexbuf, start : Int, end : Int) -> String {
  self.content.substring(start~, end~)
}

///|
typealias LexTagAction = Array[Array[Int]]

///|
typealias LexState = Int

///|
typealias LexInput = Int

///|
pub(all) struct LexEngine {
  graph : Array[(LexState) -> (LexState, LexTagAction)]
  end_nodes : Array[(Int, Array[((Int, Int), (Int, Int))])?]
  start_tags : Array[Int]
  code_blocks_n : Int
}

///|
pub fn run(self : LexEngine, lexbuf : Lexbuf) -> (Int, Array[(Int, Int)]) {
  let mut state = 0
  let mut tagState : Array[Array[Int]] = []
  let backtrace = Array::make(self.code_blocks_n, None)
  for tag in self.start_tags {
    while tagState.length() <= tag {
      tagState.push([])
    }
    tagState[tag].push(lexbuf.pos)
  }
  while state != -1 {
    match self.end_nodes[state] {
      Some(t) => backtrace[t.0] = Some((lexbuf.pos, state, tagState))
      _ => ()
    }
    let b = match lexbuf.next() {
      Some(b) => b.to_int()
      None => -1
    }
    let next = self.graph[state](b)
    state = next.0
    let new_tagState : Array[Array[Int]] = []
    for i = 0; i < next.1.length(); i = i + 1 {
      new_tagState.push([])
      for j = 0; j < next.1[i].length(); j = j + 1 {
        let t = next.1[i][j]
        if t == -1 {
          new_tagState[i].push(lexbuf.pos)
        } else {
          new_tagState[i].push(tagState[i][t])
        }
      }
    }
    tagState = new_tagState
  }
  for index, b in backtrace {
    match b {
      Some((p, state, tagState)) => {
        lexbuf.pos = p
        let captures = self.end_nodes[state].unwrap().1.map(fn {
          ((b_t, b_r), (e_t, e_r)) => (tagState[b_t][b_r], tagState[e_t][e_r])
        })
        break (index, captures)
      }
      None => ()
    }
  } else {
    (self.code_blocks_n, [])
  }
}

///|
enum Token {
  LPAREN
  RPAREN
  LBRACE
  RBRACE
  LBRACKET
  RBRACKET
  COLON
  SYMBOL(String)
  STRING(String)
  EOF
} derive(Eq, Show)

///|
enum TokenKind {
  TK_LPAREN
  TK_RPAREN
  TK_LBRACE
  TK_RBRACE
  TK_LBRACKET
  TK_RBRACKET
  TK_COLON
  TK_SYMBOL
  TK_STRING
  TK_EOF
} derive(Eq, Show)

///|
type! LexError {
  UnterminatedString
  UnrecognizedCharacter(String)
} derive(Show)

///|
let token_tag_action_row_0 : Array[Int] = []

///|
let token_tag_action_row_2 : Array[Int] = [-1]

///|
let token_tag_action_row_1 : Array[Int] = [0]

///|
let token_tag_action_0 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_11 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_1, token_tag_action_row_2,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_5 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_1, token_tag_action_row_2,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_6 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_8 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_1, token_tag_action_row_2,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_7 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_10 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_1, token_tag_action_row_2,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_9 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_4 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_1, token_tag_action_row_2,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_3 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_2 : Array[Array[Int]] = [
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_1, token_tag_action_row_2,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
let token_tag_action_1 : Array[Array[Int]] = [
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0, token_tag_action_row_0,
  token_tag_action_row_1, token_tag_action_row_2, token_tag_action_row_0, token_tag_action_row_0,
]

///|
fn token_state_0(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    0..=8 => (11, token_tag_action_0)
    9..=10 => (3, token_tag_action_0)
    11..=12 => (11, token_tag_action_0)
    13 => (3, token_tag_action_0)
    14..=31 => (11, token_tag_action_0)
    32 => (3, token_tag_action_0)
    33 => (11, token_tag_action_0)
    34 => (8, token_tag_action_1)
    35..=38 => (11, token_tag_action_0)
    39 => (7, token_tag_action_2)
    40 => (1, token_tag_action_3)
    41 => (6, token_tag_action_4)
    42..=47 => (11, token_tag_action_0)
    48..=57 => (5, token_tag_action_5)
    58 => (4, token_tag_action_6)
    59..=64 => (11, token_tag_action_0)
    65..=90 => (5, token_tag_action_5)
    91 => (10, token_tag_action_7)
    92 => (11, token_tag_action_0)
    93 => (12, token_tag_action_8)
    94 => (11, token_tag_action_0)
    95 => (5, token_tag_action_5)
    96 => (11, token_tag_action_0)
    97..=122 => (5, token_tag_action_5)
    123 => (9, token_tag_action_9)
    124 => (11, token_tag_action_0)
    125 => (2, token_tag_action_10)
    126..=1114111 => (11, token_tag_action_0)
    _ => (-1, [])
  }
}

///|
fn token_state_1(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_2(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_3(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_4(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_5(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    48..=57 => (13, token_tag_action_11)
    65..=90 => (13, token_tag_action_11)
    95 => (13, token_tag_action_11)
    97..=122 => (13, token_tag_action_11)
    _ => (-1, [])
  }
}

///|
fn token_state_6(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_7(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_8(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_9(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_10(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_11(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_12(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn token_state_13(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    48..=57 => (13, token_tag_action_11)
    65..=90 => (13, token_tag_action_11)
    95 => (13, token_tag_action_11)
    97..=122 => (13, token_tag_action_11)
    _ => (-1, [])
  }
}

///|
let __mbtlex_engine_token : LexEngine = {
  graph: [
    token_state_0, token_state_1, token_state_2, token_state_3, token_state_4, token_state_5,
    token_state_6, token_state_7, token_state_8, token_state_9, token_state_10, token_state_11,
    token_state_12, token_state_13,
  ],
  end_nodes: [
    Some((12, [((22, 0), (23, 0))])),
    Some((3, [((4, 0), (5, 0))])),
    Some((6, [((10, 0), (11, 0))])),
    Some((0, [])),
    Some((9, [((16, 0), (17, 0))])),
    Some((10, [((18, 0), (19, 0))])),
    Some((4, [((6, 0), (7, 0))])),
    Some((2, [((2, 0), (3, 0))])),
    Some((1, [((0, 0), (1, 0))])),
    Some((5, [((8, 0), (9, 0))])),
    Some((7, [((12, 0), (13, 0))])),
    Some((11, [((20, 0), (21, 0))])),
    Some((8, [((14, 0), (15, 0))])),
    Some((10, [((18, 0), (19, 0))])),
  ],
  start_tags: [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 23],
  code_blocks_n: 13,
}

///|
fn token(lexbuf : Lexbuf) -> (Token, Position, Position)!LexError {
  match __mbtlex_engine_token.run(lexbuf) {
    (0, __mbtlex_captures) => token!(lexbuf)
    (1, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      let buf = StringBuilder::new()
      buf.write_string(t)
      let endpos = double_quoted_string!(buf, lexbuf)
      (STRING(buf.to_string()), _start_pos_of_t, endpos)
    }
    (2, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      let buf = StringBuilder::new()
      buf.write_string(t)
      let endpos = single_quoted_string!(buf, lexbuf)
      (STRING(buf.to_string()), _start_pos_of_t, endpos)
    }
    (3, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      (LPAREN, _start_pos_of_t, _end_pos_of_t)
    }
    (4, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      (RPAREN, _start_pos_of_t, _end_pos_of_t)
    }
    (5, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      (LBRACE, _start_pos_of_t, _end_pos_of_t)
    }
    (6, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      (RBRACE, _start_pos_of_t, _end_pos_of_t)
    }
    (7, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      (LBRACKET, _start_pos_of_t, _end_pos_of_t)
    }
    (8, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      (RBRACKET, _start_pos_of_t, _end_pos_of_t)
    }
    (9, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      (COLON, _start_pos_of_t, _end_pos_of_t)
    }
    (10, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      (SYMBOL(t), _start_pos_of_t, _end_pos_of_t)
    }
    (11, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      raise UnrecognizedCharacter(t)
    }
    (12, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      (EOF, _start_pos_of_t, _end_pos_of_t)
    }
    _ => abort("lex: fail to match")
  }
}

///|
let double_quoted_string_tag_action_row_0 : Array[Int] = []

///|
let double_quoted_string_tag_action_row_2 : Array[Int] = [-1]

///|
let double_quoted_string_tag_action_row_1 : Array[Int] = [0]

///|
let double_quoted_string_tag_action_0 : Array[Array[Int]] = [
  double_quoted_string_tag_action_row_0, double_quoted_string_tag_action_row_0, double_quoted_string_tag_action_row_0,
  double_quoted_string_tag_action_row_0, double_quoted_string_tag_action_row_1, double_quoted_string_tag_action_row_2,
]

///|
let double_quoted_string_tag_action_2 : Array[Array[Int]] = [
  double_quoted_string_tag_action_row_0, double_quoted_string_tag_action_row_0, double_quoted_string_tag_action_row_1,
  double_quoted_string_tag_action_row_0, double_quoted_string_tag_action_row_1, double_quoted_string_tag_action_row_2,
]

///|
let double_quoted_string_tag_action_3 : Array[Array[Int]] = [
  double_quoted_string_tag_action_row_0, double_quoted_string_tag_action_row_0, double_quoted_string_tag_action_row_1,
  double_quoted_string_tag_action_row_2, double_quoted_string_tag_action_row_0, double_quoted_string_tag_action_row_0,
]

///|
let double_quoted_string_tag_action_1 : Array[Array[Int]] = [
  double_quoted_string_tag_action_row_1, double_quoted_string_tag_action_row_2, double_quoted_string_tag_action_row_0,
  double_quoted_string_tag_action_row_0, double_quoted_string_tag_action_row_1, double_quoted_string_tag_action_row_2,
]

///|
fn double_quoted_string_state_0(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    0..=33 => (2, double_quoted_string_tag_action_0)
    34 => (1, double_quoted_string_tag_action_1)
    35..=91 => (2, double_quoted_string_tag_action_0)
    92 => (3, double_quoted_string_tag_action_2)
    93..=1114111 => (2, double_quoted_string_tag_action_0)
    _ => (-1, [])
  }
}

///|
fn double_quoted_string_state_1(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn double_quoted_string_state_2(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn double_quoted_string_state_3(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    34 => (4, double_quoted_string_tag_action_3)
    _ => (-1, [])
  }
}

///|
fn double_quoted_string_state_4(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
let __mbtlex_engine_double_quoted_string : LexEngine = {
  graph: [
    double_quoted_string_state_0, double_quoted_string_state_1, double_quoted_string_state_2,
    double_quoted_string_state_3, double_quoted_string_state_4,
  ],
  end_nodes: [
    Some((3, [])),
    Some((0, [((0, 0), (1, 0))])),
    Some((2, [((4, 0), (5, 0))])),
    Some((2, [((4, 0), (5, 0))])),
    Some((1, [((2, 0), (3, 0))])),
  ],
  start_tags: [0, 2, 4],
  code_blocks_n: 4,
}

///|
fn double_quoted_string(
  buf : StringBuilder,
  lexbuf : Lexbuf
) -> Position!LexError {
  match __mbtlex_engine_double_quoted_string.run(lexbuf) {
    (0, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      buf.write_string(t)
      _end_pos_of_t
    }
    (1, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      buf.write_string(t)
      double_quoted_string!(buf, lexbuf)
    }
    (2, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      buf.write_string(t)
      double_quoted_string!(buf, lexbuf)
    }
    (3, __mbtlex_captures) => raise UnterminatedString
    _ => abort("lex: fail to match")
  }
}

///|
let single_quoted_string_tag_action_row_0 : Array[Int] = []

///|
let single_quoted_string_tag_action_row_2 : Array[Int] = [-1]

///|
let single_quoted_string_tag_action_row_1 : Array[Int] = [0]

///|
let single_quoted_string_tag_action_0 : Array[Array[Int]] = [
  single_quoted_string_tag_action_row_0, single_quoted_string_tag_action_row_0, single_quoted_string_tag_action_row_0,
  single_quoted_string_tag_action_row_0, single_quoted_string_tag_action_row_1, single_quoted_string_tag_action_row_2,
]

///|
let single_quoted_string_tag_action_2 : Array[Array[Int]] = [
  single_quoted_string_tag_action_row_0, single_quoted_string_tag_action_row_0, single_quoted_string_tag_action_row_1,
  single_quoted_string_tag_action_row_0, single_quoted_string_tag_action_row_1, single_quoted_string_tag_action_row_2,
]

///|
let single_quoted_string_tag_action_3 : Array[Array[Int]] = [
  single_quoted_string_tag_action_row_0, single_quoted_string_tag_action_row_0, single_quoted_string_tag_action_row_1,
  single_quoted_string_tag_action_row_2, single_quoted_string_tag_action_row_0, single_quoted_string_tag_action_row_0,
]

///|
let single_quoted_string_tag_action_1 : Array[Array[Int]] = [
  single_quoted_string_tag_action_row_1, single_quoted_string_tag_action_row_2, single_quoted_string_tag_action_row_0,
  single_quoted_string_tag_action_row_0, single_quoted_string_tag_action_row_1, single_quoted_string_tag_action_row_2,
]

///|
fn single_quoted_string_state_0(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    0..=38 => (2, single_quoted_string_tag_action_0)
    39 => (1, single_quoted_string_tag_action_1)
    40..=91 => (2, single_quoted_string_tag_action_0)
    92 => (3, single_quoted_string_tag_action_2)
    93..=1114111 => (2, single_quoted_string_tag_action_0)
    _ => (-1, [])
  }
}

///|
fn single_quoted_string_state_1(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn single_quoted_string_state_2(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
fn single_quoted_string_state_3(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    39 => (4, single_quoted_string_tag_action_3)
    _ => (-1, [])
  }
}

///|
fn single_quoted_string_state_4(input : LexInput) -> (LexState, LexTagAction) {
  match input {
    _ => (-1, [])
  }
}

///|
let __mbtlex_engine_single_quoted_string : LexEngine = {
  graph: [
    single_quoted_string_state_0, single_quoted_string_state_1, single_quoted_string_state_2,
    single_quoted_string_state_3, single_quoted_string_state_4,
  ],
  end_nodes: [
    Some((3, [])),
    Some((0, [((0, 0), (1, 0))])),
    Some((2, [((4, 0), (5, 0))])),
    Some((2, [((4, 0), (5, 0))])),
    Some((1, [((2, 0), (3, 0))])),
  ],
  start_tags: [0, 2, 4],
  code_blocks_n: 4,
}

///|
fn single_quoted_string(
  buf : StringBuilder,
  lexbuf : Lexbuf
) -> Position!LexError {
  match __mbtlex_engine_single_quoted_string.run(lexbuf) {
    (0, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      ignore(t)
      buf.write_string(t)
      _end_pos_of_t
    }
    (1, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      buf.write_string(t)
      single_quoted_string!(buf, lexbuf)
    }
    (2, __mbtlex_captures) => {
      let (_start_pos_of_t, _end_pos_of_t) = __mbtlex_captures[0]
      let t : String = lexbuf.substring(_start_pos_of_t, _end_pos_of_t)
      buf.write_string(t)
      single_quoted_string!(buf, lexbuf)
    }
    (3, __mbtlex_captures) => raise UnterminatedString
    _ => abort("lex: fail to match")
  }
}

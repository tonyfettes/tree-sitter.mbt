///|
pub(all) typealias Position = Int

///|
pub type! ParseError {
  UnexpectedToken(Token, (Position, Position), Array[TokenKind])
  UnexpectedEndOfInput(Position, Array[TokenKind])
} derive(Show)

///|
typealias YYObj = Error

///|
priv type! YYObj_Void

///|
priv type! YYObj_Atom Atom

///|
priv type! YYObj_Sexp Sexp

///|
priv type! YYObj_Array_Sexp_ Array[Sexp]

///|
priv type! YYObj_String String

///|
typealias YYState = (YYSymbol) -> YYDecision

///|
typealias YYAction = (Position, ArrayView[(YYObj, Position, Position)]) -> YYObj

///|
priv enum YYDecision {
  Accept
  Shift(YYState)
  Reduce(Int, YYSymbol, YYAction)
  ReduceNoLookahead(Int, YYSymbol, YYAction)
  Error
}

///|
priv enum YYSymbol {
  T_LPAREN
  T_RPAREN
  T_LBRACE
  T_RBRACE
  T_LBRACKET
  T_RBRACKET
  T_COLON
  T_EOF
  T_STRING
  T_SYMBOL
  NT_start
  NT_list
  NT_sexp
  NT_atom
  EOI
}

// Workaround for EOI unused warning
///|
fn init {
  match (EOI : YYSymbol) {
    EOI => ()
    _ => ()
  }
}

///|
fn yy_action_0(
  _last_pos : Position,
  _args : ArrayView[(YYObj, Position, Position)]
) -> YYObj {
  guard _args[0].0 is YYObj_String(key)
  guard _args[2].0 is YYObj_Sexp(value)
  YYObj_Sexp(
    {
      ()
      Pair(key, value)
    },
  )
}

///|
fn yy_action_1(
  _last_pos : Position,
  _args : ArrayView[(YYObj, Position, Position)]
) -> YYObj {
  guard _args[1].0 is YYObj_Array_Sexp_(s)
  YYObj_Sexp(
    {
      ()
      List(s)
    },
  )
}

///|
fn yy_action_2(
  _last_pos : Position,
  _args : ArrayView[(YYObj, Position, Position)]
) -> YYObj {
  guard _args[0].0 is YYObj_String(_dollar1)
  YYObj_Atom(
    {
      ()
      Symbol(_dollar1)
    },
  )
}

///|
fn yy_action_3(
  _last_pos : Position,
  _args : ArrayView[(YYObj, Position, Position)]
) -> YYObj {
  YYObj_Array_Sexp_(
    {
      ()
      []
    },
  )
}

///|
fn yy_action_4(
  _last_pos : Position,
  _args : ArrayView[(YYObj, Position, Position)]
) -> YYObj {
  guard _args[0].0 is YYObj_Array_Sexp_(s)
  YYObj_Array_Sexp_(
    {
      ()
      s
    },
  )
}

///|
fn yy_action_5(
  _last_pos : Position,
  _args : ArrayView[(YYObj, Position, Position)]
) -> YYObj {
  guard _args[0].0 is YYObj_Sexp(s)
  guard _args[1].0 is YYObj_Array_Sexp_(l)
  YYObj_Array_Sexp_(
    {
      ()
      [s, ..l]
    },
  )
}

///|
fn yy_action_6(
  _last_pos : Position,
  _args : ArrayView[(YYObj, Position, Position)]
) -> YYObj {
  guard _args[0].0 is YYObj_Atom(atom)
  YYObj_Sexp(
    {
      ()
      Atom(atom)
    },
  )
}

///|
fn yy_action_7(
  _last_pos : Position,
  _args : ArrayView[(YYObj, Position, Position)]
) -> YYObj {
  guard _args[1].0 is YYObj_Array_Sexp_(s)
  YYObj_Sexp(
    {
      ()
      List(s)
    },
  )
}

///|
fn yy_action_8(
  _last_pos : Position,
  _args : ArrayView[(YYObj, Position, Position)]
) -> YYObj {
  guard _args[1].0 is YYObj_Array_Sexp_(s)
  YYObj_Sexp(
    {
      ()
      List(s)
    },
  )
}

///|
fn yy_action_9(
  _last_pos : Position,
  _args : ArrayView[(YYObj, Position, Position)]
) -> YYObj {
  guard _args[0].0 is YYObj_String(_dollar1)
  YYObj_Atom(
    {
      ()
      String(_dollar1)
    },
  )
}

///|
fn yy_input(
  token : Token,
  _start_pos : Position,
  _end_pos : Position
) -> (YYSymbol, YYObj) {
  match token {
    LPAREN => (T_LPAREN, YYObj_Void)
    RPAREN => (T_RPAREN, YYObj_Void)
    LBRACE => (T_LBRACE, YYObj_Void)
    RBRACE => (T_RBRACE, YYObj_Void)
    LBRACKET => (T_LBRACKET, YYObj_Void)
    RBRACKET => (T_RBRACKET, YYObj_Void)
    COLON => (T_COLON, YYObj_Void)
    EOF => (T_EOF, YYObj_Void)
    STRING(data) => (T_STRING, YYObj_String(data))
    SYMBOL(data) => (T_SYMBOL, YYObj_String(data))
  }
}

// [0, start → • list EOF, $]
// [1, list → •, EOF]
// [2, list → • sexp list, EOF]
// [3, sexp → • LPAREN list RPAREN, LPAREN / LBRACE / LBRACKET / EOF / STRING / SYMBOL]
// [4, sexp → • LBRACKET list RBRACKET, LPAREN / LBRACE / LBRACKET / EOF / STRING / SYMBOL]
// [5, sexp → • LBRACE list RBRACE, LPAREN / LBRACE / LBRACKET / EOF / STRING / SYMBOL]
// [6, sexp → • atom, LPAREN / LBRACE / LBRACKET / EOF / STRING / SYMBOL]
// [7, sexp → • SYMBOL COLON sexp, LPAREN / LBRACE / LBRACKET / EOF / STRING / SYMBOL]
// [8, atom → • STRING, LPAREN / LBRACE / LBRACKET / EOF / STRING / SYMBOL]
// [9, atom → • SYMBOL, LPAREN / LBRACE / LBRACKET / EOF / STRING / SYMBOL]
// [10, start_prime → • start, $]
///|
fn yy_state_0(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    NT_start => Shift(yy_state_1)
    T_STRING => Shift(yy_state_2)
    T_SYMBOL => Shift(yy_state_3)
    NT_atom => Shift(yy_state_6)
    T_LBRACE => Shift(yy_state_7)
    T_LBRACKET => Shift(yy_state_10)
    T_LPAREN => Shift(yy_state_13)
    NT_sexp => Shift(yy_state_16)
    NT_list => Shift(yy_state_18)
    T_EOF => Reduce(0, NT_list, yy_action_3)
    _ => Error
  }
}

// [10, start_prime → start •, $]
///|
fn yy_state_1(_lookahead : YYSymbol) -> YYDecision {
  Accept
}

// [8, atom → STRING •, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_2(_lookahead : YYSymbol) -> YYDecision {
  ReduceNoLookahead(1, NT_atom, yy_action_9)
}

// [7, sexp → SYMBOL • COLON sexp, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [9, atom → SYMBOL •, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_3(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    T_COLON => Shift(yy_state_4)
    T_LPAREN
    | T_RPAREN
    | T_LBRACE
    | T_RBRACE
    | T_LBRACKET
    | T_RBRACKET
    | T_EOF
    | T_STRING
    | T_SYMBOL => Reduce(1, NT_atom, yy_action_2)
    _ => Error
  }
}

// [3, sexp → • LPAREN list RPAREN, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [4, sexp → • LBRACKET list RBRACKET, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [5, sexp → • LBRACE list RBRACE, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [6, sexp → • atom, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [7, sexp → • SYMBOL COLON sexp, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [7, sexp → SYMBOL COLON • sexp, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [8, atom → • STRING, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [9, atom → • SYMBOL, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_4(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    T_STRING => Shift(yy_state_2)
    T_SYMBOL => Shift(yy_state_3)
    NT_sexp => Shift(yy_state_5)
    NT_atom => Shift(yy_state_6)
    T_LBRACE => Shift(yy_state_7)
    T_LBRACKET => Shift(yy_state_10)
    T_LPAREN => Shift(yy_state_13)
    _ => Error
  }
}

// [7, sexp → SYMBOL COLON sexp •, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_5(_lookahead : YYSymbol) -> YYDecision {
  ReduceNoLookahead(3, NT_sexp, yy_action_0)
}

// [6, sexp → atom •, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_6(_lookahead : YYSymbol) -> YYDecision {
  ReduceNoLookahead(1, NT_sexp, yy_action_6)
}

// [1, list → •, RBRACE]
// [2, list → • sexp list, RBRACE]
// [3, sexp → • LPAREN list RPAREN, LPAREN / LBRACE / RBRACE / LBRACKET / STRING / SYMBOL]
// [4, sexp → • LBRACKET list RBRACKET, LPAREN / LBRACE / RBRACE / LBRACKET / STRING / SYMBOL]
// [5, sexp → • LBRACE list RBRACE, LPAREN / LBRACE / RBRACE / LBRACKET / STRING / SYMBOL]
// [5, sexp → LBRACE • list RBRACE, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [6, sexp → • atom, LPAREN / LBRACE / RBRACE / LBRACKET / STRING / SYMBOL]
// [7, sexp → • SYMBOL COLON sexp, LPAREN / LBRACE / RBRACE / LBRACKET / STRING / SYMBOL]
// [8, atom → • STRING, LPAREN / LBRACE / RBRACE / LBRACKET / STRING / SYMBOL]
// [9, atom → • SYMBOL, LPAREN / LBRACE / RBRACE / LBRACKET / STRING / SYMBOL]
///|
fn yy_state_7(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    T_STRING => Shift(yy_state_2)
    T_SYMBOL => Shift(yy_state_3)
    NT_atom => Shift(yy_state_6)
    T_LBRACE => Shift(yy_state_7)
    NT_list => Shift(yy_state_8)
    T_LBRACKET => Shift(yy_state_10)
    T_LPAREN => Shift(yy_state_13)
    NT_sexp => Shift(yy_state_16)
    T_RBRACE => Reduce(0, NT_list, yy_action_3)
    _ => Error
  }
}

// [5, sexp → LBRACE list • RBRACE, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_8(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    T_RBRACE => Shift(yy_state_9)
    _ => Error
  }
}

// [5, sexp → LBRACE list RBRACE •, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_9(_lookahead : YYSymbol) -> YYDecision {
  ReduceNoLookahead(3, NT_sexp, yy_action_1)
}

// [1, list → •, RBRACKET]
// [2, list → • sexp list, RBRACKET]
// [3, sexp → • LPAREN list RPAREN, LPAREN / LBRACE / LBRACKET / RBRACKET / STRING / SYMBOL]
// [4, sexp → • LBRACKET list RBRACKET, LPAREN / LBRACE / LBRACKET / RBRACKET / STRING / SYMBOL]
// [4, sexp → LBRACKET • list RBRACKET, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [5, sexp → • LBRACE list RBRACE, LPAREN / LBRACE / LBRACKET / RBRACKET / STRING / SYMBOL]
// [6, sexp → • atom, LPAREN / LBRACE / LBRACKET / RBRACKET / STRING / SYMBOL]
// [7, sexp → • SYMBOL COLON sexp, LPAREN / LBRACE / LBRACKET / RBRACKET / STRING / SYMBOL]
// [8, atom → • STRING, LPAREN / LBRACE / LBRACKET / RBRACKET / STRING / SYMBOL]
// [9, atom → • SYMBOL, LPAREN / LBRACE / LBRACKET / RBRACKET / STRING / SYMBOL]
///|
fn yy_state_10(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    T_STRING => Shift(yy_state_2)
    T_SYMBOL => Shift(yy_state_3)
    NT_atom => Shift(yy_state_6)
    T_LBRACE => Shift(yy_state_7)
    T_LBRACKET => Shift(yy_state_10)
    NT_list => Shift(yy_state_11)
    T_LPAREN => Shift(yy_state_13)
    NT_sexp => Shift(yy_state_16)
    T_RBRACKET => Reduce(0, NT_list, yy_action_3)
    _ => Error
  }
}

// [4, sexp → LBRACKET list • RBRACKET, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_11(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    T_RBRACKET => Shift(yy_state_12)
    _ => Error
  }
}

// [4, sexp → LBRACKET list RBRACKET •, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_12(_lookahead : YYSymbol) -> YYDecision {
  ReduceNoLookahead(3, NT_sexp, yy_action_8)
}

// [1, list → •, RPAREN]
// [2, list → • sexp list, RPAREN]
// [3, sexp → • LPAREN list RPAREN, LPAREN / RPAREN / LBRACE / LBRACKET / STRING / SYMBOL]
// [3, sexp → LPAREN • list RPAREN, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [4, sexp → • LBRACKET list RBRACKET, LPAREN / RPAREN / LBRACE / LBRACKET / STRING / SYMBOL]
// [5, sexp → • LBRACE list RBRACE, LPAREN / RPAREN / LBRACE / LBRACKET / STRING / SYMBOL]
// [6, sexp → • atom, LPAREN / RPAREN / LBRACE / LBRACKET / STRING / SYMBOL]
// [7, sexp → • SYMBOL COLON sexp, LPAREN / RPAREN / LBRACE / LBRACKET / STRING / SYMBOL]
// [8, atom → • STRING, LPAREN / RPAREN / LBRACE / LBRACKET / STRING / SYMBOL]
// [9, atom → • SYMBOL, LPAREN / RPAREN / LBRACE / LBRACKET / STRING / SYMBOL]
///|
fn yy_state_13(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    T_STRING => Shift(yy_state_2)
    T_SYMBOL => Shift(yy_state_3)
    NT_atom => Shift(yy_state_6)
    T_LBRACE => Shift(yy_state_7)
    T_LBRACKET => Shift(yy_state_10)
    T_LPAREN => Shift(yy_state_13)
    NT_list => Shift(yy_state_14)
    NT_sexp => Shift(yy_state_16)
    T_RPAREN => Reduce(0, NT_list, yy_action_3)
    _ => Error
  }
}

// [3, sexp → LPAREN list • RPAREN, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_14(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    T_RPAREN => Shift(yy_state_15)
    _ => Error
  }
}

// [3, sexp → LPAREN list RPAREN •, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_15(_lookahead : YYSymbol) -> YYDecision {
  ReduceNoLookahead(3, NT_sexp, yy_action_7)
}

// [1, list → •, RPAREN / RBRACE / RBRACKET / EOF]
// [2, list → • sexp list, RPAREN / RBRACE / RBRACKET / EOF]
// [2, list → sexp • list, RPAREN / RBRACE / RBRACKET / EOF]
// [3, sexp → • LPAREN list RPAREN, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [4, sexp → • LBRACKET list RBRACKET, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [5, sexp → • LBRACE list RBRACE, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [6, sexp → • atom, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [7, sexp → • SYMBOL COLON sexp, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [8, atom → • STRING, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
// [9, atom → • SYMBOL, LPAREN / RPAREN / LBRACE / RBRACE / LBRACKET / RBRACKET / EOF / STRING / SYMBOL]
///|
fn yy_state_16(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    T_STRING => Shift(yy_state_2)
    T_SYMBOL => Shift(yy_state_3)
    NT_atom => Shift(yy_state_6)
    T_LBRACE => Shift(yy_state_7)
    T_LBRACKET => Shift(yy_state_10)
    T_LPAREN => Shift(yy_state_13)
    NT_sexp => Shift(yy_state_16)
    NT_list => Shift(yy_state_17)
    T_RPAREN | T_RBRACE | T_RBRACKET | T_EOF => Reduce(0, NT_list, yy_action_3)
    _ => Error
  }
}

// [2, list → sexp list •, RPAREN / RBRACE / RBRACKET / EOF]
///|
fn yy_state_17(_lookahead : YYSymbol) -> YYDecision {
  ReduceNoLookahead(2, NT_list, yy_action_5)
}

// [0, start → list • EOF, $]
///|
fn yy_state_18(_lookahead : YYSymbol) -> YYDecision {
  match _lookahead {
    T_EOF => Shift(yy_state_19)
    _ => Error
  }
}

// [0, start → list EOF •, $]
///|
fn yy_state_19(_lookahead : YYSymbol) -> YYDecision {
  ReduceNoLookahead(2, NT_start, yy_action_4)
}

///|
fn yy_parse[T](
  tokens : Array[(Token, Position, Position)],
  start : YYState,
  return_ : (YYObj) -> T,
  initial_pos? : Position
) -> T!ParseError {
  let mut cursor = 0
  let mut state_stack : @immut/list.T[YYState] = Cons(start, Nil)
  let data_stack : Array[(YYObj, Position, Position)] = []
  let mut last_pos = initial_pos.or(tokens[0].1)
  let mut state = start
  let mut lookahead : (YYSymbol, (YYObj, Position, Position), Token?)? = None
  let mut last_shifted_state_stack = state_stack
  while true {
    let decision = match state(EOI) {
      ReduceNoLookahead(_) | Accept as t => t
      _ =>
        match lookahead {
          Some(la) => state(la.0)
          None =>
            if cursor < tokens.length() {
              let (token, start_pos, end_pos) = tokens[cursor]
              cursor += 1
              let (symbol, data) = yy_input(token, start_pos, end_pos)
              lookahead = Some(
                (symbol, (data, start_pos, end_pos), Some(token)),
              )
              state(symbol)
            } else {
              lookahead = Some((EOI, (YYObj_Void, last_pos, last_pos), None))
              state(EOI)
            }
        }
    }
    match decision {
      Accept => return return_(data_stack.unsafe_pop().0)
      Shift(next_state) => {
        guard lookahead is Some(la)
        data_stack.push(la.1)
        state_stack = Cons(next_state, state_stack)
        last_shifted_state_stack = state_stack
        state = next_state
        last_pos = la.1.2
        lookahead = None
      }
      Reduce(count, symbol, action)
      | ReduceNoLookahead(count, symbol, action) =>
        loop (count, symbol, action) {
          _ => {
            let args = data_stack[data_stack.length() - count:]
            let data = action(last_pos, args)
            let (start_pos, end_pos) = if args.length() == 0 {
              (last_pos, last_pos)
            } else {
              (args[0].1, args[args.length() - 1].2)
            }
            for i in 0..<count {
              ignore(data_stack.unsafe_pop())
              state_stack = state_stack.tail()
            }
            state = state_stack.unsafe_head()
            data_stack.push((data, start_pos, end_pos))
            match state(symbol) {
              Accept => return return_(data_stack.unsafe_pop().0)
              Shift(next_state) => {
                state_stack = Cons(next_state, state_stack)
                state = next_state
              }
              Reduce(count, symbol, action)
              | ReduceNoLookahead(count, symbol, action) =>
                continue (count, symbol, action)
              _ => panic()
            }
          }
        }
      Error => {
        let (_, (_, start_pos, end_pos), token) = lookahead.unwrap()
        error!(last_shifted_state_stack, token, (start_pos, end_pos))
      }
    }
  }
  panic()
}

///|
fn error(
  stack : @immut/list.T[YYState],
  token : Token?,
  loc : (Position, Position)
) -> Unit!ParseError {
  let expected = []
  fn try_add(symbol : YYSymbol, kind : TokenKind) {
    fn go(stack : @immut/list.T[YYState]) {
      match stack {
        Nil => ()
        Cons(state, _) =>
          match state(symbol) {
            Accept | Shift(_) => expected.push(kind)
            Reduce(count, symbol, _) | ReduceNoLookahead(count, symbol, _) => {
              fn inner_go(stack : @immut/list.T[YYState], count, symbol) {
                let stack = stack.drop(count)
                guard stack is Cons(state, _)
                match state(symbol) {
                  Shift(state) => go(Cons(state, stack))
                  Reduce(count, symbol, _)
                  | ReduceNoLookahead(count, symbol, _) =>
                    inner_go(stack, count, symbol)
                  _ => panic()
                }
              }

              inner_go(stack, count, symbol)
            }
            Error => ()
          }
      }
    }

    go(stack)
  }

  for
    term in (
      [
        (T_LPAREN, TK_LPAREN),
        (T_RPAREN, TK_RPAREN),
        (T_LBRACE, TK_LBRACE),
        (T_RBRACE, TK_RBRACE),
        (T_LBRACKET, TK_LBRACKET),
        (T_RBRACKET, TK_RBRACKET),
        (T_COLON, TK_COLON),
        (T_EOF, TK_EOF),
        (T_STRING, TK_STRING),
        (T_SYMBOL, TK_SYMBOL),
      ] : Array[(YYSymbol, TokenKind)]) {
    try_add(term.0, term.1)
  }
  match token {
    None => raise UnexpectedEndOfInput(loc.1, expected)
    Some(token) => raise UnexpectedToken(token, loc, expected)
  }
}

///|
pub fn start(
  tokens : Array[(Token, Position, Position)],
  initial_pos? : Position
) -> Array[Sexp]!ParseError {
  yy_parse!(
    tokens,
    yy_state_0,
    fn {
      YYObj_Array_Sexp_(result) => result
      _ => panic()
    },
    initial_pos?,
  )
}

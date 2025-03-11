///|
pub enum Atom {
  Symbol(String)
  String(String)
} derive(Eq)

///|
pub impl ToJson for Atom with to_json(self : Atom) -> Json {
  match self {
    Symbol(symbol) => symbol.to_json()
    String(string) => string.escape().to_json()
  }
}

pub impl Show for Atom with output(self : Atom, logger : &Logger) -> Unit {
  match self {
    Symbol(symbol) => logger.write_string(symbol)
    String(string) => logger.write_string(string.escape())
  }
}

///|
pub enum Sexp {
  Atom(Atom)
  Pair(String, Sexp)
  List(Array[Sexp])
} derive(Eq, Show)

///|
pub impl ToJson for Sexp with to_json(self : Sexp) -> Json {
  match self {
    Atom(atom) => atom.to_json()
    Pair(key, value) => {
      let object = {}
      object[key] = value.to_json()
      Object(object)
    }
    List(list) => list.to_json()
  }
}

///|
pub type! SexpError {
  LexError(LexError)
  ParseError(ParseError)
}

///|
pub fn parse(source : String) -> Array[Sexp]!SexpError {
  let lexer = Lexbuf::from_string(source)
  let tokens = []
  while true {
    try {
      match token!(lexer) {
        (EOF, _, _) as token => {
          tokens.push(token)
          break
        }
        token => tokens.push(token)
      }
    } catch {
      error => raise LexError(error)
    }
  }
  try {
    start!(tokens)
  } catch {
    error => raise ParseError(error)
  }
}

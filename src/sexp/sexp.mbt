///|
enum Atom {
  Number(Double)
  Symbol(String)
  String(String)
} derive(Eq, Show)

///|
pub impl ToJson for Atom with to_json(self : Atom) -> Json {
  match self {
    Symbol(symbol) => symbol.to_json()
    Number(number) => number.to_json()
    String(string) => string.escape().to_json()
  }
}

///|
enum Sexp {
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

///|
pub enum Atom {
  Symbol(String)
  String(String)
  Capture(String)
  Command(String)
} derive(Eq)

///|
pub impl ToJson for Atom with to_json(self : Atom) -> Json {
  match self {
    Symbol(symbol) => symbol.to_json()
    String(string) => string.escape().to_json()
    Capture(capture) => "@\{capture}".to_json()
    Command(command) => "#\{command}".to_json()
  }
}

///|
pub impl Show for Atom with output(self : Atom, logger : &Logger) -> Unit {
  match self {
    Symbol(symbol) => logger.write_string(symbol)
    String(string) => logger.write_string(string.escape())
    Capture(capture) => {
      logger.write_char('@')
      logger.write_string(capture)
    }
    Command(command) => {
      logger.write_char('#')
      logger.write_string(command)
    }
  }
}

///|
pub enum Sexp {
  Atom(Atom)
  Pair(String, Sexp)
  List(Char, Array[Sexp], Char)
} derive(Eq, Show)

///|
pub impl ToJson for Sexp with to_json(self : Sexp) -> Json {
  match self {
    Atom(atom) => atom.to_json()
    Pair(key, value) => {
      let object = {}
      object[key] = value.to_json()
      Json::object(object)
    }
    List(_, list, _) => list.to_json()
  }
}

///|
pub enum Atom {
  Symbol(String)
  String(String)
  Capture(String)
  Command(String)
  Comment(String)
  Newline
} derive(Eq, ToJson)

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
    Comment(comment) => {
      logger.write_char(';')
      logger.write_string(comment)
    }
    Newline => logger.write_char('\n')
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

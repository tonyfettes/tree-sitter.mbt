///|
pub fn print_to(
  list : Array[Sexp],
  logger : &Logger,
  indent~ : Int = 0
) -> Unit {
  for i, sexp in list {
    if sexp is Atom(Capture(_)) {
      logger.write_char(' ')
    } else if i > 0 {
      logger.write_string("\n")
      for _ in 0..<indent {
        logger.write_char(' ')
      }
    }
    sexp.print(logger, indent~)
    if sexp is Atom(Comment(_)) && i == list.length() - 1 {
      logger.write_char('\n')
    }
  }
}

///|
pub fn print(list : Array[Sexp]) -> String {
  let buffer = StringBuilder::new()
  print_to(list, buffer)
  return buffer.to_string()
}

///|
pub fn Sexp::print(self : Sexp, logger : &Logger, indent~ : Int = 0) -> Unit {
  match self {
    Atom(atom) => logger.write_object(atom)
    Pair(key, value) => {
      logger.write_string(key)
      logger.write_string(": ")
      value.print(logger, indent=indent + key.length() + 2)
    }
    List(open, list, close) => {
      logger.write_char(open)
      print_to(list, logger, indent=indent + 1)
      logger.write_char(close)
    }
  }
}

///|
test "print" {
  let sexp : Sexp = List(
    '(',
    [
      Atom(Symbol("a")),
      Atom(String("b")),
      Pair("c", List('(', [Atom(Symbol("d")), Atom(String("e"))], ')')),
    ],
    ')',
  )
  let buffer = StringBuilder::new()
  sexp.print(buffer)
  inspect!(
    buffer,
    content=
      #|(a
      #| "b"
      #| c: (d
      #|     "e"))
    ,
  )
}

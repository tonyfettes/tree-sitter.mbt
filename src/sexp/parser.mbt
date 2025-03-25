///|
pub type! SexpError {
  UnrecognizedCharacter(@string.View)
  UnterminatedString(@string.View)
  UnterminatedList(@string.View)
  MissingValue(@string.View)
  ExtraContent(@array.View[Sexp])
} derive(Show)

///|
fn parse_list(
  source : @string.View,
  sexp : Array[Sexp]
) -> @string.View!SexpError {
  fn parse_string(
    source : @string.View,
    string : StringBuilder,
    quote : Char
  ) -> @string.View!SexpError {
    loop source {
      ['\\', '\\', .. source] => {
        string.write_char('\\')
        continue source
      }
      ['\\', char, .. source] if char == quote => {
        string.write_char(char)
        continue source
      }
      [char, .. source] if char == quote => return source
      [char, .. source] => {
        string.write_char(char)
        continue source
      }
      [] as source => raise SexpError::UnterminatedString(source)
    }
  }

  fn parse_symbol(
    source : @string.View,
    symbol : StringBuilder
  ) -> @string.View {
    loop source {
      ['a'..<'z' | 'A'..<'Z' | '0'..<'9' | '_' as char, .. source] => {
        symbol.write_char(char)
        continue source
      }
      source => return source
    }
  }

  loop source {
    [' ' | '\t' | '\r' | '\n', .. source] => continue source
    ['\'' | '"' as quote, .. source] => {
      let string = StringBuilder::new()
      let source = parse_string!(source, string, quote)
      sexp.push(Atom(String(string.to_string())))
      continue source
    }
    ['(', .. source] => {
      let list = []
      sexp.push(List(list))
      match parse_list!(source, list) {
        [')', .. source] => continue source
        source => raise SexpError::UnterminatedList(source)
      }
    }
    ['[', .. source] => {
      let list = []
      sexp.push(List(list))
      match parse_list!(source, list) {
        [']', .. source] => continue source
        source => raise SexpError::UnterminatedList(source)
      }
    }
    ['{', .. source] => {
      let list = []
      sexp.push(List(list))
      match parse_list!(source, list) {
        ['}', .. source] => continue source
        source => raise SexpError::UnterminatedList(source)
      }
    }
    ['a'..<'z' | 'A'..<'Z' | '0'..<'9' | '_' as char, .. source] => {
      let symbol = StringBuilder::new()
      symbol.write_char(char)
      match parse_symbol(source, symbol) {
        [':', .. source] => {
          let list = []
          let source = parse_list!(source, list)
          match list {
            [item, .. list] => {
              sexp.push(Pair(symbol.to_string(), item))
              for item in list {
                sexp.push(item)
              }
              continue source
            }
            [] => raise SexpError::MissingValue(source)
          }
        }
        source => {
          sexp.push(Atom(Symbol(symbol.to_string())))
          continue source
        }
      }
    }
    source => return source
  }
}

///|
pub fn Sexp::parse(source : String) -> Sexp!SexpError {
  let list = []
  let source = parse_list!(source.view(), list)
  if source is [_, ..] {
    raise SexpError::UnrecognizedCharacter(source)
  }
  match list {
    [sexp] => return sexp
    [_, .. list] => raise SexpError::ExtraContent(list)
    [] => raise SexpError::UnrecognizedCharacter(source)
  }
}

///|
pub fn parse(source : String) -> Array[Sexp]!SexpError {
  let list = []
  let source = parse_list!(source.view(), list)
  match source {
    [_, ..] => raise SexpError::UnrecognizedCharacter(source)
    [] => return list
  }
}

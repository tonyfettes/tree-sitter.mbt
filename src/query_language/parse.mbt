///|
priv struct Range {
  start : Int
  end : Int
} derive(Show)

///|
fn Range::new(start : Int, end : Int) -> Range {
  Range::{ start, end }
}

///|
type! ParseError {
  ParseError(Array[@tree_sitter.ParseError])
  UnrecognizedCharacter(Range, Char)
  UnterminatedGroup(Range)
  MissingColon(Range)
  ConflictingMatch(Range, String, String)
  UnrecognizedEntry(Range, String)
} derive(Show)

///|
priv enum Query {
  Group(String, Range, Array[Query])
  Match(String, Range, String)
} derive(Show)

///|
fn Query::range(self : Query) -> Range {
  match self {
    Group(_, range, _) => range
    Match(_, range, _) => range
  }
}

///|
fn Query::name(self : Query) -> String {
  match self {
    Group(name, _, _) => name
    Match(name, _, _) => name
  }
}

///|
priv enum GroupState {
  Empty(children~ : Array[Query])
  Group(
    state~ : GroupState,
    children~ : Array[Query],
    ident~ : String,
    start~ : Int
  )
}

///|
fn GroupState::children(self : GroupState) -> Array[Query] {
  match self {
    Empty(children~) => children
    Group(children~, ..) => children
  }
}

///|
fn GroupState::to_parse_state(self : GroupState) -> ParseState {
  match self {
    Empty(children~) => ParseState::Empty(children~)
    Group(state~, children~, ident~, start~) =>
      ParseState::Group(state~, children~, ident~, start~)
  }
}

///|
priv enum ParseState {
  Empty(children~ : Array[Query])
  Group(
    state~ : GroupState,
    children~ : Array[Query],
    ident~ : String,
    start~ : Int
  )
  Ident(state~ : GroupState, buffer~ : StringBuilder)
  Match(
    state~ : GroupState,
    ident~ : String,
    start~ : Int,
    buffer~ : StringBuilder
  )
}

///|
priv struct Context {
  prefix : @string.View
  suffix : @string.View
}

///|
fn Context::new!(context : @string.View) -> Context!ParserCreationError {
  let prefix = StringBuilder::new()
  loop context {
    ['$', .. context] =>
      return Context::{ prefix: prefix.to_string(), suffix: context }
    [.. "\\$", .. context] => {
      prefix.write_char('$')
      continue context
    }
    [char, .. context] => {
      prefix.write_char(char)
      continue context
    }
    [] => raise MissingContextInterpolator
  }
}

///|
struct Entry {
  query : String
  placeholder : String
}

///|
pub fn Entry::new(query~ : String, placeholder~ : String) -> Entry {
  Entry::{ query, placeholder }
}

///|
struct Parser {
  language : @tree_sitter.Language
  contexts : Map[String, Context]
  entries : Map[String, Entry]
  extras : Set[String]
}

///|
type! ParserCreationError {
  MissingContextInterpolator
}

///|
pub fn Parser::new(
  language : @tree_sitter.Language,
  contexts~ : Map[String, String],
  entries~ : Map[String, Entry],
  extras~ : Array[String] = []
) -> Parser!ParserCreationError {
  let parsed_contexts = Map::new(capacity=contexts.size())
  for name, context in contexts {
    let context = Context::new!(context)
    parsed_contexts.set(name, context)
  }
  Parser::{
    language,
    contexts: parsed_contexts,
    entries,
    extras: Set::from_array(extras),
  }
}

///|
fn generate_query(
  self : Parser,
  node : @tree_sitter.Node,
  queries : Array[Query],
  offset : Int,
  buffer : StringBuilder
) -> Unit!ParseError {
  let capture_queries = []
  let children_queries = []
  for query in queries {
    let query_range = query.range()
    if query_range.start + offset <= node.start_byte() &&
      query_range.end + offset >= node.end_byte() {
      capture_queries.push(query)
      if query is Group(_, _, queries) {
        children_queries.append(queries)
      }
    } else {
      children_queries.push(query)
    }
  }
  if capture_queries.length() == 0 {
    buffer.write_char('(')
  } else {
    for _ in 0..<capture_queries.length() {
      buffer.write_char('(')
    }
  }
  let mut type_ = None
  for query in capture_queries {
    if query is Match(_, _, query_type) {
      if type_ is Some(type_) {
        raise ConflictingMatch(query.range(), type_, query_type)
      } else {
        type_ = Some(query_type)
      }
    }
  }
  if type_ is Some(type_) {
    buffer.write_string(type_)
  } else {
    let type_ = if node.is_named() {
      node.type_().to_string()
    } else {
      node.type_().to_json().stringify()
    }
    buffer.write_string(type_)
    for child in node.children() {
      if self.extras.contains(child.type_().to_string()) {
        continue
      }
      buffer.write_char(' ')
      let queries = []
      for query in children_queries {
        let query_range = query.range()
        if query_range.start + offset <= child.end_byte() &&
          query_range.end + offset >= child.start_byte() {
          queries.push(query)
        }
      }
      generate_query!(self, child, queries, offset, buffer)
    }
  }
  if capture_queries.length() == 0 {
    buffer.write_char(')')
  } else {
    for query in capture_queries {
      buffer.write_string(") @\{query.name()}")
    }
  }
}

///|
priv struct Buffer {
  buffer : StringBuilder
  mut length : Int
}

///|
fn Buffer::new() -> Buffer {
  Buffer::{ buffer: StringBuilder::new(), length: 0 }
}

///|
fn Buffer::write_char(self : Buffer, char : Char) -> Unit {
  self.buffer.write_char(char)
  self.length += 1
}

///|
fn Buffer::write_string(self : Buffer, str : String) -> Unit {
  self.buffer.write_string(str)
  self.length += str.length()
}

///|
fn Buffer::to_string(self : Buffer) -> String {
  self.buffer.to_string()
}

///|
fn Buffer::length(self : Buffer) -> Int {
  self.length
}

///|
pub fn parse(self : Parser, source : @string.View) -> String!ParseError {
  let mut numeric_ident = 0
  let state = ParseState::Empty(children=[])
  let query = Buffer::new()
  loop state, 0, source {
    Empty(children~), offset, ['$', .. source] =>
      continue Ident(state=Empty(children~), buffer=StringBuilder::new()),
        offset + 1,
        source
    Empty(children~), offset, [char, .. source] => {
      query.write_char(char)
      continue Empty(children~), offset + 1, source
    }
    Empty(children~), _, [] => {
      let parser = @tree_sitter.parser(self.language)
      let quasi = query.to_string()
      let errors = []
      let query = StringBuilder::new()
      for name, context in self.contexts {
        let tree = try {
          parser.parse_string!("\{context.prefix}\{quasi}\{context.suffix}")
        } catch {
          e => {
            errors.push(e)
            continue
          }
        }
        if tree.root_node().has_error() {
          continue
        }
        let node = tree.root_node()
        query.write_string(";; \{name}\n")
        generate_query!(self, node, children, context.prefix.length(), query)
      }
      if errors.length() > 0 {
        raise ParseError(errors)
      }
      query.to_string()
    }
    Ident(state~, buffer~), offset, [':', char, .. source] => {
      let ident = buffer.to_string()
      let ident = if ident.is_empty() {
        let ident = numeric_ident.to_string()
        numeric_ident += 1
        ident
      } else {
        ident
      }
      buffer.reset()
      match char {
        '{' =>
          continue Group(state~, children=[], start=query.length(), ident~),
            offset + 2,
            source
        'a'..<'z' | 'A'..<'Z' as char => {
          let start = query.length()
          buffer.write_char(char)
          continue Match(state~, ident~, start~, buffer~), offset + 1, source
        }
        char =>
          raise UnrecognizedCharacter(Range::new(offset, offset + 1), char)
      }
    }
    Ident(state~, buffer~),
    offset,
    ['a'..<'z' | 'A'..<'Z' as char, .. source] => {
      buffer.write_char(char)
      continue Ident(state~, buffer~), offset + 1, source
    }
    Ident(..), offset, [char, ..] =>
      raise UnrecognizedCharacter(Range::new(offset, offset + 1), char)
    Ident(..), offset, [] => raise MissingColon(Range::new(offset, offset + 1))
    Match(state~, ident~, start~, buffer~),
    offset,
    ['a'..<'z' | 'A'..<'Z' as char, .. source] => {
      buffer.write_char(char)
      continue Match(state~, ident~, start~, buffer~), offset + 1, source
    }
    Match(state~, ident~, start~, buffer~), offset, [.. source] => {
      let alias_ = buffer.to_string()
      buffer.reset()
      guard self.entries[alias_] is Some(entry) else {
        raise UnrecognizedEntry(
          Range::new(offset - alias_.length(), offset),
          alias_,
        )
      }
      query.write_string(entry.placeholder)
      state
      .children()
      .push(Match(ident, Range::{ start, end: query.length() }, entry.query))
      continue state.to_parse_state(), offset, source
    }
    Group(state~, children~, ident~, start~), offset, ['$', '}', .. source] => {
      state
      .children()
      .push(Group(ident, Range::{ start, end: query.length() }, children))
      continue state.to_parse_state(), offset + 2, source
    }
    Group(state~, children~, ident~, start~), offset, ['$', .. source] =>
      continue Ident(
          state=Group(state~, children~, ident~, start~),
          buffer=StringBuilder::new(),
        ),
        offset + 1,
        source
    Group(state~, children~, ident~, start~), offset, [char, .. source] => {
      query.write_char(char)
      continue Group(state~, children~, ident~, start~), offset + 1, source
    }
    Group(start~, ..), offset, [] =>
      raise UnterminatedGroup(Range::new(start, offset))
  }
}

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
  QueryError(@tree_sitter.QueryError)
  UnrecognizedCharacter(Range, Char)
  UnterminatedGroup(Range)
  MissingColon(Range)
  UnrecognizedEntry(Range, String)
  UnrecognizedSymbol(@string.View)
} derive(Show)

///|
priv enum Query {
  Group(String, Range, quantifier~ : Quantifier, Array[Query])
  Match(
    String,
    Range,
    quantifier~ : Quantifier,
    matches~ : @string.View,
    replace~ : @string.View?
  )
} derive(Show)

///|
fn Query::range(self : Query) -> Range {
  match self {
    Group(_, range, _, ..) => range
    Match(_, range, ..) => range
  }
}

///|
fn Query::name(self : Query) -> String {
  match self {
    Group(name, _, _, ..) => name
    Match(name, _, ..) => name
  }
}

///|
fn Query::matches(self : Query) -> @string.View {
  match self {
    Group(_, _, _, ..) => []
    Match(_, _, matches~, ..) => matches
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
priv enum Quantifier {
  ZeroOrOne
  ZeroOrMore
  One
  OneOrMore
} derive(Show)

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
    quantifier~ : Quantifier,
    buffer~ : StringBuilder
  )
}

///|
struct Context {
  prefix : @string.View
  suffix : @string.View
  select : @string.View
  strip : Bool
}

///|
pub fn Context::new!(
  context : @string.View,
  strip~ : Bool = false,
  selector~ : @string.View
) -> Context!ContextError {
  let prefix = StringBuilder::new()
  loop context {
    ['$', .. context] =>
      return Context::{
        prefix: prefix.to_string(),
        suffix: context,
        strip,
        select: selector,
      }
    [.. "\\$", .. context] => {
      prefix.write_char('$')
      continue context
    }
    [char, .. context] => {
      prefix.write_char(char)
      continue context
    }
    [] => raise MissingInterpolator
  }
}

///|
struct Entry {
  matches : @string.View
  replace : @string.View?
  placeholder : @string.View
}

///|
pub fn Entry::new(
  matches~ : @string.View,
  replace? : @string.View,
  placeholder~ : @string.View
) -> Entry {
  Entry::{ matches, replace, placeholder }
}

///|
struct Parser {
  language : @tree_sitter.Language
  contexts : Map[String, Context]
  entries : Map[String, Entry]
  extras : Array[String]
}

///|
type! ContextError {
  MissingInterpolator
}

///|
pub fn Parser::new(
  language : @tree_sitter.Language,
  contexts~ : Map[String, Context],
  entries~ : Map[String, Entry],
  extras~ : Array[String] = []
) -> Parser {
  let parsed_contexts = Map::new(capacity=contexts.size())
  for name, context in contexts {
    parsed_contexts.set(name, context)
  }
  Parser::{ language, contexts: parsed_contexts, entries, extras }
}

///|
priv struct Replacement {
  name : @string.View
  query : @string.View
  quantifier : Quantifier
} derive(Show)

///|
fn generate_replacement(
  node~ : @tree_sitter.Node,
  replace~ : Replacement,
  buffer~ : StringBuilder,
  extras~ : Array[String]
) -> Unit {
  buffer.write_string("((")
  match replace.quantifier {
    One => ()
    ZeroOrMore | OneOrMore | ZeroOrOne => buffer.write_char('(')
  }
  buffer.write_string(replace.query.to_string())
  if replace.name != "_" {
    buffer.write_string(") @")
    buffer.write_string(replace.name.to_string())
  } else {
    buffer.write_char(')')
  }
  let node_extras = []
  for symbol in node.next_symbols() {
    guard node.language().symbol_name(symbol) is Some(symbol) else { continue }
    let symbol = symbol.to_string()
    if extras.contains(symbol) {
      node_extras.push(symbol)
    }
  }
  match node_extras {
    [] => ()
    [extra] => {
      buffer.write_char('(')
      buffer.write_string(extra)
      buffer.write_string(")")
    }
    extras => {
      buffer.write_char('[')
      for extra in extras {
        buffer.write_char('(')
        buffer.write_string(extra)
        buffer.write_char(')')
      }
      buffer.write_string("]")
    }
  }
  match replace.quantifier {
    ZeroOrMore => buffer.write_string(")*")
    OneOrMore => buffer.write_string(")+")
    ZeroOrOne => buffer.write_string(")?")
    One => ()
  }
  buffer.write_char(')')
}

///|
fn generate_replacements(
  node~ : @tree_sitter.Node,
  replace~ : Array[Replacement],
  buffer~ : StringBuilder,
  extras~ : Array[String]
) -> Unit {
  match replace {
    [] => abort("Empty replacement")
    [replace] => generate_replacement(node~, replace~, buffer~, extras~)
    replaces => {
      buffer.write_char('[')
      for replace in replaces {
        generate_replacement(node~, replace~, buffer~, extras~)
      }
      buffer.write_char(']')
    }
  }
}

///|
fn generate_query(
  self : Parser,
  node : @tree_sitter.Node,
  queries~ : Array[Query],
  replace~ : Map[@tree_sitter.Node, Array[Replacement]],
  offset~ : Int,
  buffer~ : StringBuilder
) -> Unit!ParseError {
  struct Group {
    name : String
    range : Range
    quantifier : Quantifier
    mut opened : Bool
    mut closed : Bool
  } derive(Show)
  if replace[node] is Some(replace) {
    generate_replacements(node~, replace~, buffer~, extras=self.extras)
    return
  }
  // Queries that does not capture the current node, therefore they are
  // passed to the children.
  let children_queries = []
  for query in queries {
    match query {
      Match(name, range, quantifier~, matches~, replace=replacement) =>
        if range.start + offset <= node.start_byte() &&
          range.end + offset >= node.end_byte() {
          let cursor = try {
            node.query!("\{matches} @\{name}")
          } catch {
            e => raise QueryError(e)
          }
          for capture in cursor.captures() {
            if capture.name() != name {
              continue
            }
            let replacement = replacement.or(capture.node().type_())
            match replace[capture.node()] {
              Some(replace) =>
                replace.push({ name, query: replacement, quantifier })
              None =>
                replace[capture.node()] = [
                  { name, query: replacement, quantifier },
                ]
            }
          }
        } else {
          children_queries.push(query)
        }
      Group(_, range, queries, ..) =>
        if range.start + offset <= node.start_byte() &&
          range.end + offset >= node.end_byte() {
          children_queries.append(queries)
        } else {
          children_queries.push(query)
        }
    }
  }
  let children_groups : Array[Group] = []
  for query in children_queries {
    match query {
      Group(name, range, _, quantifier~) =>
        children_groups.push(Group::{
          name,
          range,
          quantifier,
          opened: false,
          closed: false,
        })
      Match(_, _, ..) => ()
    }
  }
  if replace[node] is Some(replace) {
    generate_replacements(node~, replace~, buffer~, extras=self.extras)
    return
  }
  buffer.write_char('(')
  let type_ = if node.is_named() {
    node.type_().to_string()
  } else {
    node.type_().to_json().stringify()
  }
  buffer.write_string(type_)
  let children = node.children().collect()
  for i, child in children {
    for group in children_groups {
      if not(group.opened) && child.start_byte() >= group.range.start + offset {
        buffer.write_char('(')
        group.opened = true
      }
    }
    if self.extras.contains(child.type_().to_string()) {
      match self.extras {
        [] => ()
        [extra] => {
          buffer.write_string("(")
          buffer.write_string(extra)
          buffer.write_string(")*")
        }
        extras => {
          buffer.write_string("[")
          for extra in extras {
            buffer.write_char('(')
            buffer.write_string(extra)
            buffer.write_char(')')
          }
          buffer.write_string("]*")
        }
      }
    } else {
      let queries = []
      for query in children_queries {
        let query_range = query.range()
        if query_range.start + offset <= child.end_byte() &&
          query_range.end + offset >= child.start_byte() {
          queries.push(query)
        }
      }
      generate_query!(self, child, queries~, replace~, offset~, buffer~)
    }
    if i < children.length() - 1 {
      let next_child = children[i + 1]
      for group in children_groups {
        if not(group.closed) &&
          next_child.start_byte() >= group.range.end + offset {
          match group.quantifier {
            ZeroOrMore => buffer.write_string(")*")
            OneOrMore => buffer.write_string(")+")
            ZeroOrOne => buffer.write_string(")?")
            One => buffer.write_string(")")
          }
          if group.name != "_" {
            buffer.write_string(" @\{group.name}")
          }
          group.closed = true
          continue
        }
      } else {
        buffer.write_string(" . ")
      }
    }
  }
  buffer.write_char(')')
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
fn strip_colocated_nodes(node : @tree_sitter.Node) -> @tree_sitter.Node {
  for child in node.children() {
    if child.start_byte() == node.start_byte() &&
      child.end_byte() == node.end_byte() {
      return strip_colocated_nodes(child)
    }
  }
  return node
}

///|
fn lowest_common_ancestor(
  root : @tree_sitter.Node,
  nodes : Array[@tree_sitter.Node]
) -> @tree_sitter.Node {
  let mut ancestor : @tree_sitter.Node? = None
  for node in nodes {
    let node_ancestor = root.child_with_descendant(node)
    match (ancestor, node_ancestor) {
      (Some(ancestor), Some(node_ancestor)) =>
        if ancestor != node_ancestor {
          return root
        }
      (None, Some(_)) => ancestor = node_ancestor
      (_, None) => continue
    }
  }
  match ancestor {
    None => root
    Some(ancestor) => lowest_common_ancestor(ancestor, nodes)
  }
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
    Empty(children=queries), _, [] => {
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
        let cursor = try {
          tree.query!(context.select)
        } catch {
          e => raise QueryError(e)
        }
        let nodes = []
        for capture in cursor.captures() {
          if capture.name() != name {
            continue
          }
          if self.extras.contains(capture.node().type_().to_string()) {
            continue
          }
          nodes.push(capture.node())
        }
        query.write_string(";; \{name}\n")
        if nodes is [] {
          generate_query!(
            self,
            strip_colocated_nodes(tree.root_node()),
            queries~,
            replace=Map::new(),
            offset=context.prefix.length(),
            buffer=query,
          )
        } else if nodes is [node] {
          let node = if context.strip {
            strip_colocated_nodes(node)
          } else {
            node
          }
          generate_query!(
            self,
            node,
            queries~,
            replace=Map::new(),
            offset=context.prefix.length(),
            buffer=query,
          )
        } else {
          let ancestor = lowest_common_ancestor(tree.root_node(), nodes)
          query.write_char('(')
          let mut start_byte = ancestor.end_byte()
          let mut end_byte = ancestor.start_byte()
          for node in nodes {
            guard ancestor.child_with_descendant(node) is Some(parent) else {
              continue
            }
            start_byte = @math.minimum(start_byte, parent.start_byte())
            end_byte = @math.maximum(end_byte, parent.end_byte())
          }
          let ancestor_children = ancestor
            .children()
            .filter(fn(node) {
              node.start_byte() >= start_byte && node.end_byte() <= end_byte
            })
            .collect()
          for i, node in ancestor_children {
            if self.extras.contains(node.type_().to_string()) {
              match self.extras {
                [] => ()
                [extra] => {
                  query.write_string("(")
                  query.write_string(extra)
                  query.write_string(")*")
                }
                extras => {
                  query.write_string("[")
                  for extra in extras {
                    query.write_char('(')
                    query.write_string(extra)
                    query.write_char(')')
                  }
                  query.write_string("]*")
                }
              }
            } else {
              generate_query!(
                self,
                node,
                queries~,
                replace=Map::new(),
                offset=context.prefix.length(),
                buffer=query,
              )
            }
            if i < ancestor_children.length() - 1 {
              query.write_string(" . ")
            }
          }
          query.write_char(')')
        }
        query.write_char('\n')
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
        'a'..<'z' | 'A'..<'Z' | '_' as char => {
          let start = query.length()
          buffer.write_char(char)
          continue Match(state~, ident~, start~, buffer~, quantifier=One),
            offset + 1,
            source
        }
        char =>
          raise UnrecognizedCharacter(Range::new(offset, offset + 1), char)
      }
    }
    Ident(state~, buffer~),
    offset,
    ['a'..<'z' | 'A'..<'Z' | '_' as char, .. source] => {
      buffer.write_char(char)
      continue Ident(state~, buffer~), offset + 1, source
    }
    Ident(..), offset, [char, ..] =>
      raise UnrecognizedCharacter(Range::new(offset, offset + 1), char)
    Ident(..), offset, [] => raise MissingColon(Range::new(offset, offset + 1))
    Match(state~, ident~, start~, buffer~, quantifier~),
    offset,
    ['a'..<'z' | 'A'..<'Z' | '_' as char, .. source] => {
      buffer.write_char(char)
      continue Match(state~, ident~, start~, buffer~, quantifier~),
        offset + 1,
        source
    }
    Match(state~, ident~, start~, buffer~, quantifier=_),
    offset,
    ['*', .. source] =>
      continue Match(state~, ident~, start~, buffer~, quantifier=ZeroOrMore),
        offset + 1,
        source
    Match(state~, ident~, start~, buffer~, quantifier=_),
    offset,
    ['+', .. source] =>
      continue Match(state~, ident~, start~, buffer~, quantifier=OneOrMore),
        offset + 1,
        source
    Match(state~, ident~, start~, buffer~, quantifier=_),
    offset,
    ['?', .. source] =>
      continue Match(state~, ident~, start~, buffer~, quantifier=ZeroOrOne),
        offset + 1,
        source
    Match(state~, ident~, start~, buffer~, quantifier~), offset, [.. source] => {
      let alias_ = buffer.to_string()
      buffer.reset()
      guard self.entries[alias_] is Some(entry) else {
        raise UnrecognizedEntry(
          Range::new(offset - alias_.length(), offset),
          alias_,
        )
      }
      query.write_string(entry.placeholder.to_string())
      state
      .children()
      .push(
        Match(
          ident,
          Range::{ start, end: query.length() },
          matches=entry.matches,
          replace=entry.replace,
          quantifier~,
        ),
      )
      continue state.to_parse_state(), offset, source
    }
    Group(state~, children~, ident~, start~), offset, ['$', '}', .. source] => {
      let (quantifier, source) = match source {
        ['*', .. source] => (ZeroOrMore, source)
        ['+', .. source] => (OneOrMore, source)
        ['?', .. source] => (ZeroOrOne, source)
        [.. source] => (One, source)
      }
      state
      .children()
      .push(
        Group(
          ident,
          Range::{ start, end: query.length() },
          quantifier~,
          children,
        ),
      )
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

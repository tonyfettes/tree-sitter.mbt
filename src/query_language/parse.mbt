///|
priv struct Range {
  start : Int
  end : Int
} derive(Show, ToJson)

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
} derive(Show)

///|
priv enum Query {
  Group(range~ : Range, quantifier~ : Quantifier, Array[Query])
  Match(
    name~ : String,
    range~ : Range,
    quantifier~ : Quantifier,
    matches~ : @string.View,
    replace~ : @string.View?
  )
} derive(Show, ToJson)

///|
fn Query::group(
  range~ : Range,
  quantifier~ : Quantifier,
  children~ : Array[Query]
) -> Query {
  Group(range~, quantifier~, children)
}

///|
fn Query::range(self : Query) -> Range {
  match self {
    Group(range~, _, ..) => range
    Match(range~, ..) => range
  }
}

///|
priv enum GroupState {
  Empty(children~ : Array[Query])
  Group(state~ : GroupState, children~ : Array[Query], start~ : Int)
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
    Group(state~, children~, start~) =>
      ParseState::Group(state~, children~, start~)
  }
}

///|
priv enum Quantifier {
  ZeroOrOne
  ZeroOrMore
  One
  OneOrMore
} derive(Show, ToJson)

///|
priv enum ParseState {
  Empty(children~ : Array[Query])
  Group(state~ : GroupState, children~ : Array[Query], start~ : Int)
  Entry(state~ : GroupState, buffer~ : StringBuilder)
  Match(
    state~ : GroupState,
    entry~ : Entry,
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
  parser : @tree_sitter.Parser
  contexts : Map[String, Context]
  entries : Map[String, Entry]
  extras : Array[String]
}

///|
pub fn Parser::language(self : Parser) -> @tree_sitter.Language {
  self.language
}

///|
pub fn Parser::parser(self : Parser) -> @tree_sitter.Parser {
  self.parser
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
  let parser = @tree_sitter.Parser::new()
  parser.set_language(language)
  Parser::{ language, parser, contexts: parsed_contexts, entries, extras }
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
  for symbol in node.next_symbol_names() {
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
fn generate_query_for_children(
  self : Parser,
  children : Array[@tree_sitter.Node],
  queries~ : Array[Query],
  replace~ : Map[@tree_sitter.Node, Array[Replacement]],
  offset~ : Int,
  buffer~ : StringBuilder
) -> Unit!ParseError {
  struct Group {
    range : Range
    quantifier : Quantifier
    mut closed : Bool
  } derive(Show, ToJson)

  // We use a queue to maintain the active set of queries.
  let mut queries_queue : @deque.T[Query] = @deque.from_array(queries)
  let opened_groups : Array[Group] = []
  for i, child in children {
    // BFS traversal of the queries. Basically we are looking for all the
    // queries that match the current child node.
    // 1. If the query is a match.
    //    a. If its range covers the child node, we add it to the child queries,
    //       and remove it from the queue.
    //    b. If its range does not cover the child node, we schedule it for
    //       processing later by adding it to the next queue.
    // 2. If the query is a group.
    //    a. If its range covers the child node, we unpack the queries inside
    //       the group and add them to the current queue so that they get
    //       processed immediately.
    //    b. If its range intersects the child node, we add it to the child
    //       queries, and remove it from the queue.
    //    c. If its range has no intersection with the child node, we add it to
    //       the next queue so that it gets processed later.
    let child_queries = []
    let queries_queue_next = @deque.new()
    while queries_queue.pop_front() is Some(query) {
      fn intersects_with(node : @tree_sitter.Node, range : Range) -> Bool {
        // The range of tree-sitter node is exclusive on the right side.
        // This means range [a, b) has no intersection with [b, c). Therefore
        // we should not use '<=' and '>=' here.
        node.start_byte() < range.end + offset &&
        node.end_byte() > range.start + offset
      }

      fn covered_by(node : @tree_sitter.Node, range : Range) -> Bool {
        node.start_byte() >= range.start + offset &&
        node.end_byte() <= range.end + offset
      }

      fn covers(node : @tree_sitter.Node, range : Range) -> Bool {
        node.start_byte() <= range.start + offset &&
        node.end_byte() >= range.end + offset
      }

      match query {
        Match(range~, ..) =>
          if covers(child, range) {
            child_queries.push(query)
          } else {
            queries_queue_next.push_back(query)
          }
        Group(range~, group_queries, quantifier~) =>
          if covered_by(child, range) {
            buffer.write_char('(')
            opened_groups.push(Group::{ range, quantifier, closed: false })
            for group_query in group_queries {
              queries_queue.push_back(group_query)
            }
          } else if intersects_with(child, range) {
            child_queries.push(query)
          } else {
            queries_queue_next.push_back(query)
          }
      }
    }
    queries_queue = queries_queue_next
    if self.extras.contains(child.type_().to_string()) {
      // Handle extras. Ideally this should be done by using the next_symbols()
      // functionality provided by tree-sitter. However, it seems that it will
      // missing some of the symbols, thus we have to do it manually.
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
      generate_query!(
        self,
        child,
        queries=child_queries,
        replace~,
        offset~,
        buffer~,
      )
    }
    let last = i == children.length() - 1
    for group in opened_groups {
      if not(group.closed) {
        let should_close = if not(last) {
          let next_child = children[i + 1]
          if next_child.start_byte() >= group.range.end + offset {
            true
          } else {
            false
          }
        } else {
          // Always close the group that spans beyond the last child.
          true
        }
        if should_close {
          match group.quantifier {
            ZeroOrMore => buffer.write_string(")*")
            OneOrMore => buffer.write_string(")+")
            ZeroOrOne => buffer.write_string(")?")
            One => buffer.write_string(")")
          }
          group.closed = true
        }
      }
    }
    // We emit anchor between each child node to make sure there is no extra
    // nodes between them when pattern matching.
    if not(last) {
      buffer.write_string(" . ")
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
  if replace.get(node) is Some(replace) {
    generate_replacements(node~, replace~, buffer~, extras=self.extras)
    return
  }
  // Queries that does not capture the current node, therefore they are
  // passed to the children.
  let children_queries = []
  for query in queries {
    match query {
      Match(name~, range~, quantifier~, matches~, replace=replacement) =>
        if range.start + offset <= node.start_byte() &&
          range.end + offset >= node.end_byte() {
          let cursor = try {
            @tree_sitter.Query::new!(self.language, "\{matches} @\{name}")
          } catch {
            e => raise QueryError(e)
          }
          for capture in cursor.captures(node) {
            if capture.name() != name {
              continue
            }
            let replacement = replacement.or(capture.node().type_())
            match replace.get(capture.node()) {
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
      Group(range~, quantifier=_, queries) =>
        if range.start + offset <= node.start_byte() &&
          range.end + offset >= node.end_byte() {
          children_queries.append(queries)
        } else {
          children_queries.push(query)
        }
    }
  }
  if replace.get(node) is Some(replace) {
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
  self.generate_query_for_children!(
    children,
    queries=children_queries,
    replace~,
    offset~,
    buffer~,
  )
  buffer.write_char(')')
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
  let state = ParseState::Empty(children=[])
  let query = Buffer::new()
  loop state, 0, source {
    Empty(children~), offset, ['$', '{', .. source] =>
      continue Group(state=Empty(children~), children=[], start=query.length()),
        offset + 2,
        source
    Empty(children~), offset, ['$', .. source] =>
      continue Entry(state=Empty(children~), buffer=StringBuilder::new()),
        offset + 1,
        source
    Empty(children~), offset, [char, .. source] => {
      query.write_char(char)
      continue Empty(children~), offset + 1, source
    }
    Empty(children=queries), _, [] => {
      let parser = @tree_sitter.Parser::new()
      parser.set_language(self.language)
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
          @tree_sitter.Query::new!(self.language, context.select)
        } catch {
          e => raise QueryError(e)
        }
        let nodes = []
        for capture in cursor.captures(tree.root_node()) {
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
          self.generate_query_for_children!(
            [strip_colocated_nodes(tree.root_node())],
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
          self.generate_query_for_children!(
            [node],
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
          self.generate_query_for_children!(
            ancestor_children,
            queries~,
            replace=Map::new(),
            offset=context.prefix.length(),
            buffer=query,
          )
          query.write_char(')')
        }
        query.write_char('\n')
      }
      if errors.length() > 0 {
        raise ParseError(errors)
      }
      query.to_string()
    }
    Entry(state~, buffer~), offset, [':', char, .. source] => {
      let entry = buffer.to_string()
      buffer.reset()
      guard self.entries.get(entry) is Some(entry) else {
        raise UnrecognizedEntry(
          Range::new(offset - entry.length(), offset),
          entry,
        )
      }
      match char {
        'a'..<'z' | 'A'..<'Z' | '_' as char => {
          let start = query.length()
          query.write_string(entry.placeholder.to_string())
          buffer.write_char(char)
          continue Match(state~, entry~, start~, buffer~, quantifier=One),
            offset + 1,
            source
        }
        char =>
          raise UnrecognizedCharacter(Range::new(offset, offset + 1), char)
      }
    }
    Entry(state~, buffer~),
    offset,
    ['a'..<'z' | 'A'..<'Z' | '_' as char, .. source] => {
      buffer.write_char(char)
      continue Entry(state~, buffer~), offset + 1, source
    }
    Entry(..), offset, [char, ..] =>
      raise UnrecognizedCharacter(Range::new(offset, offset + 1), char)
    Entry(..), offset, [] => raise MissingColon(Range::new(offset, offset + 1))
    Match(state~, entry~, start~, buffer~, quantifier~),
    offset,
    ['a'..<'z' | 'A'..<'Z' | '_' as char, .. source] => {
      buffer.write_char(char)
      continue Match(state~, entry~, start~, buffer~, quantifier~),
        offset + 1,
        source
    }
    Match(state~, entry~, start~, buffer~, quantifier=One),
    offset,
    ['*', .. source] =>
      continue Match(state~, entry~, start~, buffer~, quantifier=ZeroOrMore),
        offset + 1,
        source
    Match(state~, entry~, start~, buffer~, quantifier=One),
    offset,
    ['+', .. source] =>
      continue Match(state~, entry~, start~, buffer~, quantifier=OneOrMore),
        offset + 1,
        source
    Match(state~, entry~, start~, buffer~, quantifier=One),
    offset,
    ['?', .. source] =>
      continue Match(state~, entry~, start~, buffer~, quantifier=ZeroOrOne),
        offset + 1,
        source
    Match(state~, entry~, start~, buffer~, quantifier~), offset, [.. source] => {
      let ident = buffer.to_string()
      buffer.reset()
      state
      .children()
      .push(
        Match(
          name=ident,
          range=Range::{ start, end: query.length() },
          matches=entry.matches,
          replace=entry.replace,
          quantifier~,
        ),
      )
      continue state.to_parse_state(), offset, source
    }
    Group(state~, children~, start~), offset, [.. "\\{", .. source] => {
      query.write_char('{')
      continue Group(state~, children~, start~), offset + 2, source
    }
    Group(state~, children~, start~), offset, [.. "\\}", .. source] => {
      query.write_char('}')
      continue Group(state~, children~, start~), offset + 2, source
    }
    Group(state~, children~, start~), offset, ['}', .. source] => {
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
          range=Range::{ start, end: query.length() },
          quantifier~,
          children,
        ),
      )
      continue state.to_parse_state(), offset + 2, source
    }
    Group(state~, children~, start~), offset, ['$', '{', .. source] =>
      continue Group(
          state=Group(state~, children~, start~),
          children=[],
          start=query.length(),
        ),
        offset + 2,
        source
    Group(state~, children~, start~), offset, ['$', .. source] =>
      continue Entry(
          state=Group(state~, children~, start~),
          buffer=StringBuilder::new(),
        ),
        offset + 1,
        source
    Group(state~, children~, start~), offset, [char, .. source] => {
      query.write_char(char)
      continue Group(state~, children~, start~), offset + 1, source
    }
    Group(start~, ..), offset, [] =>
      raise UnterminatedGroup(Range::new(start, offset))
  }
}

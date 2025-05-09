///|
type QueryCapture

///|
pub extern "js" fn QueryCapture::pattern_index(self : QueryCapture) -> Int =
  #|(self) => {
  #|  return self.patternIndex;
  #|}

///|
pub extern "js" fn QueryCapture::name(self : QueryCapture) -> String =
  #|(self) => {
  #|  return self.name;
  #|}

///|
pub extern "js" fn QueryCapture::node(self : QueryCapture) -> Node =
  #|(self) => {
  #|  return self.node;
  #|}

///|
type QueryMatch

///|
pub extern "js" fn QueryMatch::captures(
  self : QueryMatch
) -> Array[QueryCapture] =
  #|(self) => {
  #|  return self.captures;
  #|}

///|
pub extern "js" fn QueryMatch::pattern_index(self : QueryMatch) -> Int =
  #|(self) => {
  #|  return self.patternIndex;
  #|}

///|
struct QueryCursor {
  mut query : Query?
  mut node : Node?
}

///|
pub fn QueryCursor::new() -> QueryCursor {
  QueryCursor::{ query: None, node: None }
}

///|
pub fn QueryCursor::exec(
  self : QueryCursor,
  query : Query,
  node : Node
) -> Unit {
  self.query = Some(query)
  self.node = Some(node)
}

///|
pub fn QueryCursor::matches(self : QueryCursor) -> Iter[QueryMatch] {
  guard self.query is Some(query) && self.node is Some(node) else {
    Iter::empty()
  }
  query.matches(node).iter()
}

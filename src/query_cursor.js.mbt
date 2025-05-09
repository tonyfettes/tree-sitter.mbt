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

pub extern "js" fn QueryMatch::pattern_index(self : QueryMatch) -> Int =
  #|(self) => {
  #|  return self.patternIndex;
  #|}

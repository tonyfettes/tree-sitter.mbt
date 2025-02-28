///|
struct SupertypeNode {
  type_ : String
  named : Bool
}

///|
enum Prec {
  NonAssoc
  Left
  Right
  Dynamic
}

///|
impl Show for Prec with to_string(self) {
  match self {
    Prec::NonAssoc => "PREC"
    Prec::Left => "PREC_LEFT"
    Prec::Right => "PREC_RIGHT"
    Prec::Dynamic => "PREC_DYNAMIC"
  }
}

///|
impl Show for Prec with output(self, logger) {
  logger.write_string(self.to_string())
}

///|
impl ToJson for Prec with to_json(self) {
  String(self.to_string())
}

///|
enum Pattern {
  RegExp(@regexp.RegExp)
  String(String)
}

///|
impl Show for Pattern with to_string(self) {
  match self {
    Pattern::RegExp(re) => re.pattern()
    Pattern::String(s) => s
  }
}

///|
impl Show for Pattern with output(self, logger) {
  logger.write_string(self.to_string())
}

///|
impl ToJson for Pattern with to_json(self) {
  String(self.to_string())
}

///|
enum Rule {
  Blank
  Symbol(String)
  String(String)
  Repeat(Rule)
  Repeat1(Rule)
  Choice(members~ : Array[Rule])
  Seq(members~ : Array[Rule])
  Field(String, Rule)
  Token(immediate~ : Bool, Rule)
  Prec(Prec, Int, Rule)
  Pattern(mut value~ : Pattern)
} derive(Show)

///|
fn Rule::visit_rule[E : Error](
  self : Rule,
  visitor : (Rule) -> Unit!E
) -> Unit!E {
  visitor!(self)
  match self {
    Prec(_, _, rule) => rule.visit_rule!(visitor)
    Token(immediate=_, rule) => rule.visit_rule!(visitor)
    Field(_, rule) => rule.visit_rule!(visitor)
    Seq(members~) | Choice(members~) =>
      for rule in members {
        rule.visit_rule!(visitor)
      }
    Repeat1(rule) | Repeat(rule) => rule.visit_rule!(visitor)
    String(_) => ()
    Symbol(_) => ()
    Blank => ()
    Pattern(_) => ()
  }
}

///|
impl @json.FromJson for Rule with from_json(
  json : Json,
  json_path : @json.JsonPath
) -> Rule!@json.JsonDecodeError {
  match json {
    { "type": "BLANK", .. } => Rule::Blank
    { "type": "SYMBOL", "name": String(name), .. } => Rule::Symbol(name)
    { "type": "STRING", "value": String(value), .. } => Rule::String(value)
    { "type": "CHOICE", "members": Array(members_json), .. } => {
      let members_json_path = json_path.add_key("members")
      let members = []
      for i, member_json in members_json {
        members.push(
          Rule::from_json!(member_json, members_json_path.add_index(i)),
        )
      }
      Rule::Choice(members~)
    }
    { "type": "SEQ", "members": Array(members_json), .. } => {
      let members_json_path = json_path.add_key("members")
      let members = []
      for i, member_json in members_json {
        members.push(
          Rule::from_json!(member_json, members_json_path.add_index(i)),
        )
      }
      Rule::Seq(members~)
    }
    { "type": "REPEAT", "content": rule, .. } =>
      Rule::Repeat(Rule::from_json!(rule, json_path.add_key("content")))
    { "type": "REPEAT1", "content": rule, .. } =>
      Rule::Repeat1(Rule::from_json!(rule, json_path.add_key("content")))
    { "type": "TOKEN", "content": rule, .. } =>
      Rule::Token(
        immediate=false,
        Rule::from_json!(rule, json_path.add_key("content")),
      )
    { "type": "IMMEDIATE_TOKEN", "content": rule, .. } =>
      Rule::Token(
        immediate=true,
        Rule::from_json!(rule, json_path.add_key("content")),
      )
    { "type": "FIELD", "name": String(name), "content": rule, .. } =>
      Rule::Field(name, Rule::from_json!(rule, json_path.add_key("content")))
    {
      "type": String([.. "PREC", .. suffix]),
      "value": Number(value),
      "content": rule,
      ..
    } => {
      let prec = match suffix {
        [.. ""] => Prec::NonAssoc
        [.. "_LEFT"] => Prec::Left
        [.. "_RIGHT"] => Prec::Right
        [.. "_DYNAMIC"] => Prec::Dynamic
        suffix => {
          let message = "Rule::from_json: invalid precedence type \"PREC\{suffix}\""
          raise @json.JsonDecodeError((json_path, message))
        }
      }
      Rule::Prec(
        prec,
        value.to_int(),
        Rule::from_json!(rule, json_path.add_key("content")),
      )
    }
    { "type": "PATTERN", "value": String(value), .. } =>
      Rule::Pattern(value=String(value))
    json => {
      let message = "Rule::from_json: expected object with \"type\" field, got \{json}"
      raise @json.JsonDecodeError((json_path, message))
    }
  }
}

///|
impl ToJson for Rule with to_json(self : Rule) -> Json {
  match self {
    Prec(prec, value, rule) =>
      {
        "type": prec.to_json(),
        "value": value.to_json(),
        "content": rule.to_json(),
      }
    Token(immediate~, rule) => {
      let token_type = if immediate { "IMMEDIATE_TOKEN" } else { "TOKEN" }
      { "type": String(token_type), "content": rule.to_json() }
    }
    Field(name, rule) =>
      { "type": "FIELD", "name": String(name), "content": rule.to_json() }
    Seq(members~) => {
      let members_json = []
      for member in members {
        members_json.push(member.to_json())
      }
      { "type": "SEQ", "members": Array(members_json) }
    }
    Choice(members~) => {
      let members_json = []
      for member in members {
        members_json.push(member.to_json())
      }
      { "type": "CHOICE", "members": Array(members_json) }
    }
    Repeat1(rule) => { "type": "REPEAT1", "content": rule.to_json() }
    Repeat(rule) => { "type": "REPEAT", "content": rule.to_json() }
    String(value) => { "type": "STRING", "value": String(value) }
    Symbol(name) => { "type": "SYMBOL", "name": String(name) }
    Blank => { "type": "BLANK" }
    Pattern(value~) => { "type": "PATTERN", "value": value.to_json() }
  }
}

///|
struct RuleName {
  name : String
  mut rule : Rule?
} derive(Show)

///|
impl @json.FromJson for RuleName with from_json(
  json : Json,
  json_path : @json.JsonPath
) -> RuleName!@json.JsonDecodeError {
  guard json is String(name) else {
    let message = "RuleName::from_json: expected string, got \{json}"
    raise @json.JsonDecodeError((json_path, message))
  }
  { name, rule: None }
}

///|
impl ToJson for RuleName with to_json(self : RuleName) -> Json {
  String(self.name)
}

///|
struct Grammar {
  name : String
  rules : Map[String, Rule]
  extras : Array[Rule]
  supertypes : Array[RuleName]
  reserved : Map[String, Rule]
  externals : Array[Rule]
  inline : Array[RuleName]
  conflicts : Array[Array[RuleName]]
  word : RuleName?
} derive(@json.FromJson, Show, ToJson)

///|
type! GrammarParseError {
  JsonDecodeError(@json.JsonDecodeError)
  RegExpParseError(Error)
  RuleNotFound(String)
}

///|
pub fn Grammar::from_json(json : Json) -> Grammar!GrammarParseError {
  let grammar : Grammar = try {
    @json.from_json!(json)
  } catch {
    error => raise JsonDecodeError(error)
  }
  for _, rule in grammar.rules {
    let visitor = fn(rule : Rule) -> Unit!GrammarParseError {
      guard rule is (Pattern(value~) as pattern) else { return }
      guard value is String(s) else { return }
      let compiled = try {
        @regexp.compile!(s)
      } catch {
        error => raise RegExpParseError(error)
      }
      pattern.value = RegExp(compiled)
    }
    rule.visit_rule!(visitor)
  }
  for supertype in grammar.supertypes {
    guard grammar.rules[supertype.name] is Some(rule) else {
      raise RuleNotFound(supertype.name)
    }
    supertype.rule = Some(rule)
  }
  for inline in grammar.inline {
    guard grammar.rules[inline.name] is Some(rule) else {
      raise RuleNotFound(inline.name)
    }
    inline.rule = Some(rule)
  }
  for conflict in grammar.conflicts {
    for rule_name in conflict {
      guard grammar.rules[rule_name.name] is Some(rule) else {
        raise RuleNotFound(rule_name.name)
      }
      rule_name.rule = Some(rule)
    }
  }
  if grammar.word is Some(word) {
    guard grammar.rules[word.name] is Some(rule) else {
      raise RuleNotFound(word.name)
    }
    word.rule = Some(rule)
  }
  grammar
}

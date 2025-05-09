///|
enum Prec {
  NonAssoc
  Left
  Right
  Dynamic
} derive(Eq, Hash)

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
  self.to_string().to_json()
}

///|
pub enum Rule {
  Alias(named~ : Bool, String, Rule)
  Blank
  Symbol(String)
  String(String)
  Repeat(Rule)
  Repeat1(Rule)
  Choice(Array[Rule])
  Seq(Array[Rule])
  Field(name~ : String, Rule)
  Token(immediate~ : Bool, Rule)
  Prec(prec~ : Prec, value~ : Int, Rule)
  Pattern(String)
} derive(Show)

///|
pub impl Eq for Rule with op_equal(self : Rule, other : Rule) -> Bool {
  match (self, other) {
    (Alias(named=named1, alias1, rule1), Alias(named=named2, alias2, rule2)) =>
      named1 == named2 && alias1 == alias2 && rule1 == rule2
    (Alias(_, ..), _) => false
    (Blank, Blank) => true
    (Blank, _) => false
    (Symbol(name1), Symbol(name2)) => name1 == name2
    (Symbol(_), _) => false
    (String(value1), String(value2)) => value1 == value2
    (String(_), _) => false
    (Repeat(rule1), Repeat(rule2)) => rule1 == rule2
    (Repeat(_), _) => false
    (Repeat1(rule1), Repeat1(rule2)) => rule1 == rule2
    (Repeat1(_), _) => false
    (Choice(rules1), Choice(rules2)) => rules1 == rules2
    (Choice(_, ..), _) => false
    (Seq(rules1), Seq(rules2)) => rules1 == rules2
    (Seq(_, ..), _) => false
    (Field(name=name1, rule1), Field(name=name2, rule2)) =>
      name1 == name2 && rule1 == rule2
    (Field(_, ..), _) => false
    (Token(immediate=imm1, rule1), Token(immediate=imm2, rule2)) =>
      imm1 == imm2 && rule1 == rule2
    (Token(_, ..), _) => false
    (
      Prec(prec=prec1, value=value1, rule1),
      Prec(prec=prec2, value=value2, rule2),
    ) => prec1 == prec2 && value1 == value2 && rule1 == rule2
    (Prec(_, ..), _) => false
    (Pattern(value1), Pattern(value2)) => value1 == value2
    (Pattern(_, ..), _) => false
  }
}

///|
pub impl Hash for Rule with hash_combine(self, hasher) {
  match self {
    Alias(named~, value, rule) => {
      hasher.combine_int(0)
      hasher.combine_bool(named)
      hasher.combine_string(value)
      hasher.combine(rule)
    }
    Blank => hasher.combine_int(1)
    Symbol(name) => {
      hasher.combine_int(2)
      hasher.combine_string(name)
    }
    String(value) => {
      hasher.combine_int(3)
      hasher.combine_string(value)
    }
    Repeat(rule) => {
      hasher.combine_int(4)
      hasher.combine(rule)
    }
    Repeat1(rule) => {
      hasher.combine_int(5)
      hasher.combine(rule)
    }
    Choice(rules) => {
      hasher.combine_int(6)
      for rule in rules {
        hasher.combine(rule)
      }
    }
    Seq(rules) => {
      hasher.combine_int(7)
      for rule in rules {
        hasher.combine(rule)
      }
    }
    Field(name~, rule) => {
      hasher.combine_int(8)
      hasher.combine_string(name)
      hasher.combine(rule)
    }
    Token(immediate~, rule) => {
      hasher.combine_int(9)
      hasher.combine_bool(immediate)
      hasher.combine(rule)
    }
    Prec(prec~, value~, rule) => {
      hasher.combine_int(10)
      hasher.combine(prec)
      hasher.combine_int(value)
      hasher.combine(rule)
    }
    Pattern(value) => {
      hasher.combine_int(11)
      hasher.combine(value)
    }
  }
}

///|
fn Rule::visit_rule[E : Error](
  self : Rule,
  visitor : (Rule) -> Unit!E
) -> Unit!E {
  visitor!(self)
  match self {
    Alias(_, rule, ..) => rule.visit_rule!(visitor)
    Prec(rule, ..) => rule.visit_rule!(visitor)
    Token(rule, ..) => rule.visit_rule!(visitor)
    Field(rule, ..) => rule.visit_rule!(visitor)
    Seq(rules) | Choice(rules) =>
      for rule in rules {
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
    {
      "type": "ALIAS",
      "named": True
      | False as named,
      "value": String(value),
      "content": rule,
      ..
    } =>
      Rule::Alias(
        named=@json.from_json!(named),
        value,
        Rule::from_json!(rule, json_path.add_key("content")),
      )
    { "type": "BLANK", .. } => Rule::Blank
    { "type": "SYMBOL", "name": String(name), .. } => Rule::Symbol(name)
    { "type": "STRING", "value": String(value), .. } => Rule::String(value)
    { "type": "CHOICE", "members": Array(members_json), .. } => {
      let members_json_path = json_path.add_key("members")
      let rules = []
      for i, member_json in members_json {
        rules.push(
          Rule::from_json!(member_json, members_json_path.add_index(i)),
        )
      }
      Rule::Choice(rules)
    }
    { "type": "SEQ", "members": Array(members_json), .. } => {
      let members_json_path = json_path.add_key("members")
      let rules = []
      for i, member_json in members_json {
        rules.push(
          Rule::from_json!(member_json, members_json_path.add_index(i)),
        )
      }
      Rule::Seq(rules)
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
      Rule::Field(name~, Rule::from_json!(rule, json_path.add_key("content")))
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
        prec~,
        value=value.to_int(),
        Rule::from_json!(rule, json_path.add_key("content")),
      )
    }
    { "type": "PATTERN", "value": String(value), .. } => Rule::Pattern(value)
    json => {
      let message = "Rule::from_json: expected object with \"type\" field, got \{json}"
      raise @json.JsonDecodeError((json_path, message))
    }
  }
}

///|
impl ToJson for Rule with to_json(self : Rule) -> Json {
  match self {
    Alias(named~, value, rule) =>
      {
        "type": "ALIAS",
        "value": value.to_json(),
        "named": named.to_json(),
        "content": rule.to_json(),
      }
    Prec(prec~, value~, rule) =>
      {
        "type": prec.to_json(),
        "value": value.to_json(),
        "content": rule.to_json(),
      }
    Token(immediate~, rule) => {
      let token_type = if immediate { "IMMEDIATE_TOKEN" } else { "TOKEN" }
      { "type": token_type.to_json(), "content": rule.to_json() }
    }
    Field(name~, rule) =>
      { "type": "FIELD", "name": Json::string(name), "content": rule.to_json() }
    Seq(rules) => { "type": "SEQ", "members": rules.to_json() }
    Choice(rules) => { "type": "CHOICE", "members": rules.to_json() }
    Repeat1(rule) => { "type": "REPEAT1", "content": rule.to_json() }
    Repeat(rule) => { "type": "REPEAT", "content": rule.to_json() }
    String(value) => { "type": "STRING", "value": value.to_json() }
    Symbol(name) => { "type": "SYMBOL", "name": name.to_json() }
    Blank => { "type": "BLANK" }
    Pattern(value) => { "type": "PATTERN", "value": value.to_json() }
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
  self.name.to_json()
}

///|
pub struct Grammar {
  name : String
  rules : Map[String, Rule]
  extras : Array[Rule]
  supertypes : Array[RuleName]
  reserved : Map[String, Rule]
  externals : Array[Rule]
  inline : Array[RuleName]
  conflicts : Array[Array[RuleName]]
  word : RuleName?
} derive(@json.FromJson(fields(reserved(default={}))), Show, ToJson)

///|
type! GrammarParseError {
  JsonDecodeError(@json.JsonDecodeError)
  RuleNotFound(String)
} derive(Show)

///|
pub fn Grammar::from_json(json : Json) -> Grammar!GrammarParseError {
  let grammar : Grammar = try {
    @json.from_json!(json)
  } catch {
    error => raise JsonDecodeError(error)
  }
  for _, rule in grammar.rules {
    let visitor = fn(rule : Rule) -> Unit!GrammarParseError {
      match rule {
        Symbol(name) =>
          if grammar.rules.get(name) is None {
            raise RuleNotFound(name)
          }
        _ => return
      }
    }
    rule.visit_rule!(visitor)
  }
  for supertype in grammar.supertypes {
    guard grammar.rules.get(supertype.name) is Some(rule) else {
      raise RuleNotFound(supertype.name)
    }
    supertype.rule = Some(rule)
  }
  for inline in grammar.inline {
    guard grammar.rules.get(inline.name) is Some(rule) else {
      raise RuleNotFound(inline.name)
    }
    inline.rule = Some(rule)
  }
  for conflict in grammar.conflicts {
    for rule_name in conflict {
      guard grammar.rules.get(rule_name.name) is Some(rule) else {
        raise RuleNotFound(rule_name.name)
      }
      rule_name.rule = Some(rule)
    }
  }
  if grammar.word is Some(word) {
    guard grammar.rules.get(word.name) is Some(rule) else {
      raise RuleNotFound(word.name)
    }
    word.rule = Some(rule)
  }
  grammar
}

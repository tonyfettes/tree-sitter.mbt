# Pattern Grammar

The Pattern Grammar is a specialized syntax for creating pattern-matching
queries in MoonBit code. It provides a powerful way to search for specific code
patterns and extract information from them.

## Overview

The Pattern Grammar allows you to:

- Match specific code structures in MoonBit source files
- Extract variables from matched patterns
- Use quantifiers to match repeated patterns
- Group patterns together for more complex matching

This grammar is implemented using
[tree-sitter](https://tree-sitter.github.io/tree-sitter/), a parser generator
tool that can build concrete syntax trees for source code.

## Syntax

### Basic Syntax

The pattern grammar consists of two main elements:

1. **Literals**: Regular text that matches exactly in the source code
2. **Patterns**: Special syntax that matches specific code structures

### Variable Patterns

Variable patterns allow you to capture specific parts of the code:

```moonbit
$<entry>:<identifier>
```

Where:

- `<entry>` is the type of pattern to match (e.g., `exp`, `pat`, `id`, `ty`)
- `<identifier>` is the name you give to the captured value

For example, `$exp:a` would match an expression and capture it with the name
"a".

### Group Patterns

Group patterns allow you to group multiple patterns together:

```moonbit
${...}
```

You can also apply quantifiers to groups:

```moonbit
${...}*  // Match zero or more times
${...}+  // Match one or more times
${...}?  // Match zero or one time
```

### Escaping

To include literal characters that would otherwise be interpreted as part of the
pattern syntax:

- `\$` to include a literal dollar sign
- `\{` to include a literal opening brace
- `\}` to include a literal closing brace
- `\\` to include a literal backslash

## Available Pattern Types

The pattern grammar supports several types of patterns:

- `exp`: Matches expressions
- `top`: Matches top-level structure items
- `pat`: Matches patterns
- `id`: Matches identifiers
- `ty`: Matches types

## Examples

### Matching Simple Expressions

```moonbit
$exp:a == $exp:b
```

This pattern matches expressions like `1 == 2` and captures the left side as "a"
and the right side as "b".

### Matching Function Definitions

```moonbit
fn $id:name() -> $ty:ret {
  $exp:body
}
```

This pattern matches function definitions with no parameters and exactly one
expression in their body, and captures the function name and body.

### Using Quantifiers

```moonbit
guard $exp:condition is $pat:pattern else {
  ${
    $exp:statement
  }*
  return $exp:result
}
```

This pattern matches a guard expression with zero or more statements before the
return statement.

### Matching Multiple Patterns

```moonbit
match $exp:value {
  $pat:pattern => $exp:result
}
```

This pattern matches a match expression with a single case.

## Usage in Code

The pattern grammar is used through the `@pattern.Language` API:

```moonbit
test {
  // Create a language instance
  let language = moonbit!()

  // Compile a pattern query
  let query = language.compile!("$exp:a == $exp:b")

  // Search for matches in source code
  let matches = query.search!("fn main { 1 == 2 }")

  // Process the matches
  for matched in matches {
    println(matched["a"])  // Prints "1"
    println(matched["b"])  // Prints "2"
  }
}
```

## Advanced Features

### Context-Aware Matching

The pattern system is context-aware, meaning it can match patterns in different
contexts:

- Expression context (`exp`)
- Pattern context (`pat`)
- Type context (`ty`)
- Top-level context (`top`)
- Case clause context (`case`)
- Matrix case clause context (`matrix`)

## Limitations

- Patterns must be valid within their context.
- Complex patterns may require careful construction to match exactly what you
  want.
- The pattern grammar is currently specific to MoonBit and may not work with
  other languages.

## Further Reading

For more details on how to use the pattern grammar, refer to the test cases in
`src/pattern/pattern_test.mbt` which demonstrate various usage scenarios.

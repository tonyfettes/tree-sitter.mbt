# `tonyfettes/tree-sitter/bin/edit`

This package provides a command-line tool to perform structural find and
replace operations on MoonBit source files.

## Usage

To use this tool, run the following command:

```bash
moon run edit --target native <ruleset_path> <source_path>
```

Where `<ruleset_path>` is the path to a YAML file containing the ruleset to
apply to the source file at `<source_path>`.

## Ruleset

The ruleset file is a YAML file that contains a list of rules to apply to the
source file. Each rule is a mapping with the following keys:

- `search`: The tree-sitter query to match against the source file. The syntax
  of the query is described in the
  [Queries](https://tree-sitter.github.io/tree-sitter/using-parsers/queries/index.html)
  section of the Tree-sitter User Guide. Note that predicates/directives are
  implemented by this tool not by the tree-sitter library, therefore only the
  following predicates are supported.

  - `#eq?`: Test if two captured string are equal.
  - `#match?`: Test if a captured string matches a regular expression. In additional
    to the standard `#match?` behavior, this tool also support referencing the
    named capture group in the following `replace` string of the rule.

- `replace`: The text to replace the matched pattern with. It may contains
  references to capture groups in the `search` pattern using the syntax `$<name>`,
  where `<name>` is the name of the capture group. Additionally, if you
  use the `#match?` predicate in the `search` pattern, you can reference the
  named captures in the regex pattern using the syntax `$<name>`.

We have included a sample ruleset file at `replace.yml` in this directory for
your reference.

It often helps a lot to use the
[Tree-sitter MoonBit Playground](https://moonbitlang.github.io/tree-sitter-moonbit/)
to debug the your `search` queries when creating the ruleset file.

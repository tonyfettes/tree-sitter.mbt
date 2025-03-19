# `tonyfettes/tree_sitter/test`

This module is contains tests for `tonyfettes/tree_sitter`.

## Running the tests

Use

```bash
moon test --target native
```

to run the tests, and

```bash
moon test --target native --update
```

to promote the test results.

## Test descriptions

Here is a brief description of the tests:

- `query_test.mbt`: Test the query API from the Tree-sitter library.
- `parser_test.mbt`: Test the parser API from the Tree-sitter library.
- `pattern_test.mbt`: Includes a simple human-readable pattern language that is
  transpiled to Tree-sitter queries.
- `edit_test.mbt`: Tests related to the `tonyfettes/tree-sitter/bin/edit` tool.

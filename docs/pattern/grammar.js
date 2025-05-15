/**
 * @file Pattern grammar for tree-sitter
 * @author Haoxiang Fei <feihaoxiang@idea.edu.cn>
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "pattern",

  rules: {
    source_file: ($) => repeat(choice($.literal, $.pattern)),

    segment: (_) => /[^$]+/,

    quantifier: (_) => choice("*", "+", "?"),

    dollar: (_) => "\\$",

    literal: ($) => choice($.segment, $.dollar),

    identifier: (_) => /[a-zA-Z_][a-zA-Z0-9_]*/,

    entry: ($) => $.identifier,

    variable_pattern: ($) => seq("$", $.entry, ":", $.identifier),

    group_segment: (_) => /[^${}\\]+/,

    group_literal: ($) =>
      choice($.group_segment, $.dollar, "\\{", "\\}", "\\\\"),

    group_pattern: ($) =>
      seq(
        "$",
        "{",
        repeat1(choice($.group_literal, $.pattern)),
        choice("}", "}*", "}+", "}?", "}\\*", "}\\+", "}\\?")
      ),

    pattern: ($) => choice($.group_pattern, $.variable_pattern),
  },
});

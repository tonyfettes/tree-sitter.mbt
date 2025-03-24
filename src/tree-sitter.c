#include "tree-sitter/lib/src/lib.c"
#include "tree_sitter/api.h"
#include <assert.h>
#include <moonbit.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __TINYC__
#define static_assert_type_equal(type, expected)                               \
  static_assert(                                                               \
    _Generic((type)0, expected: 1, default: 0), #type " is not " #expected     \
  )
#else
#define static_assert_type_equal(...)
#endif

const TSLanguage *
moonbit_ts_language_copy(const TSLanguage *self) {
  return ts_language_copy(self);
}

void
moonbit_ts_language_delete(const TSLanguage *self) {
  ts_language_delete(self);
}

static inline int32_t
moonbit_uint_to_int(uint32_t value) {
  assert(value <= INT32_MAX);
  return (int32_t)value;
}

uint32_t
moonbit_ts_language_symbol_count(const TSLanguage *self) {
  return ts_language_symbol_count(self);
}

uint32_t
moonbit_ts_language_state_count(const TSLanguage *self) {
  return ts_language_state_count(self);
}

static_assert_type_equal(TSSymbol, uint16_t);

TSSymbol
moonbit_ts_language_symbol_for_name(
  const TSLanguage *self,
  moonbit_bytes_t name,
  bool is_named
) {
  uint32_t length = Moonbit_array_length(name);
  TSSymbol symbol =
    ts_language_symbol_for_name(self, (const char *)name, length, is_named);
  moonbit_decref(name);
  return symbol;
}

uint32_t
moonbit_ts_language_field_count(const TSLanguage *self) {
  return ts_language_field_count(self);
}

static inline int32_t
moonbit_size_to_int(size_t value) {
  assert(value <= INT32_MAX);
  return (int32_t)value;
}

static inline moonbit_bytes_t
moonbit_make_bytes_sz(size_t size, int value) {
  return moonbit_make_bytes(moonbit_size_to_int(size), value);
}

moonbit_bytes_t
moonbit_ts_language_field_name_for_id(const TSLanguage *self, TSFieldId id) {
  const char *name = ts_language_field_name_for_id(self, id);
  size_t length = strlen(name);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, name, length);
  return bytes;
}

TSFieldId
moonbit_ts_language_field_id_for_name(
  const TSLanguage *self,
  moonbit_bytes_t name
) {
  uint32_t length = Moonbit_array_length(name);
  TSFieldId id =
    ts_language_field_id_for_name(self, (const char *)name, length);
  moonbit_decref(name);
  return id;
}

TSSymbol *
moonbit_ts_language_supertypes(const TSLanguage *self) {
  uint32_t length;
  const TSSymbol *supertypes = ts_language_supertypes(self, &length);
  TSSymbol *copy = (TSSymbol *)moonbit_make_bytes_sz(length, 0);
  memcpy(copy, supertypes, length * sizeof(TSSymbol));
  return copy;
}

TSSymbol *
moonbit_ts_language_subtypes(const TSLanguage *self, TSSymbol supertype) {
  uint32_t length;
  const TSSymbol *subtypes = ts_language_subtypes(self, supertype, &length);
  TSSymbol *copy = (TSSymbol *)moonbit_make_bytes_sz(length, 0);
  memcpy(copy, subtypes, length * sizeof(TSSymbol));
  return copy;
}

moonbit_bytes_t
moonbit_ts_language_symbol_name(const TSLanguage *self, TSSymbol symbol) {
  const char *name = ts_language_symbol_name(self, symbol);
  size_t length = strlen(name);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, name, length);
  return bytes;
}

static_assert_type_equal(TSSymbolType, uint32_t);

TSSymbolType
moonbit_ts_language_symbol_type(const TSLanguage *self, TSSymbol symbol) {
  return ts_language_symbol_type(self, symbol);
}

uint32_t
moonbit_ts_language_version(const TSLanguage *self) {
  return ts_language_version(self);
}

uint32_t
moonbit_ts_language_abi_version(const TSLanguage *self) {
  return ts_language_abi_version(self);
}

moonbit_bytes_t
moonbit_ts_language_metadata(const TSLanguage *self) {
  const TSLanguageMetadata *metadata = ts_language_metadata(self);
  moonbit_bytes_t bytes = moonbit_make_bytes(3, 0);
  bytes[0] = metadata->major_version;
  bytes[1] = metadata->minor_version;
  bytes[2] = metadata->patch_version;
  return bytes;
}

static_assert_type_equal(TSStateId, uint16_t);

TSStateId
moonbit_ts_language_next_state(
  const TSLanguage *self,
  TSStateId state,
  TSSymbol symbol
) {
  return ts_language_next_state(self, state, symbol);
}

const char *
moonbit_ts_language_name(const TSLanguage *self) {
  return ts_language_name(self);
}

typedef struct MoonBitTSParser {
  TSParser *parser;
} MoonBitTSParser;

void
moonbit_ts_parser_delete(void *object) {
  MoonBitTSParser *parser = (MoonBitTSParser *)object;
  ts_parser_delete(parser->parser);
}

MoonBitTSParser *
moonbit_ts_parser_new(void) {
  MoonBitTSParser *parser = (MoonBitTSParser *)moonbit_make_external_object(
    moonbit_ts_parser_delete, sizeof(TSParser *)
  );
  parser->parser = ts_parser_new();
  return parser;
}

const TSLanguage *
moonbit_ts_parser_language(MoonBitTSParser *parser) {
  const TSLanguage *language = ts_parser_language(parser->parser);
  moonbit_decref(parser);
  return language;
}

bool
moonbit_ts_parser_set_language(MoonBitTSParser *parser, TSLanguage *language) {
  bool result = ts_parser_set_language(parser->parser, language);
  moonbit_decref(parser);
  return result;
}

static inline uint32_t
moonbit_size_to_uint(size_t value) {
  assert(value <= UINT32_MAX);
  return (uint32_t)value;
}

bool
moonbit_ts_parser_set_included_ranges(
  MoonBitTSParser *parser,
  uint32_t *ranges
) {
  size_t length = Moonbit_array_length(ranges);
  uint32_t count =
    moonbit_size_to_uint(length * sizeof(uint32_t) / sizeof(TSRange));
  bool result =
    ts_parser_set_included_ranges(parser->parser, (TSRange *)ranges, count);
  moonbit_decref(parser);
  moonbit_decref(ranges);
  return result;
}

TSRange *
moonbit_ts_parser_included_ranges(MoonBitTSParser *self) {
  uint32_t count = 0;
  const TSRange *ranges = ts_parser_included_ranges(self->parser, &count);
  moonbit_decref(self->parser);
  TSRange *copy = (TSRange *)moonbit_make_int32_array(
    count * sizeof(TSRange) / sizeof(int32_t), 0
  );
  memcpy(copy, ranges, count * sizeof(TSRange));
  return copy;
}

struct MoonBitTSInputRead {
  moonbit_bytes_t (*read)(
    struct MoonBitTSInputRead *payload,
    uint32_t byte,
    TSPoint *position
  );
};

static inline const char *
moonbit_ts_input_read(
  void *payload,
  uint32_t byte,
  TSPoint position,
  uint32_t *bytes_read
) {
  struct MoonBitTSInputRead *input = (struct MoonBitTSInputRead *)payload;
  TSPoint *point =
    (TSPoint *)moonbit_make_int32_array(sizeof(TSPoint) / sizeof(int32_t), 0);
  *point = position;
  moonbit_bytes_t bytes = input->read(input, byte, point);
  *bytes_read = Moonbit_array_length(bytes);
  return (const char *)bytes;
}

TSTree *
moonbit_ts_parser_parse(
  MoonBitTSParser *self,
  TSTree *old_tree,
  struct MoonBitTSInputRead *input,
  TSInputEncoding encoding,
  DecodeFunction decode
) {
  TSInput ts_input = {
    .payload = input,
    .read = moonbit_ts_input_read,
    .encoding = encoding,
    .decode = decode
  };
  TSTree *tree = ts_parser_parse(self->parser, old_tree, ts_input);
  moonbit_decref(self);
  return tree;
}

struct MoonBitTSParseOptionsProgressCallback {
  bool (*progress_callback)(
    struct MoonBitTSParseOptionsProgressCallback *callback,
    uint32_t current_byte_offset,
    bool has_error
  );
};

static inline bool
moonbit_ts_parse_options_progress_callback(TSParseState *state) {
  struct MoonBitTSParseOptionsProgressCallback *callback =
    (struct MoonBitTSParseOptionsProgressCallback *)state->payload;
  return callback->progress_callback(
    callback, state->current_byte_offset, state->has_error
  );
}

TSTree *
moonbit_ts_parser_parse_with_options(
  MoonBitTSParser *self,
  TSTree *old_tree,
  struct MoonBitTSInputRead *input,
  TSInputEncoding encoding,
  DecodeFunction decode,
  struct MoonBitTSParseOptionsProgressCallback *callback
) {
  TSInput ts_input = {
    .payload = input,
    .read = moonbit_ts_input_read,
    .encoding = encoding,
    .decode = decode
  };
  TSParseOptions options = {
    .payload = callback,
    .progress_callback = moonbit_ts_parse_options_progress_callback
  };
  TSTree *tree =
    ts_parser_parse_with_options(self->parser, old_tree, ts_input, options);
  moonbit_decref(self);
  return tree;
}

TSTree *
moonbit_ts_parser_parse_string(
  MoonBitTSParser *parser,
  TSTree *old_tree,
  moonbit_bytes_t bytes
) {
  uint32_t length = Moonbit_array_length(bytes);
  TSTree *tree = ts_parser_parse_string(
    parser->parser, old_tree, (const char *)bytes, length
  );
  moonbit_decref(parser);
  moonbit_decref(bytes);
  return tree;
}

TSTree *
moonbit_ts_parser_parse_string_encoding(
  MoonBitTSParser *parser,
  TSTree *old_tree,
  moonbit_bytes_t bytes,
  TSInputEncoding encoding
) {
  uint32_t length = Moonbit_array_length(bytes);
  TSTree *tree = ts_parser_parse_string_encoding(
    parser->parser, old_tree, (const char *)bytes, length, encoding
  );
  moonbit_decref(parser);
  moonbit_decref(bytes);
  return tree;
}

void
moonbit_ts_parser_reset(MoonBitTSParser *self) {
  ts_parser_reset(self->parser);
  moonbit_decref(self);
}

struct MoonBitTSLogger {
  void (*log)(
    struct MoonBitTSLogger *payload,
    TSLogType log_type,
    moonbit_bytes_t buffer
  );
};

void
moonbit_ts_logger_log(void *payload, TSLogType log_type, const char *buffer) {
  struct MoonBitTSLogger *logger = (struct MoonBitTSLogger *)payload;
  size_t length = strlen(buffer);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, buffer, length);
  logger->log(logger, log_type, bytes);
}

void
moonbit_ts_parser_set_logger(
  MoonBitTSParser *self,
  struct MoonBitTSLogger *logger
) {
  TSLogger ts_logger = {.payload = logger, .log = moonbit_ts_logger_log};
  ts_parser_set_logger(self->parser, ts_logger);
  moonbit_decref(self);
}

struct MoonBitTSLogger *
moonbit_ts_parser_logger(MoonBitTSParser *self) {
  TSLogger logger = ts_parser_logger(self->parser);
  moonbit_decref(self);
  return logger.payload;
}

TSTree *
moonbit_ts_tree_copy(TSTree *self) {
  return ts_tree_copy(self);
}

void
moonbit_ts_tree_delete(TSTree *tree) {
  ts_tree_delete(tree);
}

TSNode *
moonbit_ts_tree_root_node(TSTree *tree) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_tree_root_node(tree);
  return node;
}

TSNode *
moonbit_ts_tree_root_node_with_offset(
  TSTree *tree,
  uint32_t offset_bytes,
  TSPoint *offset_extent
) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_tree_root_node_with_offset(tree, offset_bytes, *offset_extent);
  moonbit_decref(offset_extent);
  return node;
}

const TSLanguage *
moonbit_ts_tree_language(TSTree *tree) {
  return ts_tree_language(tree);
}

TSRange *
moonbit_ts_tree_included_ranges(TSTree *tree) {
  uint32_t count = 0;
  const TSRange *ranges = ts_tree_included_ranges(tree, &count);
  TSRange *copy = (TSRange *)moonbit_make_int32_array(
    count * sizeof(TSRange) / sizeof(int32_t), 0
  );
  memcpy(copy, ranges, count * sizeof(TSRange));
  return copy;
}

void
moonbit_ts_tree_edit(TSTree *tree, TSInputEdit *edit) {
  ts_tree_edit(tree, edit);
  moonbit_decref(edit);
}

TSRange *
moonbit_ts_tree_get_changed_ranges(
  const TSTree *old_tree,
  const TSTree *new_tree
) {
  uint32_t count = 0;
  TSRange *ranges = ts_tree_get_changed_ranges(old_tree, new_tree, &count);
  TSRange *copy = (TSRange *)moonbit_make_int32_array(
    count * sizeof(TSRange) / sizeof(int32_t), 0
  );
  memcpy(copy, ranges, count * sizeof(TSRange));
  return copy;
}

moonbit_bytes_t
moonbit_ts_node_type(TSNode *self) {
  const char *type = ts_node_type(*self);
  moonbit_decref(self);
  size_t length = strlen(type);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, type, length);
  return bytes;
}

TSSymbol
moonbit_ts_node_symbol(TSNode *self) {
  TSSymbol symbol = ts_node_symbol(*self);
  moonbit_decref(self);
  return symbol;
}

const TSLanguage *
moonbit_ts_node_language(TSNode *self) {
  return ts_node_language(*self);
}

moonbit_bytes_t
moonbit_ts_node_grammar_type(TSNode *self) {
  const char *type = ts_node_grammar_type(*self);
  moonbit_decref(self);
  size_t length = strlen(type);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, type, length);
  return bytes;
}

TSSymbol
moonbit_ts_node_grammar_symbol(TSNode *self) {
  TSSymbol symbol = ts_node_grammar_symbol(*self);
  moonbit_decref(self);
  return symbol;
}

uint32_t
moonbit_ts_node_start_byte(TSNode *self) {
  uint32_t byte = ts_node_start_byte(*self);
  moonbit_decref(self);
  return byte;
}

TSPoint *
moonbit_ts_node_start_point(TSNode *self) {
  TSPoint *point = (TSPoint *)moonbit_make_int32_array(
    sizeof(struct TSPoint) / sizeof(int32_t), 0
  );
  *point = ts_node_start_point(*self);
  moonbit_decref(self);
  return point;
}

uint32_t
moonbit_ts_node_end_byte(TSNode *self) {
  uint32_t byte = ts_node_end_byte(*self);
  moonbit_decref(self);
  return byte;
}

TSPoint *
moonbit_ts_node_end_point(TSNode *self) {
  TSPoint *point = (TSPoint *)moonbit_make_int32_array(
    sizeof(struct TSPoint) / sizeof(int32_t), 0
  );
  *point = ts_node_end_point(*self);
  moonbit_decref(self);
  return point;
}

moonbit_bytes_t
moonbit_ts_node_string(TSNode *self) {
  char *string = ts_node_string(*self);
  moonbit_decref(self);
  size_t length = strlen(string);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, string, length);
  free(string);
  return bytes;
}

bool
moonbit_ts_node_is_null(TSNode *self) {
  bool is_null = ts_node_is_null(*self);
  moonbit_decref(self);
  return is_null;
}

bool
moonbit_ts_node_is_named(TSNode *self) {
  bool is_named = ts_node_is_named(*self);
  moonbit_decref(self);
  return is_named;
}

bool
moonbit_ts_node_is_missing(TSNode *self) {
  bool is_missing = ts_node_is_missing(*self);
  moonbit_decref(self);
  return is_missing;
}

bool
moonbit_ts_node_is_extra(TSNode *self) {
  bool is_extra = ts_node_is_extra(*self);
  moonbit_decref(self);
  return is_extra;
}

bool
moonbit_ts_node_has_changes(TSNode *self) {
  bool has_changes = ts_node_has_changes(*self);
  moonbit_decref(self);
  return has_changes;
}

bool
moonbit_ts_node_has_error(TSNode *self) {
  bool has_error = ts_node_has_error(*self);
  moonbit_decref(self);
  return has_error;
}

bool
moonbit_ts_node_is_error(TSNode *self) {
  bool is_error = ts_node_is_error(*self);
  moonbit_decref(self);
  return is_error;
}

TSStateId
moonbit_ts_node_parse_state(TSNode *self) {
  TSStateId state = ts_node_parse_state(*self);
  moonbit_decref(self);
  return state;
}

TSStateId
moonbit_ts_node_next_parse_state(TSNode *self) {
  TSStateId state = ts_node_next_parse_state(*self);
  moonbit_decref(self);
  return state;
}

TSNode *
moonbit_ts_node_parent(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_parent(*self);
  moonbit_decref(self);
  return node;
}

TSNode *
moonbit_ts_node_child_with_descendant(TSNode *self, TSNode *descendant) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_child_with_descendant(*self, *descendant);
  moonbit_decref(self);
  moonbit_decref(descendant);
  return node;
}

TSNode *
moonbit_ts_node_child(TSNode *self, uint32_t child_index) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_child(*self, child_index);
  moonbit_decref(self);
  return node;
}

const char *
moonbit_ts_node_field_name_for_child(TSNode *self, uint32_t child_index) {
  return ts_node_field_name_for_child(*self, child_index);
}

const char *
moonbit_ts_node_field_name_for_named_child(
  TSNode *self,
  uint32_t named_child_index
) {
  return ts_node_field_name_for_named_child(*self, named_child_index);
}

uint32_t
moonbit_ts_node_child_count(TSNode *self) {
  uint32_t count = ts_node_child_count(*self);
  moonbit_decref(self);
  return count;
}

TSNode *
moonbit_ts_node_named_child(TSNode *self, uint32_t child_index) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_named_child(*self, child_index);
  moonbit_decref(self);
  return node;
}

uint32_t
moonbit_ts_node_named_child_count(TSNode *self) {
  uint32_t count = ts_node_named_child_count(*self);
  moonbit_decref(self);
  return count;
}

TSNode *
moonbit_ts_node_child_by_field_name(TSNode *self, moonbit_bytes_t name) {
  uint32_t length = Moonbit_array_length(name);
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_child_by_field_name(*self, (const char *)name, length);
  moonbit_decref(self);
  moonbit_decref(name);
  return node;
}

TSNode *
moonbit_ts_node_child_by_field_id(TSNode *self, TSFieldId field_id) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_child_by_field_id(*self, field_id);
  moonbit_decref(self);
  return node;
}

TSNode *
moonbit_ts_node_next_sibling(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_next_sibling(*self);
  moonbit_decref(self);
  return node;
}

TSNode *
moonbit_ts_node_prev_sibling(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_prev_sibling(*self);
  moonbit_decref(self);
  return node;
}

TSNode *
moonbit_ts_node_next_named_sibling(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_next_named_sibling(*self);
  moonbit_decref(self);
  return node;
}

TSNode *
moonbit_ts_node_prev_named_sibling(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_prev_named_sibling(*self);
  moonbit_decref(self);
  return node;
}

TSNode *
moonbit_ts_node_first_child_for_byte(TSNode *self, uint32_t byte) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_first_child_for_byte(*self, byte);
  moonbit_decref(self);
  return node;
}

TSNode *
moonbit_ts_node_first_named_child_for_byte(TSNode *self, uint32_t byte) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_first_named_child_for_byte(*self, byte);
  moonbit_decref(self);
  return node;
}

uint32_t
moonbit_ts_node_descendant_count(TSNode *self) {
  uint32_t count = ts_node_descendant_count(*self);
  moonbit_decref(self);
  return count;
}

TSNode *
moonbit_ts_node_descendant_for_byte_range(
  TSNode *self,
  uint32_t start,
  uint32_t end
) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_descendant_for_byte_range(*self, start, end);
  moonbit_decref(self);
  return node;
}

TSNode *
moonbit_ts_node_descendant_for_point_range(
  TSNode *self,
  TSPoint *start,
  TSPoint *end
) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_descendant_for_point_range(*self, *start, *end);
  moonbit_decref(self);
  moonbit_decref(start);
  moonbit_decref(end);
  return node;
}

TSNode *
moonbit_ts_node_named_descendant_for_byte_range(
  TSNode *self,
  uint32_t start,
  uint32_t end
) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_named_descendant_for_byte_range(*self, start, end);
  moonbit_decref(self);
  return node;
}

TSNode *
moonbit_ts_node_named_descendant_for_point_range(
  TSNode *self,
  TSPoint *start,
  TSPoint *end
) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_named_descendant_for_point_range(*self, *start, *end);
  moonbit_decref(self);
  moonbit_decref(start);
  moonbit_decref(end);
  return node;
}

void
moonbit_ts_node_edit(TSNode *self, TSInputEdit *edit) {
  ts_node_edit(self, edit);
  moonbit_decref(self);
  moonbit_decref(edit);
}

bool
moonbit_ts_node_eq(TSNode *self, TSNode *other) {
  bool eq = ts_node_eq(*self, *other);
  moonbit_decref(self);
  moonbit_decref(other);
  return eq;
}

TSTreeCursor *
moonbit_ts_tree_cursor_new(TSNode *node) {
  TSTreeCursor *cursor =
    (TSTreeCursor *)moonbit_malloc(sizeof(struct TSTreeCursor));
  *cursor = ts_tree_cursor_new(*node);
  moonbit_decref(node);
  return cursor;
}

void
moonbit_ts_tree_cursor_delete(TSTreeCursor *self) {
  ts_tree_cursor_delete(self);
  moonbit_decref(self);
}

void
moonbit_ts_tree_cursor_reset(TSTreeCursor *self, TSNode *node) {
  ts_tree_cursor_reset(self, *node);
  moonbit_decref(node);
  moonbit_decref(self);
}

void
moonbit_ts_tree_cursor_reset_to(TSTreeCursor *dst, TSTreeCursor *src) {
  ts_tree_cursor_reset_to(dst, src);
  moonbit_decref(src);
  moonbit_decref(dst);
}

TSNode *
moonbit_ts_tree_cursor_current_node(TSTreeCursor *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_tree_cursor_current_node(self);
  moonbit_decref(self);
  return node;
}

const char *
moonbit_ts_tree_cursor_current_field_name(TSTreeCursor *self) {
  return ts_tree_cursor_current_field_name(self);
}

TSFieldId
moonbit_ts_tree_cursor_current_field_id(TSTreeCursor *self) {
  TSFieldId id = ts_tree_cursor_current_field_id(self);
  moonbit_decref(self);
  return id;
}

bool
moonbit_ts_tree_cursor_goto_parent(TSTreeCursor *self) {
  bool result = ts_tree_cursor_goto_parent(self);
  moonbit_decref(self);
  return result;
}

bool
moonbit_ts_tree_cursor_goto_next_sibling(TSTreeCursor *self) {
  bool result = ts_tree_cursor_goto_next_sibling(self);
  moonbit_decref(self);
  return result;
}

bool
moonbit_ts_tree_cursor_goto_first_child(TSTreeCursor *self) {
  bool result = ts_tree_cursor_goto_first_child(self);
  moonbit_decref(self);
  return result;
}

bool
moonbit_ts_tree_cursor_goto_last_child(TSTreeCursor *self) {
  bool result = ts_tree_cursor_goto_last_child(self);
  moonbit_decref(self);
  return result;
}

void
moonbit_ts_tree_cursor_goto_descendant(
  TSTreeCursor *self,
  uint32_t goal_descendant_index
) {
  ts_tree_cursor_goto_descendant(self, goal_descendant_index);
  moonbit_decref(self);
}

uint32_t
moonbit_ts_tree_cursor_current_descendant_index(TSTreeCursor *self) {
  uint32_t index = ts_tree_cursor_current_descendant_index(self);
  moonbit_decref(self);
  return index;
}

uint32_t
moonbit_ts_tree_cursor_current_depth(TSTreeCursor *self) {
  uint32_t depth = ts_tree_cursor_current_depth(self);
  moonbit_decref(self);
  return depth;
}

int64_t
moonbit_ts_tree_cursor_goto_first_child_for_byte(
  TSTreeCursor *self,
  uint32_t goal_byte
) {
  int64_t result = ts_tree_cursor_goto_first_child_for_byte(self, goal_byte);
  moonbit_decref(self);
  return result;
}

int64_t
moonbit_ts_tree_cursor_goto_first_child_for_point(
  TSTreeCursor *self,
  TSPoint *goal_point
) {
  int64_t result = ts_tree_cursor_goto_first_child_for_point(self, *goal_point);
  moonbit_decref(self);
  moonbit_decref(goal_point);
  return result;
}

TSTreeCursor *
moonbit_ts_tree_cursor_copy(TSTreeCursor *cursor) {
  TSTreeCursor *copy =
    (TSTreeCursor *)moonbit_malloc(sizeof(struct TSTreeCursor));
  *copy = ts_tree_cursor_copy(cursor);
  moonbit_decref(cursor);
  return copy;
}

TSQuery *
moonbit_ts_query_new(
  const TSLanguage *language,
  moonbit_bytes_t source,
  uint32_t *error
) {
  uint32_t length = Moonbit_array_length(source);
  TSQuery *query =
    ts_query_new(language, (const char *)source, length, error, error + 1);
  moonbit_decref(source);
  moonbit_decref(error);
  return query;
}

void
moonbit_ts_query_delete(TSQuery *self) {
  ts_query_delete(self);
}

uint32_t
moonbit_ts_query_pattern_count(TSQuery *self) {
  return ts_query_pattern_count(self);
}

uint32_t
moonbit_ts_query_capture_count(TSQuery *self) {
  return ts_query_capture_count(self);
}

uint32_t
moonbit_ts_query_string_count(TSQuery *self) {
  return ts_query_string_count(self);
}

uint32_t
moonbit_ts_query_start_byte_for_pattern(TSQuery *self, uint32_t pattern_index) {
  return ts_query_start_byte_for_pattern(self, pattern_index);
}

uint32_t
moonbit_ts_query_end_byte_for_pattern(TSQuery *self, uint32_t pattern_index) {
  return ts_query_end_byte_for_pattern(self, pattern_index);
}

static_assert_type_equal(TSQueryPredicateStepType, uint32_t);

uint32_t *
moonbit_ts_query_predicates_for_pattern(TSQuery *self, uint32_t pattern_index) {
  uint32_t step_count = 0;
  const TSQueryPredicateStep *predicates =
    ts_query_predicates_for_pattern(self, pattern_index, &step_count);
  uint32_t *copy = (uint32_t *)moonbit_make_int32_array(
    moonbit_uint_to_int(step_count * 2), 0
  );
  for (uint32_t i = 0; i < step_count; i++) {
    copy[i * 2] = predicates[i].type;
    copy[i * 2 + 1] = predicates[i].value_id;
  }
  return copy;
}

bool
moonbit_ts_query_is_pattern_rooted(TSQuery *self, uint32_t pattern_index) {
  return ts_query_is_pattern_rooted(self, pattern_index);
}

bool
moonbit_ts_query_is_pattern_non_local(TSQuery *self, uint32_t pattern_index) {
  return ts_query_is_pattern_non_local(self, pattern_index);
}

bool
moonbit_ts_query_is_pattern_guaranteed_at_step(
  TSQuery *self,
  uint32_t byte_offset
) {
  return ts_query_is_pattern_guaranteed_at_step(self, byte_offset);
}

moonbit_bytes_t
moonbit_ts_query_capture_name_for_id(TSQuery *self, uint32_t index) {
  uint32_t length;
  const char *name = ts_query_capture_name_for_id(self, index, &length);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, name, length);
  return bytes;
}

static_assert_type_equal(TSQuantifier, uint32_t);

TSQuantifier
moonbit_ts_query_capture_quantifier_for_id(
  TSQuery *self,
  uint32_t pattern_index,
  uint32_t capture_index
) {
  return ts_query_capture_quantifier_for_id(self, pattern_index, capture_index);
}

moonbit_bytes_t
moonbit_ts_query_string_value_for_id(TSQuery *self, uint32_t index) {
  uint32_t length;
  const char *value = ts_query_string_value_for_id(self, index, &length);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, value, length);
  return bytes;
}

void
moonbit_ts_query_disable_capture(TSQuery *self, moonbit_bytes_t name) {
  ts_query_disable_capture(
    self, (const char *)name, Moonbit_array_length(name)
  );
  moonbit_decref(name);
}

void
moonbit_ts_query_disable_pattern(TSQuery *self, uint32_t pattern_index) {
  ts_query_disable_pattern(self, pattern_index);
}

TSQueryCursor *
moonbit_ts_query_cursor_new(void) {
  return ts_query_cursor_new();
}

void
moonbit_ts_query_cursor_delete(TSQueryCursor *self) {
  ts_query_cursor_delete(self);
}

void
moonbit_ts_query_cursor_exec(
  TSQueryCursor *self,
  TSQuery *query,
  TSNode *node
) {
  ts_query_cursor_exec(self, query, *node);
  moonbit_decref(node);
}

typedef struct MoonBitTSQueryCursorProgressCallback {
  bool (*progress_callback)(
    struct MoonBitTSQueryCursorProgressCallback *callback,
    uint32_t current_byte_offset
  );
} MoonBitTSQueryCursorProgressCallback;

static inline bool
moonbit_ts_query_cursor_progress_callback(TSQueryCursorState *state) {
  MoonBitTSQueryCursorProgressCallback *callback =
    (MoonBitTSQueryCursorProgressCallback *)state->payload;
  return callback->progress_callback(callback, state->current_byte_offset);
}

void
moonbit_ts_query_cursor_exec_with_options(
  TSQueryCursor *self,
  TSQuery *query,
  TSNode *node,
  MoonBitTSQueryCursorProgressCallback *callback
) {
  TSQueryCursorOptions options = {
    .payload = callback,
    .progress_callback = moonbit_ts_query_cursor_progress_callback
  };
  ts_query_cursor_exec_with_options(self, query, *node, &options);
  moonbit_decref(node);
}

bool
moonbit_ts_query_cursor_did_exceed_match_limit(TSQueryCursor *self) {
  return ts_query_cursor_did_exceed_match_limit(self);
}

uint32_t
moonbit_ts_query_cursor_match_limit(TSQueryCursor *self) {
  return ts_query_cursor_match_limit(self);
}

void
moonbit_ts_query_cursor_set_match_limit(TSQueryCursor *self, uint32_t limit) {
  ts_query_cursor_set_match_limit(self, limit);
}

void
moonbit_ts_query_cursor_set_byte_range(
  TSQueryCursor *self,
  uint32_t start_byte,
  uint32_t end_byte
) {
  ts_query_cursor_set_byte_range(self, start_byte, end_byte);
}

void
moonbit_ts_query_cursor_set_point_range(
  TSQueryCursor *self,
  TSPoint *start_point,
  TSPoint *end_point
) {
  ts_query_cursor_set_point_range(self, *start_point, *end_point);
  moonbit_decref(start_point);
  moonbit_decref(end_point);
}

TSQueryMatch *
moonbit_ts_query_cursor_next_match(TSQueryCursor *self) {
  TSQueryMatch *match =
    (TSQueryMatch *)moonbit_malloc(sizeof(struct TSQueryMatch));
  bool has_match = ts_query_cursor_next_match(self, match);
  if (has_match) {
    return match;
  } else {
    moonbit_decref(match);
    return NULL;
  }
}

void
moonbit_ts_query_cursor_remove_match(TSQueryCursor *self, uint32_t match_id) {
  ts_query_cursor_remove_match(self, match_id);
}

TSQueryMatch *
moonbit_ts_query_cursor_next_capture(TSQueryCursor *self, uint32_t *match_id) {
  TSQueryMatch *match =
    (TSQueryMatch *)moonbit_malloc(sizeof(struct TSQueryMatch));
  bool has_match = ts_query_cursor_next_capture(self, match, match_id);
  moonbit_decref(match_id);
  if (has_match) {
    return match;
  } else {
    moonbit_decref(match);
    return NULL;
  }
}

void
moonbit_ts_query_cursor_set_max_start_depth(
  TSQueryCursor *self,
  uint32_t max_start_depth
) {
  ts_query_cursor_set_max_start_depth(self, max_start_depth);
}

uint32_t
moonbit_ts_query_match_id(TSQueryMatch *self) {
  uint32_t id = self->id;
  moonbit_decref(self);
  return id;
}

uint16_t
moonbit_ts_query_match_pattern_index(TSQueryMatch *self) {
  uint16_t index = self->pattern_index;
  moonbit_decref(self);
  return index;
}

uint16_t
moonbit_ts_query_match_capture_count(TSQueryMatch *self) {
  uint16_t count = self->capture_count;
  moonbit_decref(self);
  return count;
}

TSNode *
moonbit_ts_query_match_captures_get_node(TSQueryMatch *self, uint32_t index) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = self->captures[index].node;
  moonbit_decref(self);
  return node;
}

uint32_t
moonbit_ts_query_match_captures_get_index(TSQueryMatch *self, uint32_t index) {
  uint32_t i = self->captures[index].index;
  moonbit_decref(self);
  return i;
}

TSLookaheadIterator *
moonbit_ts_lookahead_iterator_new(TSLanguage *language, TSStateId state) {
  return ts_lookahead_iterator_new(language, state);
}

void
moonbit_ts_lookahead_iterator_delete(TSLookaheadIterator *self) {
  ts_lookahead_iterator_delete(self);
}

bool
moonbit_ts_lookahead_iterator_reset_state(
  TSLookaheadIterator *self,
  TSStateId state
) {
  return ts_lookahead_iterator_reset_state(self, state);
}

bool
moonbit_ts_lookahead_iterator_reset(
  TSLookaheadIterator *self,
  TSLanguage *language,
  TSStateId state
) {
  return ts_lookahead_iterator_reset(self, language, state);
}

const TSLanguage *
moonbit_ts_lookahead_iterator_language(const TSLookaheadIterator *self) {
  return ts_lookahead_iterator_language(self);
}

bool
moonbit_ts_lookahead_iterator_next(TSLookaheadIterator *self) {
  return ts_lookahead_iterator_next(self);
}

TSSymbol
moonbit_ts_lookahead_iterator_current_symbol(const TSLookaheadIterator *self) {
  return ts_lookahead_iterator_current_symbol(self);
}

moonbit_bytes_t
moonbit_ts_lookahead_iterator_current_symbol_name(
  const TSLookaheadIterator *self
) {
  const char *name = ts_lookahead_iterator_current_symbol_name(self);
  size_t length = strlen(name);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, name, length);
  return bytes;
}

#include "tree-sitter-lib/tree_sitter/api.h"
#include <assert.h>
#include <moonbit.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#ifdef DEBUG
#include <stdio.h>
#define moonbit_ts_trace(format, ...)                                          \
  fprintf(stderr, "%s: " format, __func__, __VA_ARGS__)
#else
#define moonbit_ts_trace(...)
#endif

#if defined (__GNUC__) || defined (__clang__)
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

static inline void
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

typedef struct MoonBitTSTree {
  TSTree *tree;
} MoonBitTSTree;

static inline void
moonbit_ts_tree_delete(void *object) {
  MoonBitTSTree *tree = (MoonBitTSTree *)object;
  moonbit_ts_trace("tree = %p\n", tree);
  moonbit_ts_trace("tree->tree = %p\n", tree->tree);
  ts_tree_delete(tree->tree);
}

MoonBitTSTree *
moonbit_ts_parser_parse(
  MoonBitTSParser *self,
  MoonBitTSTree *old_tree,
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
  TSTree *ts_old_tree = NULL;
  if (old_tree) {
    ts_old_tree = old_tree->tree;
  }
  MoonBitTSTree *tree = (MoonBitTSTree *)moonbit_make_external_object(
    moonbit_ts_tree_delete, sizeof(TSTree *)
  );
  tree->tree = ts_parser_parse(self->parser, ts_old_tree, ts_input);
  moonbit_decref(self);
  if (old_tree) {
    moonbit_decref(old_tree);
  }
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

MoonBitTSTree *
moonbit_ts_parser_parse_with_options(
  MoonBitTSParser *self,
  MoonBitTSTree *old_tree,
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
  TSTree *ts_old_tree = NULL;
  if (old_tree) {
    ts_old_tree = old_tree->tree;
  }
  MoonBitTSTree *tree = (MoonBitTSTree *)moonbit_make_external_object(
    moonbit_ts_tree_delete, sizeof(MoonBitTSTree *)
  );
  tree->tree =
    ts_parser_parse_with_options(self->parser, ts_old_tree, ts_input, options);
  moonbit_decref(self);
  if (old_tree) {
    moonbit_decref(old_tree);
  }
  return tree;
}

MoonBitTSTree *
moonbit_ts_parser_parse_string(
  MoonBitTSParser *parser,
  MoonBitTSTree *old_tree,
  moonbit_bytes_t bytes
) {
  uint32_t length = Moonbit_array_length(bytes);
  TSTree *old_ts_tree = NULL;
  if (old_tree) {
    old_ts_tree = old_tree->tree;
  }
  MoonBitTSTree *tree = (MoonBitTSTree *)moonbit_make_external_object(
    moonbit_ts_tree_delete, sizeof(MoonBitTSTree *)
  );
  moonbit_ts_trace("tree = %p\n", tree);
  tree->tree = ts_parser_parse_string(
    parser->parser, old_ts_tree, (const char *)bytes, length
  );
  moonbit_ts_trace("tree->tree = %p\n", tree->tree);
  moonbit_decref(parser);
  if (old_tree) {
    moonbit_decref(old_tree);
  }
  moonbit_decref(bytes);
  return tree;
}

MoonBitTSTree *
moonbit_ts_parser_parse_string_encoding(
  MoonBitTSParser *parser,
  MoonBitTSTree *old_tree,
  moonbit_bytes_t bytes,
  TSInputEncoding encoding
) {
  uint32_t length = Moonbit_array_length(bytes);
  TSTree *old_ts_tree = NULL;
  if (old_tree) {
    old_ts_tree = old_tree->tree;
  }
  MoonBitTSTree *tree = (MoonBitTSTree *)moonbit_make_external_object(
    moonbit_ts_tree_delete, sizeof(MoonBitTSTree *)
  );
  moonbit_ts_trace(
    "moonbit_ts_parser_parse_string_encoding: tree = %p\n", tree
  );
  tree->tree = ts_parser_parse_string_encoding(
    parser->parser, old_ts_tree, (const char *)bytes, length, encoding
  );
  moonbit_ts_trace(
    "moonbit_ts_parser_parse_string_encoding: tree->tree = %p\n", tree->tree
  );
  moonbit_decref(parser);
  if (old_tree) {
    moonbit_decref(old_tree);
  }
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

MoonBitTSTree *
moonbit_ts_tree_copy(MoonBitTSTree *self) {
  MoonBitTSTree *tree = (MoonBitTSTree *)moonbit_make_external_object(
    moonbit_ts_tree_delete, sizeof(MoonBitTSTree *)
  );
  tree->tree = ts_tree_copy(self->tree);
  moonbit_decref(self);
  return tree;
}

typedef struct MoonBitTSNode {
  TSNode node;
  MoonBitTSTree *tree;
} MoonBitTSNode;

static inline void
moonbit_ts_node_delete(void *object) {
  MoonBitTSNode *self = (MoonBitTSNode *)object;
  moonbit_ts_trace("self = %p\n", self);
  moonbit_ts_trace("self->tree = %p\n", self->tree);
  moonbit_decref(self->tree);
}

static inline MoonBitTSNode *
moonbit_ts_node_new(TSNode node, MoonBitTSTree *tree) {
  MoonBitTSNode *self = (MoonBitTSNode *)moonbit_make_external_object(
    moonbit_ts_node_delete, sizeof(MoonBitTSNode)
  );
  self->node = node;
  self->tree = tree;
  moonbit_ts_trace("self = %p\n", self);
  moonbit_ts_trace("self->node.id = %p\n", self->node.id);
  moonbit_ts_trace("self->tree = %p\n", self->tree);
  return self;
}

static inline MoonBitTSTree *
moonbit_ts_node_tree(MoonBitTSNode *node) {
  MoonBitTSTree *tree = node->tree;
  moonbit_incref(tree);
  moonbit_decref(node);
  return tree;
}

MoonBitTSNode *
moonbit_ts_tree_root_node(MoonBitTSTree *tree) {
  TSNode node = ts_tree_root_node(tree->tree);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_tree_root_node_with_offset(
  MoonBitTSTree *tree,
  uint32_t offset_bytes,
  TSPoint *offset_extent
) {
  TSNode node =
    ts_tree_root_node_with_offset(tree->tree, offset_bytes, *offset_extent);
  moonbit_decref(offset_extent);
  return moonbit_ts_node_new(node, tree);
}

const TSLanguage *
moonbit_ts_tree_language(MoonBitTSTree *tree) {
  const TSLanguage *language = ts_tree_language(tree->tree);
  moonbit_decref(tree);
  return language;
}

TSRange *
moonbit_ts_tree_included_ranges(MoonBitTSTree *tree) {
  uint32_t count = 0;
  const TSRange *ranges = ts_tree_included_ranges(tree->tree, &count);
  moonbit_decref(tree);
  TSRange *copy = (TSRange *)moonbit_make_int32_array(
    count * sizeof(TSRange) / sizeof(int32_t), 0
  );
  memcpy(copy, ranges, count * sizeof(TSRange));
  return copy;
}

void
moonbit_ts_tree_edit(MoonBitTSTree *tree, TSInputEdit *edit) {
  ts_tree_edit(tree->tree, edit);
  moonbit_decref(tree);
  moonbit_decref(edit);
}

TSRange *
moonbit_ts_tree_get_changed_ranges(
  MoonBitTSTree *old_tree,
  MoonBitTSTree *new_tree
) {
  uint32_t count = 0;
  TSRange *ranges =
    ts_tree_get_changed_ranges(old_tree->tree, new_tree->tree, &count);
  moonbit_decref(old_tree);
  moonbit_decref(new_tree);
  TSRange *copy = (TSRange *)moonbit_make_int32_array(
    count * sizeof(TSRange) / sizeof(int32_t), 0
  );
  memcpy(copy, ranges, count * sizeof(TSRange));
  return copy;
}

moonbit_bytes_t
moonbit_ts_node_type(MoonBitTSNode *self) {
  const char *type = ts_node_type(self->node);
  moonbit_decref(self);
  size_t length = strlen(type);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, type, length);
  return bytes;
}

TSSymbol
moonbit_ts_node_symbol(MoonBitTSNode *self) {
  TSSymbol symbol = ts_node_symbol(self->node);
  moonbit_decref(self);
  return symbol;
}

const TSLanguage *
moonbit_ts_node_language(MoonBitTSNode *self) {
  return ts_node_language(self->node);
}

moonbit_bytes_t
moonbit_ts_node_grammar_type(MoonBitTSNode *self) {
  const char *type = ts_node_grammar_type(self->node);
  moonbit_decref(self);
  size_t length = strlen(type);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, type, length);
  return bytes;
}

TSSymbol
moonbit_ts_node_grammar_symbol(MoonBitTSNode *self) {
  TSSymbol symbol = ts_node_grammar_symbol(self->node);
  moonbit_decref(self);
  return symbol;
}

uint32_t
moonbit_ts_node_start_byte(MoonBitTSNode *self) {
  uint32_t byte = ts_node_start_byte(self->node);
  moonbit_decref(self);
  return byte;
}

TSPoint *
moonbit_ts_node_start_point(MoonBitTSNode *self) {
  TSPoint *point = (TSPoint *)moonbit_make_int32_array(
    sizeof(struct TSPoint) / sizeof(int32_t), 0
  );
  *point = ts_node_start_point(self->node);
  moonbit_decref(self);
  return point;
}

uint32_t
moonbit_ts_node_end_byte(MoonBitTSNode *self) {
  uint32_t byte = ts_node_end_byte(self->node);
  moonbit_decref(self);
  return byte;
}

TSPoint *
moonbit_ts_node_end_point(MoonBitTSNode *self) {
  TSPoint *point = (TSPoint *)moonbit_make_int32_array(
    sizeof(struct TSPoint) / sizeof(int32_t), 0
  );
  *point = ts_node_end_point(self->node);
  moonbit_decref(self);
  return point;
}

moonbit_bytes_t
moonbit_ts_node_string(MoonBitTSNode *self) {
  moonbit_ts_trace("self = %p\n", self);
  moonbit_ts_trace("self->node.id = %p\n", self->node.id);
  char *string = ts_node_string(self->node);
  moonbit_decref(self);
  size_t length = strlen(string);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, string, length);
  free(string);
  return bytes;
}

bool
moonbit_ts_node_is_null(MoonBitTSNode *self) {
  bool is_null = ts_node_is_null(self->node);
  moonbit_decref(self);
  return is_null;
}

bool
moonbit_ts_node_is_named(MoonBitTSNode *self) {
  bool is_named = ts_node_is_named(self->node);
  moonbit_decref(self);
  return is_named;
}

bool
moonbit_ts_node_is_missing(MoonBitTSNode *self) {
  bool is_missing = ts_node_is_missing(self->node);
  moonbit_decref(self);
  return is_missing;
}

bool
moonbit_ts_node_is_extra(MoonBitTSNode *self) {
  bool is_extra = ts_node_is_extra(self->node);
  moonbit_decref(self);
  return is_extra;
}

bool
moonbit_ts_node_has_changes(MoonBitTSNode *self) {
  bool has_changes = ts_node_has_changes(self->node);
  moonbit_decref(self);
  return has_changes;
}

bool
moonbit_ts_node_has_error(MoonBitTSNode *self) {
  bool has_error = ts_node_has_error(self->node);
  moonbit_decref(self);
  return has_error;
}

bool
moonbit_ts_node_is_error(MoonBitTSNode *self) {
  bool is_error = ts_node_is_error(self->node);
  moonbit_decref(self);
  return is_error;
}

TSStateId
moonbit_ts_node_parse_state(MoonBitTSNode *self) {
  TSStateId state = ts_node_parse_state(self->node);
  moonbit_decref(self);
  return state;
}

TSStateId
moonbit_ts_node_next_parse_state(MoonBitTSNode *self) {
  TSStateId state = ts_node_next_parse_state(self->node);
  moonbit_decref(self);
  return state;
}

MoonBitTSNode *
moonbit_ts_node_parent(MoonBitTSNode *self) {
  TSNode node = ts_node_parent(self->node);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_child_with_descendant(
  MoonBitTSNode *self,
  MoonBitTSNode *descendant
) {
  TSNode node = ts_node_child_with_descendant(self->node, descendant->node);
  moonbit_decref(descendant);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_child(MoonBitTSNode *self, uint32_t child_index) {
  TSNode node = ts_node_child(self->node, child_index);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

const char *
moonbit_ts_node_field_name_for_child(
  MoonBitTSNode *self,
  uint32_t child_index
) {
  const char *name = ts_node_field_name_for_child(self->node, child_index);
  moonbit_decref(self);
  return name;
}

const char *
moonbit_ts_node_field_name_for_named_child(
  MoonBitTSNode *self,
  uint32_t named_child_index
) {
  const char *name =
    ts_node_field_name_for_named_child(self->node, named_child_index);
  moonbit_decref(self);
  return name;
}

uint32_t
moonbit_ts_node_child_count(MoonBitTSNode *self) {
  uint32_t count = ts_node_child_count(self->node);
  moonbit_decref(self);
  return count;
}

MoonBitTSNode *
moonbit_ts_node_named_child(MoonBitTSNode *self, uint32_t child_index) {
  TSNode node = ts_node_named_child(self->node, child_index);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

uint32_t
moonbit_ts_node_named_child_count(MoonBitTSNode *self) {
  uint32_t count = ts_node_named_child_count(self->node);
  moonbit_decref(self);
  return count;
}

MoonBitTSNode *
moonbit_ts_node_child_by_field_name(MoonBitTSNode *self, moonbit_bytes_t name) {
  uint32_t length = Moonbit_array_length(name);
  TSNode node =
    ts_node_child_by_field_name(self->node, (const char *)name, length);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  moonbit_decref(name);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_child_by_field_id(MoonBitTSNode *self, TSFieldId field_id) {
  TSNode node = ts_node_child_by_field_id(self->node, field_id);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_next_sibling(MoonBitTSNode *self) {
  TSNode node = ts_node_next_sibling(self->node);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_prev_sibling(MoonBitTSNode *self) {
  TSNode node = ts_node_prev_sibling(self->node);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_next_named_sibling(MoonBitTSNode *self) {
  TSNode node = ts_node_next_named_sibling(self->node);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_prev_named_sibling(MoonBitTSNode *self) {
  TSNode node = ts_node_prev_named_sibling(self->node);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_first_child_for_byte(MoonBitTSNode *self, uint32_t byte) {
  TSNode node = ts_node_first_child_for_byte(self->node, byte);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_first_named_child_for_byte(MoonBitTSNode *self, uint32_t byte) {
  TSNode node = ts_node_first_named_child_for_byte(self->node, byte);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

uint32_t
moonbit_ts_node_descendant_count(MoonBitTSNode *self) {
  uint32_t count = ts_node_descendant_count(self->node);
  moonbit_decref(self);
  return count;
}

MoonBitTSNode *
moonbit_ts_node_descendant_for_byte_range(
  MoonBitTSNode *self,
  uint32_t start,
  uint32_t end
) {
  TSNode node = ts_node_descendant_for_byte_range(self->node, start, end);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_descendant_for_point_range(
  MoonBitTSNode *self,
  TSPoint *start,
  TSPoint *end
) {
  TSNode node = ts_node_descendant_for_point_range(self->node, *start, *end);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  moonbit_decref(start);
  moonbit_decref(end);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_named_descendant_for_byte_range(
  MoonBitTSNode *self,
  uint32_t start,
  uint32_t end
) {
  TSNode node = ts_node_named_descendant_for_byte_range(self->node, start, end);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  return moonbit_ts_node_new(node, tree);
}

MoonBitTSNode *
moonbit_ts_node_named_descendant_for_point_range(
  MoonBitTSNode *self,
  TSPoint *start,
  TSPoint *end
) {
  TSNode node =
    ts_node_named_descendant_for_point_range(self->node, *start, *end);
  MoonBitTSTree *tree = moonbit_ts_node_tree(self);
  moonbit_decref(start);
  moonbit_decref(end);
  return moonbit_ts_node_new(node, tree);
}

void
moonbit_ts_node_edit(MoonBitTSNode *self, TSInputEdit *edit) {
  ts_node_edit(&self->node, edit);
  moonbit_decref(self);
  moonbit_decref(edit);
}

bool
moonbit_ts_node_eq(MoonBitTSNode *self, MoonBitTSNode *other) {
  bool eq = ts_node_eq(self->node, other->node);
  moonbit_decref(self);
  moonbit_decref(other);
  return eq;
}

typedef struct MoonBitTSTreeCursor {
  TSTreeCursor cursor;
  MoonBitTSTree *tree;
} MoonBitTSTreeCursor;

static inline void
moonbit_ts_tree_cursor_delete(void *object) {
  MoonBitTSTreeCursor *cursor = (MoonBitTSTreeCursor *)object;
  ts_tree_cursor_delete(&cursor->cursor);
  moonbit_decref(cursor->tree);
}

MoonBitTSTreeCursor *
moonbit_ts_tree_cursor_new(MoonBitTSNode *node) {
  MoonBitTSTreeCursor *cursor =
    (MoonBitTSTreeCursor *)moonbit_make_external_object(
      moonbit_ts_tree_cursor_delete, sizeof(MoonBitTSTreeCursor)
    );
  cursor->cursor = ts_tree_cursor_new(node->node);
  cursor->tree = moonbit_ts_node_tree(node);
  return cursor;
}

MoonBitTSTree *
moonbit_ts_tree_cursor_tree(MoonBitTSTreeCursor *self) {
  MoonBitTSTree *tree = self->tree;
  moonbit_incref(tree);
  moonbit_decref(self);
  return tree;
}

void
moonbit_ts_tree_cursor_reset(MoonBitTSTreeCursor *self, MoonBitTSNode *node) {
  ts_tree_cursor_reset(&self->cursor, node->node);
  moonbit_decref(node);
  moonbit_decref(self);
}

void
moonbit_ts_tree_cursor_reset_to(
  MoonBitTSTreeCursor *dst,
  MoonBitTSTreeCursor *src
) {
  ts_tree_cursor_reset_to(&dst->cursor, &src->cursor);
  moonbit_decref(src);
  moonbit_decref(dst);
}

MoonBitTSNode *
moonbit_ts_tree_cursor_current_node(MoonBitTSTreeCursor *self) {
  TSNode node = ts_tree_cursor_current_node(&self->cursor);
  MoonBitTSTree *tree = moonbit_ts_tree_cursor_tree(self);
  return moonbit_ts_node_new(node, tree);
}

const char *
moonbit_ts_tree_cursor_current_field_name(MoonBitTSTreeCursor *self) {
  const char *name = ts_tree_cursor_current_field_name(&self->cursor);
  moonbit_decref(self);
  return name;
}

TSFieldId
moonbit_ts_tree_cursor_current_field_id(MoonBitTSTreeCursor *self) {
  TSFieldId id = ts_tree_cursor_current_field_id(&self->cursor);
  moonbit_decref(self);
  return id;
}

bool
moonbit_ts_tree_cursor_goto_parent(MoonBitTSTreeCursor *self) {
  bool result = ts_tree_cursor_goto_parent(&self->cursor);
  moonbit_decref(self);
  return result;
}

bool
moonbit_ts_tree_cursor_goto_next_sibling(MoonBitTSTreeCursor *self) {
  bool result = ts_tree_cursor_goto_next_sibling(&self->cursor);
  moonbit_decref(self);
  return result;
}

bool
moonbit_ts_tree_cursor_goto_first_child(MoonBitTSTreeCursor *self) {
  bool result = ts_tree_cursor_goto_first_child(&self->cursor);
  moonbit_decref(self);
  return result;
}

bool
moonbit_ts_tree_cursor_goto_last_child(MoonBitTSTreeCursor *self) {
  bool result = ts_tree_cursor_goto_last_child(&self->cursor);
  moonbit_decref(self);
  return result;
}

void
moonbit_ts_tree_cursor_goto_descendant(
  MoonBitTSTreeCursor *self,
  uint32_t goal_descendant_index
) {
  ts_tree_cursor_goto_descendant(&self->cursor, goal_descendant_index);
  moonbit_decref(self);
}

uint32_t
moonbit_ts_tree_cursor_current_descendant_index(MoonBitTSTreeCursor *self) {
  uint32_t index = ts_tree_cursor_current_descendant_index(&self->cursor);
  moonbit_decref(self);
  return index;
}

uint32_t
moonbit_ts_tree_cursor_current_depth(MoonBitTSTreeCursor *self) {
  uint32_t depth = ts_tree_cursor_current_depth(&self->cursor);
  moonbit_decref(self);
  return depth;
}

int64_t
moonbit_ts_tree_cursor_goto_first_child_for_byte(
  MoonBitTSTreeCursor *self,
  uint32_t goal_byte
) {
  int64_t result =
    ts_tree_cursor_goto_first_child_for_byte(&self->cursor, goal_byte);
  moonbit_decref(self);
  return result;
}

int64_t
moonbit_ts_tree_cursor_goto_first_child_for_point(
  MoonBitTSTreeCursor *self,
  TSPoint *goal_point
) {
  int64_t result =
    ts_tree_cursor_goto_first_child_for_point(&self->cursor, *goal_point);
  moonbit_decref(self);
  moonbit_decref(goal_point);
  return result;
}

MoonBitTSTreeCursor *
moonbit_ts_tree_cursor_copy(MoonBitTSTreeCursor *self) {
  MoonBitTSTreeCursor *copy =
    (MoonBitTSTreeCursor *)moonbit_make_external_object(
      moonbit_ts_tree_cursor_delete, sizeof(MoonBitTSTreeCursor)
    );
  copy->cursor = ts_tree_cursor_copy(&self->cursor);
  copy->tree = moonbit_ts_tree_cursor_tree(self);
  return copy;
}

typedef struct MoonBitTSQuery {
  TSQuery *query;
} MoonBitTSQuery;

static inline void
moonbit_ts_query_delete(void *object) {
  MoonBitTSQuery *self = object;
  moonbit_ts_trace("self = %p\n", self);
  moonbit_ts_trace("self->query = %p\n", self->query);
  ts_query_delete(self->query);
}

MoonBitTSQuery *
moonbit_ts_query_new(
  const TSLanguage *language,
  moonbit_bytes_t source,
  uint32_t *error
) {
  uint32_t length = Moonbit_array_length(source);
  MoonBitTSQuery *query = moonbit_make_external_object(
    moonbit_ts_query_delete, sizeof(MoonBitTSQuery)
  );
  moonbit_ts_trace("query = %p\n", query);
  query->query =
    ts_query_new(language, (const char *)source, length, &error[0], &error[1]);
  moonbit_ts_trace("query->query = %p\n", query->query);
  moonbit_decref(source);
  moonbit_decref(error);
  return query;
}

uint32_t
moonbit_ts_query_pattern_count(MoonBitTSQuery *self) {
  uint32_t count = ts_query_pattern_count(self->query);
  moonbit_decref(self);
  return count;
}

uint32_t
moonbit_ts_query_capture_count(MoonBitTSQuery *self) {
  uint32_t count = ts_query_capture_count(self->query);
  moonbit_decref(self);
  return count;
}

uint32_t
moonbit_ts_query_string_count(MoonBitTSQuery *self) {
  uint32_t count = ts_query_string_count(self->query);
  moonbit_decref(self);
  return count;
}

uint32_t
moonbit_ts_query_start_byte_for_pattern(
  MoonBitTSQuery *self,
  uint32_t pattern_index
) {
  uint32_t start_byte =
    ts_query_start_byte_for_pattern(self->query, pattern_index);
  moonbit_decref(self);
  return start_byte;
}

uint32_t
moonbit_ts_query_end_byte_for_pattern(
  MoonBitTSQuery *self,
  uint32_t pattern_index
) {
  uint32_t end_byte = ts_query_end_byte_for_pattern(self->query, pattern_index);
  moonbit_decref(self);
  return end_byte;
}

static_assert_type_equal(TSQueryPredicateStepType, uint32_t);

uint32_t *
moonbit_ts_query_predicates_for_pattern(
  MoonBitTSQuery *self,
  uint32_t pattern_index
) {
  uint32_t step_count = 0;
  const TSQueryPredicateStep *predicates =
    ts_query_predicates_for_pattern(self->query, pattern_index, &step_count);
  moonbit_decref(self);
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
moonbit_ts_query_is_pattern_rooted(
  MoonBitTSQuery *self,
  uint32_t pattern_index
) {
  bool result = ts_query_is_pattern_rooted(self->query, pattern_index);
  moonbit_decref(self);
  return result;
}

bool
moonbit_ts_query_is_pattern_non_local(
  MoonBitTSQuery *self,
  uint32_t pattern_index
) {
  bool result = ts_query_is_pattern_non_local(self->query, pattern_index);
  moonbit_decref(self);
  return result;
}

bool
moonbit_ts_query_is_pattern_guaranteed_at_step(
  MoonBitTSQuery *self,
  uint32_t byte_offset
) {
  bool result =
    ts_query_is_pattern_guaranteed_at_step(self->query, byte_offset);
  moonbit_decref(self);
  return result;
}

moonbit_bytes_t
moonbit_ts_query_capture_name_for_id(MoonBitTSQuery *self, uint32_t index) {
  uint32_t length;
  const char *name = ts_query_capture_name_for_id(self->query, index, &length);
  moonbit_decref(self);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, name, length);
  return bytes;
}

static_assert_type_equal(TSQuantifier, uint32_t);

TSQuantifier
moonbit_ts_query_capture_quantifier_for_id(
  MoonBitTSQuery *self,
  uint32_t pattern_index,
  uint32_t capture_index
) {
  TSQuantifier quantifier = ts_query_capture_quantifier_for_id(
    self->query, pattern_index, capture_index
  );
  moonbit_decref(self);
  return quantifier;
}

moonbit_bytes_t
moonbit_ts_query_string_value_for_id(MoonBitTSQuery *self, uint32_t index) {
  uint32_t length;
  const char *value = ts_query_string_value_for_id(self->query, index, &length);
  moonbit_decref(self);
  moonbit_bytes_t bytes = moonbit_make_bytes_sz(length, 0);
  memcpy(bytes, value, length);
  return bytes;
}

void
moonbit_ts_query_disable_capture(MoonBitTSQuery *self, moonbit_bytes_t name) {
  ts_query_disable_capture(
    self->query, (const char *)name, Moonbit_array_length(name)
  );
  moonbit_decref(self);
  moonbit_decref(name);
}

void
moonbit_ts_query_disable_pattern(MoonBitTSQuery *self, uint32_t pattern_index) {
  ts_query_disable_pattern(self->query, pattern_index);
  moonbit_decref(self);
}

typedef struct MoonBitTSQueryCursor {
  TSQueryCursor *cursor;
  MoonBitTSQuery *query;
  MoonBitTSTree *tree;
} MoonBitTSQueryCursor;

static inline void
moonbit_ts_query_cursor_delete(void *object) {
  MoonBitTSQueryCursor *self = (MoonBitTSQueryCursor *)object;
  moonbit_ts_trace("self = %p\n", self);
  moonbit_ts_trace("self->cursor = %p\n", self->cursor);
  ts_query_cursor_delete(self->cursor);
  if (self->query) {
    moonbit_decref(self->query);
  }
  if (self->tree) {
    moonbit_decref(self->tree);
  }
}

MoonBitTSQueryCursor *
moonbit_ts_query_cursor_new(void) {
  MoonBitTSQueryCursor *cursor = moonbit_make_external_object(
    moonbit_ts_query_cursor_delete, sizeof(MoonBitTSQueryCursor)
  );
  moonbit_ts_trace("cursor = %p\n", cursor);
  cursor->cursor = ts_query_cursor_new();
  moonbit_ts_trace("cursor->cursor = %p\n", cursor->cursor);
  cursor->query = NULL;
  cursor->tree = NULL;
  return cursor;
}

static inline void
moonbit_ts_query_cursor_set_query(
  MoonBitTSQueryCursor *self,
  MoonBitTSQuery *query
) {
  if (self->query) {
    moonbit_decref(self->query);
  }
  self->query = query;
}

static inline void
moonbit_ts_query_cursor_set_tree(
  MoonBitTSQueryCursor *self,
  MoonBitTSTree *tree
) {
  if (self->tree) {
    moonbit_decref(self->tree);
  }
  self->tree = tree;
}

static inline MoonBitTSTree *
moonbit_ts_query_cursor_tree(MoonBitTSQueryCursor *self) {
  MoonBitTSTree *tree = self->tree;
  if (self->tree) {
    moonbit_incref(self->tree);
  }
  moonbit_decref(self);
  return tree;
}

void
moonbit_ts_query_cursor_exec(
  MoonBitTSQueryCursor *self,
  MoonBitTSQuery *query,
  MoonBitTSNode *node
) {
  ts_query_cursor_exec(self->cursor, query->query, node->node);
  moonbit_ts_query_cursor_set_query(self, query);
  moonbit_ts_query_cursor_set_tree(self, moonbit_ts_node_tree(node));
  moonbit_ts_trace("self = %p\n", self);
  moonbit_ts_trace("self->cursor = %p\n", self->cursor);
  moonbit_ts_trace("self->tree = %p\n", self->tree);
  moonbit_decref(self);
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
  MoonBitTSQueryCursor *self,
  MoonBitTSQuery *query,
  MoonBitTSNode *node,
  MoonBitTSQueryCursorProgressCallback *callback
) {
  TSQueryCursorOptions options = {
    .payload = callback,
    .progress_callback = moonbit_ts_query_cursor_progress_callback
  };
  moonbit_ts_query_cursor_set_tree(self, moonbit_ts_node_tree(node));
  ts_query_cursor_exec_with_options(
    self->cursor, query->query, node->node, &options
  );
  moonbit_decref(self);
  moonbit_decref(query);
}

bool
moonbit_ts_query_cursor_did_exceed_match_limit(MoonBitTSQueryCursor *self) {
  bool result = ts_query_cursor_did_exceed_match_limit(self->cursor);
  moonbit_decref(self);
  return result;
}

uint32_t
moonbit_ts_query_cursor_match_limit(MoonBitTSQueryCursor *self) {
  bool result = ts_query_cursor_match_limit(self->cursor);
  moonbit_decref(self);
  return result;
}

void
moonbit_ts_query_cursor_set_match_limit(
  MoonBitTSQueryCursor *self,
  uint32_t limit
) {
  ts_query_cursor_set_match_limit(self->cursor, limit);
  moonbit_decref(self);
}

void
moonbit_ts_query_cursor_set_byte_range(
  MoonBitTSQueryCursor *self,
  uint32_t start_byte,
  uint32_t end_byte
) {
  ts_query_cursor_set_byte_range(self->cursor, start_byte, end_byte);
  moonbit_decref(self);
}

void
moonbit_ts_query_cursor_set_point_range(
  MoonBitTSQueryCursor *self,
  TSPoint *start_point,
  TSPoint *end_point
) {
  ts_query_cursor_set_point_range(self->cursor, *start_point, *end_point);
  moonbit_decref(self);
  moonbit_decref(start_point);
  moonbit_decref(end_point);
}

typedef struct MoonBitTSQueryMatch {
  TSQueryMatch match;
  MoonBitTSQueryCursor *cursor;
} MoonBitTSQueryMatch;

static inline void
moonbit_ts_query_match_delete(void *object) {
  MoonBitTSQueryMatch *self = (MoonBitTSQueryMatch *)object;
  moonbit_ts_trace("self = %p\n", self);
  moonbit_ts_trace("self->cursor = %p\n", self->cursor);
  if (self->cursor) {
    moonbit_decref(self->cursor);
  }
}

static inline MoonBitTSQueryCursor *
moonbit_ts_query_match_cursor(MoonBitTSQueryMatch *self) {
  MoonBitTSQueryCursor *cursor = self->cursor;
  if (self->cursor) {
    moonbit_incref(self->cursor);
  }
  moonbit_decref(self);
  return cursor;
}

static inline MoonBitTSTree *
moonbit_ts_query_match_tree(MoonBitTSQueryMatch *self) {
  return moonbit_ts_query_cursor_tree(moonbit_ts_query_match_cursor(self));
}

MoonBitTSQueryMatch *
moonbit_ts_query_cursor_next_match(MoonBitTSQueryCursor *self) {
  moonbit_ts_trace("self = %p\n", self);
  moonbit_ts_trace("self->cursor = %p\n", self->cursor);
  moonbit_ts_trace("self->tree = %p\n", self->tree);
  MoonBitTSQueryMatch *match = moonbit_make_external_object(
    moonbit_ts_query_match_delete, sizeof(MoonBitTSQueryMatch)
  );
  bool has_match = ts_query_cursor_next_match(self->cursor, &match->match);
  moonbit_ts_trace("has_match = %d\n", has_match);
  if (has_match) {
    match->cursor = self;
    return match;
  } else {
    match->cursor = NULL;
    moonbit_decref(match);
    moonbit_decref(self);
    return NULL;
  }
}

void
moonbit_ts_query_cursor_remove_match(
  MoonBitTSQueryCursor *self,
  uint32_t match_id
) {
  ts_query_cursor_remove_match(self->cursor, match_id);
  moonbit_decref(self);
}

MoonBitTSQueryMatch *
moonbit_ts_query_cursor_next_capture(
  MoonBitTSQueryCursor *self,
  uint32_t *match_id
) {
  MoonBitTSQueryMatch *match = moonbit_make_external_object(
    moonbit_ts_query_match_delete, sizeof(MoonBitTSQueryMatch)
  );
  bool has_match =
    ts_query_cursor_next_capture(self->cursor, &match->match, match_id);
  moonbit_decref(match_id);
  if (has_match) {
    match->cursor = self;
    return match;
  } else {
    match->cursor = NULL;
    moonbit_decref(match);
    moonbit_decref(self);
    return NULL;
  }
}

void
moonbit_ts_query_cursor_set_max_start_depth(
  MoonBitTSQueryCursor *self,
  uint32_t max_start_depth
) {
  ts_query_cursor_set_max_start_depth(self->cursor, max_start_depth);
  moonbit_decref(self);
}

uint32_t
moonbit_ts_query_match_id(MoonBitTSQueryMatch *self) {
  uint32_t id = self->match.id;
  moonbit_decref(self);
  return id;
}

uint16_t
moonbit_ts_query_match_pattern_index(MoonBitTSQueryMatch *self) {
  uint16_t index = self->match.pattern_index;
  moonbit_decref(self);
  return index;
}

uint16_t
moonbit_ts_query_match_capture_count(MoonBitTSQueryMatch *self) {
  uint16_t count = self->match.capture_count;
  moonbit_decref(self);
  return count;
}

MoonBitTSNode *
moonbit_ts_query_match_captures_get_node(
  MoonBitTSQueryMatch *self,
  uint32_t index
) {
  TSNode node = self->match.captures[index].node;
  moonbit_ts_trace("node.id = %p\n", node.id);
  MoonBitTSTree *tree = moonbit_ts_query_match_tree(self);
  return moonbit_ts_node_new(node, tree);
}

uint32_t
moonbit_ts_query_match_captures_get_index(
  MoonBitTSQueryMatch *self,
  uint32_t index
) {
  uint32_t i = self->match.captures[index].index;
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

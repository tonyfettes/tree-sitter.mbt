#include <dlfcn.h>
#include <moonbit.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <tree_sitter/api.h>

void *
moonbit_c_null() {
  return NULL;
}

bool
moonbit_c_is_null(void *ptr) {
  return ptr == NULL;
}

TSLanguage *
moonbit_ts_language_load(moonbit_bytes_t pathname, moonbit_bytes_t symbol) {
  void *handle = dlopen((const char *)pathname, RTLD_NOW);
  if (!handle) {
    moonbit_decref(pathname);
    moonbit_decref(symbol);
    return NULL;
  }
  TSLanguage *(*load)(void) = dlsym(handle, (const char *)symbol);
  moonbit_decref(pathname);
  moonbit_decref(symbol);
  if (!load) {
    dlclose(handle);
    return NULL;
  }
  return load();
}

moonbit_bytes_t
moonbit_ts_field_name_for_id(TSLanguage *self, TSFieldId id) {
  const char *name = ts_language_field_name_for_id(self, id);
  size_t length = strlen(name);
  moonbit_bytes_t bytes = moonbit_make_bytes(length, 0);
  memcpy(bytes, name, length);
  return bytes;
}

TSFieldId
moonbit_ts_language_field_id_for_name(TSLanguage *self, moonbit_bytes_t name) {
  uint32_t length = Moonbit_array_length(name);
  TSFieldId id =
    ts_language_field_id_for_name(self, (const char *)name, length);
  moonbit_decref(name);
  return id;
}

TSParser *
moonbit_ts_parser_new() {
  return ts_parser_new();
}

void
moonbit_ts_parser_delete(TSParser *parser) {
  ts_parser_delete(parser);
}

bool
moonbit_ts_parser_set_language(TSParser *parser, TSLanguage *language) {
  return ts_parser_set_language(parser, language);
}

TSTree *
moonbit_ts_parser_parse_string(
  TSParser *parser,
  TSTree *old_tree,
  moonbit_bytes_t bytes
) {
  uint32_t length = Moonbit_array_length(bytes);
  TSTree *tree =
    ts_parser_parse_string(parser, old_tree, (const char *)bytes, length);
  moonbit_decref(bytes);
  return tree;
}

void
moonbit_ts_parser_set_included_ranges(TSParser *parser, TSRange *ranges) {
  size_t length = Moonbit_array_length(ranges);
  ts_parser_set_included_ranges(
    parser, ranges, length * sizeof(uint32_t) / sizeof(TSRange)
  );
}

void
moonbit_ts_tree_edit(TSTree *tree, TSInputEdit *edit) {
  ts_tree_edit(tree, edit);
  moonbit_decref(edit);
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

TSTree *
moonbit_ts_tree_copy(TSTree *self) {
  return ts_tree_copy(self);
}

TSNode *
moonbit_ts_node_child(TSNode *self, uint32_t child_index) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_child(*self, child_index);
  moonbit_decref(self);
  return node;
}

TSNode *
moonbit_ts_node_named_child(TSNode *self, uint32_t child_index) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_named_child(*self, child_index);
  moonbit_decref(self);
  return node;
}

uint32_t
moonbit_ts_node_child_count(TSNode *self) {
  int count = ts_node_child_count(*self);
  moonbit_decref(self);
  return count;
}

uint32_t
moonbit_ts_node_named_child_count(TSNode *self) {
  int count = ts_node_named_child_count(*self);
  moonbit_decref(self);
  return count;
}

moonbit_bytes_t
moonbit_ts_node_string(TSNode *self) {
  char *string = ts_node_string(*self);
  moonbit_decref(self);
  size_t length = strlen(string);
  moonbit_bytes_t bytes = moonbit_make_bytes(length, 0);
  memcpy(bytes, string, length);
  free(string);
  return bytes;
}

moonbit_bytes_t
moonbit_ts_node_type(TSNode *self) {
  const char *type = ts_node_type(*self);
  moonbit_decref(self);
  moonbit_bytes_t bytes = moonbit_make_bytes(strlen(type), 0);
  memcpy(bytes, type, strlen(type));
  return bytes;
}

uint32_t
moonbit_ts_node_start_byte(TSNode *self) {
  uint32_t byte = ts_node_start_byte(*self);
  moonbit_decref(self);
  return byte;
}

uint32_t
moonbit_ts_node_end_byte(TSNode *self) {
  uint32_t byte = ts_node_end_byte(*self);
  moonbit_decref(self);
  return byte;
}

TSPoint *
moonbit_ts_node_start_point(TSNode *self) {
  TSPoint *point = (TSPoint *)moonbit_malloc(sizeof(struct TSPoint));
  *point = ts_node_start_point(*self);
  moonbit_decref(self);
  return point;
}

TSPoint *
moonbit_ts_node_end_point(TSNode *self) {
  TSPoint *point = (TSPoint *)moonbit_malloc(sizeof(struct TSPoint));
  *point = ts_node_end_point(*self);
  moonbit_decref(self);
  return point;
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

TSNode *
moonbit_ts_node_parent(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_parent(*self);
  moonbit_decref(self);
  return node;
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

void
moonbit_ts_node_edit(TSNode *self, TSInputEdit *edit) {
  ts_node_edit(self, edit);
  moonbit_decref(self);
  moonbit_decref(edit);
}

TSTreeCursor *
moonbit_ts_tree_cursor_new(TSNode *node) {
  TSTreeCursor *cursor =
    (TSTreeCursor *)moonbit_malloc(sizeof(struct TSTreeCursor));
  *cursor = ts_tree_cursor_new(*node);
  moonbit_decref(node);
  return cursor;
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

TSNode *
moonbit_ts_tree_cursor_current_node(TSTreeCursor *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_tree_cursor_current_node(self);
  moonbit_decref(self);
  return node;
}

moonbit_bytes_t
moonbit_ts_tree_cursor_current_field_name(TSTreeCursor *self) {
  const char *name = ts_tree_cursor_current_field_name(self);
  size_t length = strlen(name);
  moonbit_bytes_t bytes = moonbit_make_bytes(length, 0);
  memcpy(bytes, name, length);
  moonbit_decref(self);
  return bytes;
}

TSFieldId
moonbit_ts_tree_cursor_current_field_id(TSTreeCursor *self) {
  TSFieldId id = ts_tree_cursor_current_field_id(self);
  moonbit_decref(self);
  return id;
}

TSQuery *
moonbit_ts_query_new(
  TSLanguage *language,
  moonbit_bytes_t source,
  uint32_t *error
) {
  uint32_t length = Moonbit_array_length(source);
  TSQuery *query =
    ts_query_new(language, (const char *)source, length, error, error + 1);
  moonbit_decref(source);
  return query;
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

TSQueryMatch *
moonbit_ts_query_cursor_next_match(TSQueryCursor *self) {
  TSQueryMatch *match =
    (TSQueryMatch *)moonbit_malloc(sizeof(struct TSQueryMatch));
  bool has_match = !ts_query_cursor_next_match(self, match);
  moonbit_decref(self);
  if (has_match) {
    return match;
  } else {
    return NULL;
  }
}

void
moonbit_ts_query_cursor_delete(TSQueryCursor *self) {
  ts_query_cursor_delete(self);
}

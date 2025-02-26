#include <moonbit.h>
#include <stdbool.h>
#include <string.h>
#include <tree_sitter/api.h>

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
  return ts_parser_parse_string(parser, old_tree, (const char *)bytes, length);
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
moonbit_ts_node_named_child(TSNode *self, uint32_t child_index) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_named_child(*self, child_index);
  moonbit_decref(self);
  return node;
}

moonbit_bytes_t
moonbit_ts_node_type(TSNode *self) {
  const char *type = ts_node_type(*self);
  moonbit_decref(self);
  moonbit_bytes_t bytes = moonbit_make_bytes(strlen(type), 0);
  memcpy(bytes, type, strlen(type));
  return bytes;
}

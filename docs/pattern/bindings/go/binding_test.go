package tree_sitter_pattern_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_pattern "github.com/tonyfettes/tree-sitter.mbt/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_pattern.Language())
	if language == nil {
		t.Errorf("Error loading Pattern grammar")
	}
}

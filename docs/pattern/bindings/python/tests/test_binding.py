from unittest import TestCase

import tree_sitter
import tree_sitter_pattern


class TestLanguage(TestCase):
    def test_can_load_grammar(self):
        try:
            tree_sitter.Language(tree_sitter_pattern.language())
        except Exception:
            self.fail("Error loading Pattern grammar")

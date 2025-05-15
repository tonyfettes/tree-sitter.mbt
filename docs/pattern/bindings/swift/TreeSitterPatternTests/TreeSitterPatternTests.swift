import XCTest
import SwiftTreeSitter
import TreeSitterPattern

final class TreeSitterPatternTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_pattern())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Pattern grammar")
    }
}

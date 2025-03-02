# `tonyfettes/tree_sitter_language`

The tree-sitter language type used by generated tree-sitter binding.

> [!NOTE] This package is not meant to be used directly. It is used by the
> MoonBit bindings of tree-sitter grammars to provide a common language type so
> that they can be used with `tonyfettes/tree_sitter`.

## Usage (for grammar developers)

1. Add this module as a dependency to the MoonBit binding:

   ```bash
   moon update # Update the mooncakes.io package index
   moon add tonyfettes/tree_sitter_language
   ```

2. Import the `tonyfettes/tree_sitter_language` package in `moon.pkg.json`:

   ```json
   {
     "import": [
       "tonyfettes/tree_sitter_language"
     ]
   }
   ```

3. Make your the entry point of your grammar module return a `@tree_sitter_language.Language`:

   ```moonbit
   ///|
   extern "c" fn language -> @tree_sitter_language.Language = "tree_sitter_xxx"
   ```

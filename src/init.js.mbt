priv type TS

let ts : TS = import_web_tree_sitter()

extern "js" fn import_web_tree_sitter() -> TS =
  #|await new Promise(async (resolve) => {
  #|  const ts = await import('web-tree-sitter');
  #|  await ts.Parser.init();
  #|  resolve(() => ts);
  #|});

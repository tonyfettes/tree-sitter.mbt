///|
test "roundtrip" {
  let sexp =
    #|(a b c d: (f g))
    #|(h (j) (k (l)))
  let sexp = @sexp.parse!(sexp)
  let buffer = StringBuilder::new()
  @sexp.print(sexp, buffer)
  inspect!(buffer, content=
    #|(a
    #| b
    #| c
    #| d: (f
    #|     g))
    #|(h
    #| (j)
    #| (k
    #|  (l)))
  )
}

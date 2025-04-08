///|
test "roundtrip" {
  let sexp =
    #|(a b c d: (f g))
    #|(h (j) (k (l)))
  let sexp = @sexp.parse!(sexp)
  inspect!(
    @sexp.print(sexp),
    content=
      #|(a
      #| b
      #| c
      #| d: (f
      #|     g))
      #|(h
      #| (j)
      #| (k
      #|  (l)))
    ,
  )
}

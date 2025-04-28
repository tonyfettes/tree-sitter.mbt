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

///|
test "brackets" {
  let sexp =
    #|[a b c d: [f g]]
    #|[h [j] [k [l]]]
  let sexp = @sexp.parse!(sexp)
  inspect!(
    @sexp.print(sexp),
    content=
      #|[a
      #| b
      #| c
      #| d: [f
      #|     g]]
      #|[h
      #| [j]
      #| [k
      #|  [l]]]
    ,
  )
}

///|
test "capture" {
  let sexp =
    #|(capture) @a
  let sexp = @sexp.parse!(sexp)
  inspect!(@sexp.print(sexp), content="(capture) @a")
}

///|
test "comment" {
  let sexp =
    #|; comment a
    #|a b c d: (f g) ; comment b
    #|; comment c
    #|(h (j) ; command d
    #|   (k (l)) ; comment e
    #|)
    #|
    #|(a b ; comment
    #|   c ; comment
    #|   d e f)
  let sexp = @sexp.parse!(sexp)
  inspect!(
    @sexp.print(sexp),
    content=
      #|; comment a
      #|a
      #|b
      #|c
      #|d: (f
      #|    g)
      #|; comment b
      #|; comment c
      #|(h
      #| (j)
      #| ; command d
      #| (k
      #|  (l))
      #| ; comment e
      #|)
      #|(a
      #| b
      #| ; comment
      #| c
      #| ; comment
      #| d
      #| e
      #| f)

    ,
  )
}

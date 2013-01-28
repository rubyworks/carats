# String#splice

## About

String#slice is essentially the same as #[]=.
But it acts like #slice! when given a single argument.

    a = "HELLO"
    a.splice(1, "X")
    a                #=> "HXLLO"

    a = "HELLO"
    a.splice(1)    #=> "E"
    a              #=> "HLLO"

Returns the string with changes made or new sub-string. [String]

Note: New implementation can take three arguments for
      begin and end indexes, e.g. `splice(beg, end, sub)`.


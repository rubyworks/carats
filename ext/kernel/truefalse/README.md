# true? & false?

## About

We have `#nil?` which returns `true` only if the receiver is the one and only
`NilClass` instance. Here we simply provide the same for `TrueClass` and `FalseClass`.

    true.true?    #=> true
    false.true?   #=> false
    nil.true?     #=> false
    "foo".true?   #=> false

    true.false?   #=> false
    false.false?  #=> true
    nil.false?    #=> false
    "foo".false?  #=> false


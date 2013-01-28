# Hash#<<

## About

Such a lovely little method, one has to wonder why Ruby doesn't have it.
The simplist and primary usage is to merge a key-value pair into a hash.

    {:a=>1} << [:b, 2]
    => {:a=>1, :b=>2}

It can also take an array of even number of elements of any length.

    {:a=>1} << [:b, 2, :c, 3]
    => {:a=>1, :b=>2, :c=>3}

That's really the heart of the matter. But because it just minor addition
to to the method it can also take another hash, in which case it acts just
like merge.

    {:a=>1} << {:b=>2}
    => {:a=>1, :b=>2}


## Pairs?

If Ruby had built-in support for the concept of a `Pair` and a literal
notation to go with it, we probably would not allow the later two forms 
at all and limit the first form to pairs only. But since we have to use
Arrays to represent the pairs, the later forms are reasonable.


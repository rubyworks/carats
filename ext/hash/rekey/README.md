# Hash#rekey

## Bounty

There is a $10 bounty for finishing this method. Part of the implementation
has already be completed by Calib Clausen.

## About

The `Hash#rekey` method is sorely missing from Ruby. It's purpose it too
convert the keys of hash via a block.

    {'a'=>'X', 'b'=>'Y'}.rekey{ |k| k.to_sym }
    => {:a=>'X', :b=>'Y'}

Since converting keys to symbols is one of the most, if not the most, 
common conversion that is the default if no block is given.

    {'a'=>'X', 'b'=>'Y'}.rekey
    => {:a=>'X', :b=>'Y'}

The block can also take a key-value pair if the value is needed to
determine the key.

    {'a'=>'X', 'b'=>'Y'}.rekey{ |k,v| "#{k}{v}".to_sym }
    => {:aX=>'X', :bY=>'Y'}

Finally the method can take key paramters for specific key conversions.

    {'a'=>'X', 'b'=>'Y'}.rekey('a'=>'q')
    => {'q'=>'X', 'b'=>'Y'}

If both key parameters and a block are given, the key parameters are
applied first, and then the block.


# Kernel#identical?

## About

The `Kernel#equal?` method is a terrible name for that method.
By using it to mean "one and the same", Ruby is forced to use 
more cryptic methods like `#eql?` for more usual meanings.

Worse still for test frameworks that need to define ssertions
for these methods. Consider for instance what `#assert_equal` 
means.

To push back against this we introduce the `#indentical?` method
which does the the same thing a `#equal?`. With any fortune 
one day `#identical?` will completely supplant `#equal?` in
general usage.


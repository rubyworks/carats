# Array#each_value

## About

The `Array#each_value` method is a simply a analog to `Hash#each_value`,
and  does essentially the same thing. Implementation wise it is just
an alias for `Array#each`.

    [:a, :b, :c].each_value do |item|
      p index, item
    end

    :a
    :b
    :c

Its purpose is simply to enhance polymorphism bewtween Array and Hash.


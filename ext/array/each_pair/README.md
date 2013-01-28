# Array#each_pair

## About

The `Array#each_pair` method is a simply a analog to `Hash#each_pair`, and 
does essentially the same thing, but instead of the hash key it iterates
with the array index. 

    [:a, :b, :c].each_pair do |index, item|
      p [index, item]
    end

    [1, :a]
    [2, :b]
    [3, :c]

Its purpose is simply to enhance polymorphism bewtween Array and Hash.


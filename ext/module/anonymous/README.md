# Module#anonymous

## About

Technically one can determine if a module is anonymous, which means it 
is not referenced by any constant, by checking to see if it has a name.
For example `Object` is not anonymous b/c it has a name.

    Object.name  #=> "Object"

But if we create a module via `Module.new` then it would not.

    m = Module.new
    m.name  #=> nil

Such a module is anonymous.

    m.anonymous?  #=> true

In addition, if a module as *no* anonymous instances it is said to 
be permanent.

    m.permanent?  #=> false


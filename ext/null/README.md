# Null

## Bounty!

The NullClass has yet to be fully implemented. There are issues a more 
experienced Ruby C expert needs to work out. 

There is a $20 bounty for this class.

## About

NullClass is just like NilClass with one exception -- missing methods
always return +null+.

Because +null+ evaluates as false, just like +nil+ and +false+, +null+
makes it very convenient to to query method chains that might not exist.

Here is a classic example:

  class Config
    def initialize(data={})
      @data = data
    end

    def method_missing(name)
      value = @data[name] || null
      Hash === value ? Config.new(value) : value
    end
  end

  config = Config.new(:x=>{:a=>'A'})

  config.x.a  #=> 'X'
  config.x.y  #=> null

  if config.x.y.z
    # will not happen, but not an error either
  end

Null is useful when working with nested data, in that it does not require
the data's user to continually check for possible +nil+ values to circumvent
NoMethodErrors.

## Note

Would `NA`, for Non-Applicable, be a better name for this class?

# Is

## Bounty!

There is a $20 Bounty for this feature.

## About

A module method that works like #include and #extend combined. It
includes at the instance level and extends at the class-level.

Here is a testable example:

    module Demonstratable
      def self.y; "y"; end
      def x; "x"; end
    end

    class Example
      is Demonstratable
    end

    Example.y      #=> "y"
    Example.new.x  #=> "x"




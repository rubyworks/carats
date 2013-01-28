# String#indent

## Bounty

There is a $20 bounty for a good implementation of indent and unindent.
A good implmentation should not rely on regular expressions.

## About

String#indent is used to indent a String a given number of spaces.
Optionally a diferrent string can be used for the "indention" besides
a space.

The #indent method is aliased as #tab (as that is the typical modern use
of the tab key these days). And there is a complementary `#unindent` method
(or should it be `#undent`?) along with it's alias `backtab`.

## Implementation

The basic implementation is to iterate over each line of a string and prefix
the tab character the specified number of times. But I came acorss this 
implementation on the Internet that claimed superior design:

  def indent(count, char = ' ')
    gsub(/([^\n]*)(\n|$)/) do |match|
      last_iteration = ($1 == "" && $2 == "")
      line = ""
      line << (char * count) unless last_iteration
      line << $1
      line << $2
      line
    end

But it this really a better implementation for some reason?


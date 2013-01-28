# String#margin

## Bounty

There is a $10 bounty for this method. This is similar to the #indent method,
so if that boubty is completed this method should be a pretty easy derivation.

## About

String#margin preserve relative indention such that the line with the least
amount of white space ends up with the given number of spaces before non-space
characters and all other lines move relative to it.

Because of the nature of this method any leading tab characters (`\t`) must
be converted to spaces. The size of a tab can be set via the `:tab` option.
The default size is 2.


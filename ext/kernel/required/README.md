# Kernel#required?

## About

How can one tell if a feature has already been loaded? Turns out there
is no reasonable way to do so it pure Ruby. This method rememdies that.

    required?('facets')  #=> false
    require 'facets'
    required?('facets')  #=> true


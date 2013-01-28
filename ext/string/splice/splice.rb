require 'facets/string/store'

class String

  # String#slice is essentially the same as #store.
  # But it acts like #slice! when given a single argument.
  #
  # idx - index [Integer]
  # sub - a substitute string (optional) [String]
  #
  # Examples
  #
  #   a = "HELLO"
  #   a.splice(1, "X")
  #   a                #=> "HXLLO"
  #
  #   a = "HELLO"
  #   a.splice(1)    #=> "E"
  #   a              #=> "HLLO"
  #
  # Returns the string with changes made or new sub-string. [String]
  #
  # Note: New implementation can take three arguments for
  #       begin and end indexes, e.g. `splice(beg, end, sub)`.
  #
  # Credit: Trans

  def splice(idx, sub=nil)
    if sub
      store(idx, sub)
    else
      case idx
      when Range
        slice!(idx)
      else
        slice!(idx,1)
      end
    end
  end

end


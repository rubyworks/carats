class String

  # Indent left or right by `n` spaces, or `n` number of `c` string.
  #
  # n - the number of spaces to indent 
  # c - character to use, if other then space
  #
  # Returns a new string with the indention. [String]
  #
  # Author: Gavin Sinclair
  # Author: Trans
  # Author: Tyler Rick

  def indent(n, c=' ')
    if n >= 0
      gsub(/^/, c * n)
    else
      gsub(/^#{Regexp.escape(c)}{0,#{-n}}/, "")
    end
  end

  # Equivalent to String#indent, but modifies the receiver in place.
  # 
  # Returns this string indented. [String]

  def indent!(n, c=' ')
    replace(indent(n,c))
  end

  # Remove excessive indentation. Useful for multi-line strings embeded in
  # already indented code.
  #
  # Examples
  #
  #     <<-END.unindent
  #         ohaie
  #           wurld
  #     END 
  #     #=> "ohaie\n  wurld"
  #
  # Returns a new string with the unindention. [String]
  #
  # Author: Noah Gibbs
  # Author: mynyml

  def unindent(size=nil)
    if size
      indent(-size)
    else
      char = ' '
      self.scan(/^[\ \t]*\S/) do |m|
        if size.nil? || m.size < size
          size = m.size
          char = m[0...-1]
        end
      end
      size -= 1
      indent(-size, char)
    end
  end

  # Equivalent to String#unindent, but modifies the receiver in place.
  #
  # Returns this string unindented. [String]
  #
  # Author: mynyml

  def unindent!
    replace(unindent)
  end

  alias :tab :indent
  alias :tab! :indent!

  alias :backtab :unindent
  alias :backtab! :unindent!

end

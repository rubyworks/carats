

class String

  # Indent left or right by n spaces.
  #
  # CREDIT: Gavin Sinclair, Trans, Tyler Rick

  def tab(n, c=' ')
    if n >= 0
      gsub(/^/, c * n)
    else
      gsub(/^#{Regexp.escape(c)}{0,#{-n}}/, "")
    end
  end

  # Equivalent to String#indent, but modifies the receiver in place.

  def tab!(n, c=' ')
    replace(tab(n,c))
  end

  # Indention that preserves relative tabbing.
  #
  # The first non-empty line ends up with n spaces before nonspace.
  #
  # CREDIT: Gavin Sinclair

  def tabto(n)
    if self =~ /^( *)\S/
      indent(n - $1.length)
    else
      self
    end
  end

  # Equivalent to String#indent, but modifies the receiver in place.

  def tabto!(n)
    replace(tabto(n))
  end

end

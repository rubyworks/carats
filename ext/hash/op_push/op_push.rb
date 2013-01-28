class Hash

  # Can be used like update, or passed a two-element
  # `[key,value]` array.
  #
  # Credit: Trans

  def <<(other)
    if other.respond_to?(:to_ary)
      self.store(*other)
    else
      update(other)
    end
    self
  end

end

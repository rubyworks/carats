module Kernel

  # Does self and other refer to the identical object?
  def identical?(other)
    object_id == other.object_id
  end

end

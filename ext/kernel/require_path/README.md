# Kernel#require_path

## About

How can we know where a feature will be loaded from when it is required? 
Presently Ruby provided no way to know this, even though the functionaliy
to do so is just below the surfarce. The `Kernel#require_path` exposes
it.

    require_path('realms')
    => "/opt/Ruby/1.9.3-p327/lib/ruby/site_ruby/1.9.1/realms.rb"


#include <ruby.h>
#include <st.h>

/*
 *  call-seq:
 *     module.is other_module      -> module
 *
 * A module method that works like #include and #extend combined.
 * It includes at the instance level and extends at the class-level.
 *
 *   module Demonstratable
 *     def self.y; "y"; end
 *     def x; "x"; end
 *   end
 *
 *   class Example
 *     is Demonstratable
 *   end
 *
 *   Example.y      #=> "y"
 *   Example.new.x  #=> "x"
 *
 */

VALUE
rb_module_is(VALUE module){

}

void Init_carats(){
  rb_define_method(rb_cModule, "is", rb_module_is, 0);
}


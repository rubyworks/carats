#include <ruby.h>
#include <st.h>

/*
 *  call-seq:
 *     ary.each_value { |item| block }  -> ary
 *     ary.each_value                   -> Enumerator
 *
 * This method is a simple alias for #each.
 *
 * The method provides polymorphism with Hash#each_value.
 *
 */

void Init_carats(){
  rb_define_alias(rb_cArray, "each_value", "each");
}


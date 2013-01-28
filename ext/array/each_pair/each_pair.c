#include <ruby.h>
#include <st.h>

/*
 *  call-seq:
 *     ary.each_pair { |index, item| block }  -> ary
 *     ary.each_pair                          -> Enumerator
 *
 *  Calls the given block once for each element in +self+, passing that index
 *  and element as a parameter.
 *
 *  An Enumerator is returned if no block is given.
 *
 *  This method provides polymorphism with Hash#each_pair.
 *
 *     a = [ "a", "b", "c" ]
 *     a.each_pair {|i, x| print i, x, " -- " }
 *
 *  produces:
 *
 *     0a -- 1b -- 2c --
 */

VALUE
rb_ary_each_pair(VALUE array)
{
    long i;
    volatile VALUE ary = array;

    RETURN_SIZED_ENUMERATOR(ary, 0, 0, rb_ary_length);
    for (i=0; i<RARRAY_LEN(ary); i++) {
      rb_yield(LONG2NUM(i), RARRAY_PTR(ary)[i]);
    }
    return ary;
}

void Init_carats(){
  rb_define_method(rb_cArray, "each_pair", rb_ary_each_pair, 0);
}


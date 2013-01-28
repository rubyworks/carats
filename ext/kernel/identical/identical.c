#include <ruby.h>
#include <ruby/st.h>

/*
 *  call-seq:
 *     obj.identical?(other)   -> true or false
 *
 *  Identity --- For all objects, <code>identical?</code> returns
 *  <code>true</code> only if +obj+ and +other+ are one and the same object.
 *
 *  The <code>identical?</code> method should never be overridden by subclasses
 *  as it is used to determine object identity (that is, <code>a.identical?(b)</code>
 *  if and only if <code>a</code> is the same object as <code>b</code>):
 *
 *    obj = "a"
 *    other = obj.dup
 *
 *    a == other          #=> true
 *    a.identical? other  #=> false
 *    a.idential? a       #=> true
 *
 */

VALUE
rb_obj_identical(VALUE obj1, VALUE obj2)
{
    if (obj1 == obj2) return Qtrue;
    return Qfalse;
}

void Init_carats(){
  rb_define_method(rb_cObject, "identical?", rb_obj_identical, 0);
}


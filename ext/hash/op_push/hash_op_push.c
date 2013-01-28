#include <ruby.h>
#include <st.h>

/*
 *  call-seq:
 *     hsh << obj            -> hsh
 *
 *  Append---Pushes the given object into this hash. The object
 *  can be another hash or array of pairs. This expression returns
 *  the hash itself, so several appends may be chained together.
 *
 *     { :a=>1 } << [:b, 2] << { :c=>3 }
 *             #=>  { :a=>1, :b=>2, :c=>3 }
 *
 */

VALUE
rb_hsh_push(VALUE hsh, VALUE obj)
{
  if (rb_respond_to(obj, rb_intern("to_hash"))) {
    rb_hash_update(hsh, obj)  /* env_update(hsh, obj) */
  }
  else if (rb_respond_to(obj, rb_intern("to_ary"))) {
    VALUE ary = rb_convert_type(obj, T_ARRAY, "Array", "to_ary");
    long size = RARRAY_LEN(ary);
    if(size & 1) {
      rb_raise(rb_eArgError, "odd number of arguments for Hash");
    } 
    else {
      /* TODO: would it be better to convert the array to a hash then use update? */
      for (i=0; i<size; i+=2) {
        rb_hash_aset(hsh, RARRAY_PTR(ary)[i], RARRAY_PTR(ary)[i + 1]);
      }
    }
  }
  else {
    rb_raise(rb_eArgError, "attempt to merge object other then hash or array");
  }
  return(hsh);
}

void Init_carats(){
  rb_define_method(rb_cHash, "<<", rb_hash_push, 1);
}


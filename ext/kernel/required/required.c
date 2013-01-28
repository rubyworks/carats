#include <ruby.h>
#include <st.h>

/*
 *  call-seq:
 *     required?('carats/required')       -> true/false
 *
 * Returns true or false whether a feature has been required or not. 
 *
 */

VALUE
rb_f_required(VALUE obj, VALUE fname){
  if(rb_provided(RSTRING_PTR(fname))){
    return(Qtrue);
  } else {
    return(Qfalse);
  };
}

void Init_carats(){
  rb_define_global_function("required?", rb_f_required, 1);
}


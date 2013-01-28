#include <ruby.h>
#include <st.h>

/*
 *  call-seq:
 *     require_path('carats/required')    -> string
 *
 * Returns the absolute path a feature. 
 *
 */

VALUE
rb_f_require_path(VALUE obj, VALUE fname){
 	VALUE path;
  found = search_required(fname, &path, rb_safe_level());
  if (found) {
    return(path);  
  } else {
    return(Qnil);
  }
}

void Init_carats(){
  rb_define_global_function("require_path", rb_f_require_path, 1);
}


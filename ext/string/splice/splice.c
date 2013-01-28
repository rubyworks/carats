#include <ruby.h>
#include <st.h>

/*
 *  call-seq:
 *     str.splice(int, rstr)   -> str
 *
 * String#splice is a combinatin of #[] and #[]=. With to
 * or three arguments it acts like #[]=.
 *
 *   a = "HELLO"
 *   a.splice(1, "X")
 *   a                #=> "HXLLO"
 *
 * But it acts like #slice! when given a single argument.
 *
 *   a = "HELLO"
 *   a.splice(1)    #=> "E"
 *   a              #=> "HLLO"
 *
 */

VALUE
rb_str_splice2(int argc, VALUE *argv, VALUE str)
{
  if (argc == 3) {
    rb_str_splice(str, NUM2LONG(argv[0]), NUM2LONG(argv[1]), argv[2]);
    return(str);
  } else if (argc = 2) {
    rb_str_aset(str, argv[0], argv[1]);
    return(str);
  } else if (argc = 1) {
    return rb_str_aref(str, argv[0]);
  } else {
    rb_check_arity(argc, 1, 3);
  } 
}

void Init_carats(){
  rb_define_method(rb_cString, "splice", rb_str_splice2, -3);
}


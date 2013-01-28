#include <ruby.h>
#include <st.h>

void Init_carats(){
    rb_define_method(rb_mKernel, "true?", rb_false, 0);
    rb_define_method(rb_mKernel, "false?", rb_false, 0);

    rb_define_method(rb_cTrueClass, "true?", rb_true, 0);
    rb_define_method(rb_cTrueClass, "false?", rb_false, 0);

    rb_define_method(rb_cFalseClass, "true?", rb_false, 0);
    rb_define_method(rb_cFalseClass, "false?", rb_true, 0);
}


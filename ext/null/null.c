// Include the Ruby headers and goodies
#include <ruby.h>

/*
 * Document-class: NullClass
 *
 *  The class of the singleton object <code>null</code>.
 */

VALUE rb_cNullClass;

void
Init_null() {

    rb_cNullClass = rb_define_class("NullClass", rb_cNilClass);

    SPECIAL_SINGLETON(Qnull, rb_cNullClass);

    static VALUE
    method_missing(int argc, VALUE * argv, VALUE self) {
        return Qnull;
    }

    rb_define_method(rb_cNullClass, "null?", rb_true, 0);
    rb_define_method(rb_cNullClass, "method_missing", method_missing, -1);

    /*
     * An alias of +null+
     */
    rb_define_global_const("NULL", Qnull);

}


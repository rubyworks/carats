#include <ruby.h>
#include <st.h>

/*
 *  call-seq:
 *     module.anonymous?     -> true/false
 *
 * Returns false if a module or class is referenced by constant.
 *
 */

VALUE
rb_mod_anonymous(VALUE mod)
{
    int permanent;
    VALUE path = classname(mod, &permanent);

    if (!NIL_P(path)) return Qtrue;
    return Qfalse;
}

/*
 *  call-seq:
 *     module.permanent?     -> true/false
 *
 * A class or module is "permanent", that means it has no
 * anonymous names.
 *
 */

VALUE
rb_mod_permanent(VALUE mod)
{
    int permanent;
    VALUE path = classname(mod, &permanent);

    if (permanent) return Qtrue;
    return Qfalse;
}

void Init_carats(){
  rb_define_method(rb_cModule, "anonymous?", rb_mod_anonymous, 0);
  rb_define_method(rb_cModule, "permanent?", rb_mod_permanent, 0);
}



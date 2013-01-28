#include <ruby.h>
#include <st.h>

/*
 *  call-seq:
 *     str.indent(n, c)   -> new_str
 *
 * Indent a string by inserting a number of spaces before each line.
 * Optionally use a different character besides a space.
 *
 */

VALUE
rb_str_indent(VALUE num, VALUE chr)
{
  int n = NUM2LONG(num)
  if (n >= 0)
    str_gsub(/^/, rb_str_times(chr, num))
  else
    str_gsub(/^#{Regexp.escape(c)}{0,#{-n}}/, "")
  end

}

void Init_carats(){
  rb_define_method(rb_cString, "indent", rb_str_indent, 2);

  /* TODO: alias as tab? */

}


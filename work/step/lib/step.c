/*
 *  step.c  --  Simple Ruby Extensions
 */

#include "step.h"

#include <st.h>
#include <rubyio.h>
#include <re.h>

#include <sys/stat.h>


static VALUE step_index_blk( VALUE);
static VALUE step_rindex_blk( VALUE);
#ifdef ARRAY_INDEX_WITH_BLOCK
static VALUE step_index_val( VALUE, VALUE);
static VALUE step_rindex_val( VALUE, VALUE);
#endif

static ID id_delete_at;


#ifdef KERNEL_TAP

/*
 *  call-seq:
 *     obj.tap { |x| ... }    -> obj
 *
 *  Yields <code>x</code> to the block, and then returns <code>x</code>.
 *  The primary purpose of this method is to "tap into" a method chain,
 *  in order to perform operations on intermediate results within the chain.
 *
 *      (1..10)                  .tap { |x| puts "original: #{x.inspect}" }
 *        .to_a                  .tap { |x| puts "array:    #{x.inspect}" }
 *        .select { |x| x%2==0 } .tap { |x| puts "evens:    #{x.inspect}" }
 *        .map { |x| x*x }       .tap { |x| puts "squares:  #{x.inspect}" }
 *
 */

VALUE
rb_krn_tap( VALUE obj)
{
    rb_yield( obj);
    return obj;
}
#endif


/*
 *  call-seq:
 *     str.notempty?   -> nil or self
 *
 *  Returns <code>self</code> if and only if <code>str</code> is not
 *  empty, <code>nil</code> otherwise.
 *
 *     "hello".notempty?   #=> "hello"
 *     "".notempty?        #=> nil
 */

VALUE
rb_str_notempty( VALUE str)
{
#if 0
    /* Ruby Coding style */
    if (RSTRING_LEN(str) == 0)
        return Qnil;
    return str;
#else
    return RSTRING_LEN( str) ? str : Qnil;
#endif
}


/*
 *  call-seq:
 *     str.eat( n = nil)   -> str
 *
 *  Returns first <code>n</code> characters of <code>self</code> or
 *  whole string if <code>n</code> is <code>nil</code>. The returned
 *  substring will be deleted from <code>self</code>. If <code>n</code>
 *  is negative, characters will be eaten from the right.
 *
 *     a = "upcase"
 *     a.eat 2             #=> "up"
 *     a                   #=> "case"
 */

VALUE
rb_str_eat( int argc, VALUE *argv, VALUE str)
{
    VALUE val;
    int n;
    int l;
    int r;

    n = l = RSTRING(str)->len;
    if (rb_scan_args( argc, argv, "01", &val) == 1) {
        if (!NIL_P( val)) {
            int v = NUM2INT( val);
            if (v >= 0) {
                if (n >= v) n = v;
            } else {
                n = -n;
                if (n <= v) n = v;
            }
        }
    }

    rb_str_modify(str);
    if (n > 0) {
        r = l - n;
        val = rb_str_new5( str, RSTRING(str)->ptr, n);
        memmove(RSTRING(str)->ptr, RSTRING(str)->ptr + n, r);
    } else {
        r = l + n;
        val = rb_str_new5( str, RSTRING(str)->ptr + r, -n);
    }
    RSTRING(str)->len = r;
    OBJ_INFECT(val, str);
    return val;
}


/*
 *  call-seq:
 *     str.cut!( length)   -> str
 *
 *  Cut string to <code>length</code>. If nothing was removed,
 *  <code>nil</code> is returned.
 *
 *     a = "hello"
 *     a.cut! 4            #=> "hell"
 *     a                   #=> "hell"
 *     a.cut! 4            #=> nil
 */

VALUE
rb_str_cut_bang( VALUE str, VALUE len)
{
    int l = NUM2INT( len);

    rb_str_modify(str);
    if (l < RSTRING(str)->len) {
        RSTRING(str)->len = l;
        return str;
    }
    return Qnil;
}


/*
 *  call-seq:
 *     str.clear   -> self
 *
 *  Set to empty string. Equivalent to <code>str.replace ""</code>.
 *
 *     a = "hello"  #=> "hello"
 *     a.clear      #=> ""
 *     a.empty?     #=> true
 */

VALUE
rb_str_clear( VALUE str)
{
    rb_str_modify(str);
    rb_str_resize(str, 0);
    return str;
}


/*
 *  call-seq:
 *     str.head( n)   -> str
 *
 *  Returns first <code>n</code> bytes in <code>str</code>.
 *
 *     "hello".head( 2)    #=> "he"
 */

VALUE
rb_str_head( VALUE str, VALUE n)
{
    VALUE str2;
    long len;

    len = NUM2LONG(n);
    if (len < 0) return Qnil;
    if (len > RSTRING(str)->len) {
        len = RSTRING(str)->len;
    }
    str2 = rb_str_new5(str, RSTRING(str)->ptr, len);
    OBJ_INFECT(str2, str);

    return str2;
}


/*
 *  call-seq:
 *     str.rest( n)   -> str
 *
 *  Return rest after <code>n</code> bytes in <code>str</code>.
 *
 *     "hello".rest( 2)    #=> "llo"
 */

VALUE
rb_str_rest( VALUE str, VALUE n)
{
    VALUE str2;
    long beg, len;

    beg = NUM2LONG(n);
    if (beg > RSTRING(str)->len) return Qnil;
    if (beg < 0) {
        beg = 0;
    }
    len = RSTRING(str)->len - beg;
    str2 = rb_str_new5(str, RSTRING(str)->ptr+beg, len);
    OBJ_INFECT(str2, str);

    return str2;
}


/*
 *  call-seq:
 *     str.tail( n)   -> str
 *
 *  Returns last <code>n</code> bytes in <code>str</code>.
 *
 *     "hello".tail( 2)    #=> "lo"
 */

VALUE
rb_str_tail( VALUE str, VALUE n)
{
    VALUE str2;
    long beg, len;

    len = NUM2LONG(n);
    if (len < 0) return Qnil;
    beg = RSTRING(str)->len - len;
    if (beg < 0) {
        beg = 0;
        len = RSTRING(str)->len;
    }
    str2 = rb_str_new5(str, RSTRING(str)->ptr+beg, len);
    OBJ_INFECT(str2, str);

    return str2;
}


/*
 *  call-seq:
 *     str.starts_with( oth)   -> nil or int
 *
 *  Checks whether the head is <code>oth</code>. Returns length of
 *  <code>oth</code> when matching.
 *
 *     "sys-apps".starts_with( "sys-")    #=> 4
 */

VALUE
rb_str_starts_with( VALUE str, VALUE oth)
{
    long i;
    char *s, *o;

    i = RSTRING(oth)->len;
    if (i > RSTRING(str)->len)
        return Qnil;
    s = RSTRING(str)->ptr;
    o = RSTRING(oth)->ptr;
    for (; i; i--, s++, o++) {
        if (*s != *o)
            return Qnil;
    }
    return INT2NUM( RSTRING(oth)->len);
}


/*
 *  call-seq:
 *     str.ends_with( oth)   -> nil or int
 *
 *  Checks whether the tail is <code>oth</code>. Returns the position
 *  where <code>oth</code> starts when matching.
 *
 *     "sys-apps".ends_with( "-apps")    #=> 3
 */

VALUE
rb_str_ends_with( VALUE str, VALUE oth)
{
    long i;
    char *s, *o;

    i = RSTRING(oth)->len;
    if (i > RSTRING(str)->len)
        return Qnil;
    s = RSTRING(str)->ptr + RSTRING(str)->len;
    o = RSTRING(oth)->ptr + RSTRING(oth)->len;
    for (; i; i--)
        if (*--s != *--o)
            return Qnil;
    return INT2NUM( RSTRING(str)->len - RSTRING(oth)->len);
}


/*
 *  call-seq:
 *     ary.notempty?   -> nil or self
 *
 *  Returns <code>self</code> if and only if <code>ary</code> is not
 *  empty, <code>nil</code> otherwise.
 *
 *     %w(a b).notempty?   #=> [ "a", "b"]
 *     [].notempty?        #=> nil
 */

VALUE
rb_ary_notempty( VALUE ary)
{
    return RARRAY( ary)->len == 0 ? Qnil : ary;
}


/*
 *  call-seq:
 *     array.indexes()  ->  ary
 *     array.keys()     ->  ary
 *
 *  Returns the indexes from <code>0</code> to
 *  <code>array.length()</code> as an array.
 *
 *     [ "a", "h", "q"].indexes   #=> [ 0, 1, 2]
 */

VALUE
rb_ary_indexes( VALUE ary)
{
    VALUE ret;
    int i, j;

    j = RARRAY( ary)->len;
    ret = rb_ary_new2( j);
    RARRAY( ret)->len = j;
    for (i = 0; j; ++i, --j) {
        rb_ary_store( ret, i, INT2NUM(i));
    }
    return ret;
}


/*
 *  call-seq:
 *     array.pick { |elem| ... }  -> obj or nil
 *
 *  Deletes the element where the <em>block</em> first returns
 *  <code>true</code>. Or <code>nil</code> if nothing is found.
 *
 *     a = %w(ant bat cat dog)
 *     a.pick { |e| e =~ /^c/ }  #=> "cat"
 *     a                         #=> ["ant", "bat", "dog"]
 *     a.pick { |e| e =~ /^x/ }  #=> nil
 */

VALUE
rb_ary_pick( VALUE ary)
{
    VALUE pos;

    pos = step_index_blk( ary);
    if (!NIL_P( pos)) return rb_funcall( ary, id_delete_at, 1, pos);
    return Qnil;
}

VALUE
step_index_blk( VALUE ary)
{
    long i;

    for (i = 0; i < RARRAY( ary)->len; i++) {
        if (rb_yield( RARRAY( ary)->ptr[ i]))
            return LONG2NUM( i);
    }
    return Qnil;
}

/*
 *  call-seq:
 *     array.rpick { |elem| ... }  -> obj or nil
 *
 *  Deletes the element where the <em>block</em> first returns
 *  <code>true</code>. Or <code>nil</code> if nothing is found. Search
 *  from right to left.
 *
 *     a = %w(ant cow bat cat dog)
 *     a.rpick { |e| e =~ /^c/ }  #=> "cat"
 *     a                          #=> ["ant", "cow", "bat", "dog"]
 *     a.rpick { |e| e =~ /^x/ }  #=> nil
 */

VALUE
rb_ary_rpick( VALUE ary)
{
    VALUE pos;

    pos = step_rindex_blk( ary);
    if (!NIL_P( pos)) return rb_funcall( ary, id_delete_at, 1, pos);
    return Qnil;
}

VALUE
step_rindex_blk( VALUE ary)
{
    long i;

    for (i = RARRAY( ary)->len; i;) {
        --i;
        if (rb_yield( RARRAY( ary)->ptr[ i]))
            return LONG2NUM( i);
    }
    return Qnil;
}


#ifdef ARRAY_INDEX_WITH_BLOCK

/*
 *  call-seq:
 *     array.index( obj)              ->  int or nil
 *     array.index() { |elem| ... }   ->  int or nil
 *
 *  Returns the index of the first object in <code>self</code> such that
 *  is <code>==</code> to <code>obj</code> or the <em>block</em> returns
 *  <code>true</code>. If no match is found, <code>nil</code> is
 *  returned.
 *
 *     a = %w(a b c d e)
 *     a.index("b")               #=> 1
 *     a.index("z")               #=> nil
 *     a.index { |e| e >= "b" }   #=> 1
 *     a.index { |e| e >= "q" }   #=> nil
 */

VALUE
rb_ary_index( int argc, VALUE *argv, VALUE ary)
{
    VALUE val;

    if (rb_scan_args( argc, argv, "01", &val) == 1) {
        if (rb_block_given_p()) rb_warning( "given block not used");
        return step_index_val( ary, val);
    }
    else {
        return step_index_blk( ary);
    }
    return Qnil;
}

VALUE
step_index_val( VALUE ary, VALUE val)
{
    long i;

    for (i = 0; i < RARRAY( ary)->len; i++) {
        if (rb_equal( RARRAY( ary)->ptr[ i], val))
            return LONG2NUM( i);
    }
    return Qnil;
}


/*
 *  call-seq:
 *     array.rindex( obj)              ->  int or nil
 *     array.rindex() { |elem| ... }   ->  int or nil
 *
 *  Returns the index of the first object in <code>self</code> such that
 *  is <code>==</code> to <code>obj</code> or the <em>block</em> returns
 *  <code>true</code>. If no match is found, <code>nil</code> is
 *  returned. Search from right to left.
 *
 *     a = %w(a b c d e)
 *     a.rindex("b")               #=> 1
 *     a.rindex("z")               #=> nil
 *     a.rindex { |e| e >= "b" }   #=> 4
 *     a.rindex { |e| e >= "q" }   #=> nil
 */

VALUE
rb_ary_rindex( int argc, VALUE *argv, VALUE ary)
{
    VALUE val;

    if (rb_scan_args( argc, argv, "01", &val) == 1) {
        if (rb_block_given_p()) rb_warning( "given block not used");
        return step_rindex_val( ary, val);
    }
    else {
        return step_rindex_blk( ary);
    }
    return Qnil;
}

VALUE
step_rindex_val( VALUE ary, VALUE val)
{
    long i;

    for (i = RARRAY( ary)->len; i;) {
        --i;
        if (rb_equal( RARRAY( ary)->ptr[ i], val))
            return LONG2NUM( i);
    }
    return Qnil;
}

#endif



/*
 *  call-seq:
 *     num.grammatical sing, plu  -> str
 *
 *  Singular or plural
 *
 *     1.grammatical "line", "lines"         #=>  "line"
 *     6.grammatical "child", "children"     #=>  "children"
 */

VALUE
rb_num_grammatical( VALUE num, VALUE sing, VALUE plu)
{
    long l;
    double d;

    switch (TYPE(num)) {
        case T_FIXNUM:
            l = NUM2LONG(num);
            if (l == 1l || l == -1l)
                return sing;
            break;

        case T_BIGNUM:
            /* 1 is not a Bignum */
            break;

        case T_FLOAT:
            d = RFLOAT(num)->value;
            if (d == 1.0 || d == -1.0)
                return sing;
            break;

        default:
            break;
    }
    return plu;
}


/*
 *  call-seq:
 *     hash.notempty?   -> nil or self
 *
 *  Returns <code>self</code> if and only if <code>hash</code> is not
 *  empty, <code>nil</code> otherwise.
 *
 *     { :a => "A"}.notempty?   #=> { :a => "A"}
 *     {}.notempty?             #=> nil
 */

VALUE
rb_hash_notempty( VALUE hash)
{
    return RHASH(hash)->tbl->num_entries == 0 ? Qnil : hash;
}



/*
 *  call-seq:
 *     file.size   -> integer
 *
 *  Returns <code>file</code>'s size. A shortcut for
 *  <code>file.stat.size</code>. This constitutes consistency with
 *  <code>StringIO</code>.
 *
 *     file.size     #=> 16384
 */

VALUE
rb_file_size( VALUE obj)
{
    OpenFile *fptr;
    struct stat st;

    GetOpenFile(obj, fptr);
    if (fstat(fileno(fptr->f), &st) == -1) {
        rb_sys_fail(fptr->path);
    }
    return INT2FIX(st.st_size);
}


/*
 *  call-seq:
 *     mtch.begin( n = nil)   -> integer
 *
 *  Returns the offset of the start of the <code>n</code>th element of
 *  the match array in the string. In case <code>n</code> is
 *  <code>nil</code> the 0th match (whole) is assumed.
 *
 *     m = /(.)(.)(\d+)(\d)/.match("THX1138.")
 *     m.begin( 0)  #=> 1
 *     m.begin      #=> 1
 *     m.begin( 2)  #=> 2
 */

VALUE
rb_match_begin( int argc, VALUE *argv, VALUE match)
{
    VALUE val;
    int i;

    if (rb_scan_args( argc, argv, "01", &val) == 1) {
        i = NIL_P( val) ? 0 : NUM2INT( val);
    } else
        i = 0;

    if (i < 0 || RMATCH(match)->regs->num_regs <= i)
        rb_raise( rb_eIndexError, "index %d out of matches", i);

    if (RMATCH(match)->regs->beg[i] < 0)
        return Qnil;

    return INT2FIX(RMATCH(match)->regs->beg[i]);
}


/*
 *  call-seq:
 *     mtch.end( n = nil)   -> integer
 *
 *  Returns the offset of the character immediately following the end of
 *  the <code>n</code>th element of the match array in the string. In
 *  case <code>n</code> is <code>nil</code> the 0th match (whole) is
 *  assumed.
 *
 *     m = /(.)(.)(\d+)(\d)/.match("THX1138.")
 *     m.end( 0)  #=> 7
 *     m.end      #=> 7
 *     m.end( 2)  #=> 3
 */

VALUE
rb_match_end( int argc, VALUE *argv, VALUE match)
{
    VALUE val;
    int i;

    if (rb_scan_args( argc, argv, "01", &val) == 1) {
        i = NIL_P( val) ? 0 : NUM2INT( val);
    } else
        i = 0;

    if (i < 0 || RMATCH(match)->regs->num_regs <= i)
        rb_raise( rb_eIndexError, "index %d out of matches", i);

    if (RMATCH(match)->regs->beg[i] < 0)
        return Qnil;

    return INT2FIX(RMATCH(match)->regs->end[i]);
}




/*
 *  call-seq:
 *     Struct[ ...]  -> cls
 *
 *  Alias for Struct.new; This applies to Struct subclass generation
 *  as well as to the subclasses instance creation.
 *
 *    S = Struct[ :a, :b]    #=>  S
 *    s = S[ 'A', 'B']       #=>  #<struct S a="A", b="B">
 *
 */


void Init_step( void)
{
    rb_define_alias( rb_cObject, "cls", "class");
#ifdef KERNEL_TAP
    rb_define_method( rb_mKernel, "tap", rb_krn_tap, 0);
#endif

    rb_define_method( rb_cString, "notempty?", rb_str_notempty, 0);
    rb_define_method( rb_cString, "eat", rb_str_eat, -1);
    rb_define_method( rb_cString, "cut!", rb_str_cut_bang, 1);
    rb_define_method( rb_cString, "clear", rb_str_clear, 0);
    rb_define_method( rb_cString, "head", rb_str_head, 1);
    rb_define_method( rb_cString, "rest", rb_str_rest, 1);
    rb_define_method( rb_cString, "tail", rb_str_tail, 1);
    rb_define_method( rb_cString, "starts_with", rb_str_starts_with, 1);
    rb_define_method( rb_cString, "ends_with", rb_str_ends_with, 1);

    rb_define_method( rb_cNumeric, "grammatical", rb_num_grammatical, 2);

    rb_define_method( rb_cArray, "notempty?", rb_ary_notempty, 0);
    rb_define_method( rb_cArray, "indexes", rb_ary_indexes, 0);
    rb_define_alias( rb_cArray,  "keys", "indexes");
    rb_define_method( rb_cArray, "pick", rb_ary_pick, 0);
    rb_define_method( rb_cArray, "rpick", rb_ary_rpick, 0);
#ifdef ARRAY_INDEX_WITH_BLOCK
    rb_define_method( rb_cArray, "index", rb_ary_index, -1);
    rb_define_method( rb_cArray, "rindex", rb_ary_rindex, -1);
#endif

    rb_define_method( rb_cHash, "notempty?", rb_hash_notempty, 0);

    rb_define_method( rb_cFile, "size", rb_file_size, 0);

    rb_define_method(rb_cMatch, "begin", rb_match_begin, -1);
    rb_define_method(rb_cMatch, "end", rb_match_end, -1);

    rb_define_alias( rb_singleton_class( rb_cStruct), "[]", "new");

    id_delete_at = rb_intern( "delete_at");
}


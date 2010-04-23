/*
 *  filesys.c  --  File system tools
 */

#include "filesys.h"

#include <stdlib.h>
#ifdef __FSID_T_TYPE
    /* Linux */
    #include <sys/vfs.h>
#else
    #include <sys/param.h>
    #include <sys/mount.h>
#endif



static struct statfs *get_statfs( VALUE);

static ID id_mul;

/*
 *  Document-class: Filesys
 *
 *  File systems. Mount and umount commands are on the TODO list.
 */

/*
 *  Document-class: Filesys::Stat
 *
 *  Objects of class <code>Filesys::Stat</code> encapsulate common status
 *  information for <code>Filesys</code> objects. The information is
 *  recorded at the moment the <code>Filesys::Stat</code> object is
 *  created; changes made to the file after that point will not be
 *  reflected.
 *
 *  Many of its attributes contain platform-specific values, and not all
 *  values are meaningful on all systems.
 */

VALUE
rb_fsstat_s_alloc( VALUE klass)
{
    return Data_Wrap_Struct( klass, NULL, &free, (struct statfs *) NULL);
}

/*
 * call-seq:
 *
 *   Filesys::Stat.new( dir_name)  => stat
 *
 * Create a Filesys::Stat object for the given file system.
 */

VALUE
rb_fsstat_init( VALUE obj, VALUE dname)
{
    struct statfs st, *nst;

    SafeStringValue( dname);

    if (statfs( StringValueCStr( dname), &st) == -1)
        rb_sys_fail( RSTRING(dname)->ptr);
    if (DATA_PTR(obj)) {
        free( DATA_PTR(obj));
        DATA_PTR(obj) = NULL;
    }
    nst = ALLOC(struct statfs);
    *nst = st;
    DATA_PTR(obj) = nst;

    return Qnil;
}

/* :nodoc: */
VALUE
rb_fsstat_init_copy( VALUE copy, VALUE orig)
{
    struct statfs *nst;

    if (copy == orig)
        return orig;

    rb_check_frozen( copy);
    if (!rb_obj_is_instance_of( orig, rb_obj_class( copy)))
        rb_raise(rb_eTypeError, "wrong argument class");
    if (DATA_PTR(copy)) {
        free( DATA_PTR(copy));
        DATA_PTR(copy) = NULL;
    }
    if (DATA_PTR(orig)) {
        nst = ALLOC(struct statfs);
        *nst = *(struct statfs *) DATA_PTR(orig);
        DATA_PTR(copy) = nst;
    }

    return copy;
}

/* :nodoc: */
struct statfs *
get_statfs( VALUE self)
{
    struct statfs *st;
    Data_Get_Struct(self, struct statfs, st);
    if (!st)
        rb_raise( rb_eTypeError, "uninitialized Filesys::Stat");
    return st;
}



/*
 *  call-seq:
 *     stat.type    => fixnum
 *
 *  Type of filesystem.
 */

VALUE
rb_fsstat_type( VALUE self)
{
    return INT2NUM(get_statfs(self)->f_type);
}

/*
 *  call-seq:
 *     stat.bsize    => fixnum
 *
 *  Filesystem fragment size.
 */

VALUE
rb_fsstat_bsize( VALUE self)
{
    return INT2NUM(get_statfs(self)->f_bsize);
}

/*
 *  call-seq:
 *     stat.blocks    => fixnum
 *
 *  Total data blocks in filesystem.
 */

VALUE
rb_fsstat_blocks( VALUE self)
{
    return INT2NUM(get_statfs(self)->f_blocks);
}

/*
 *  call-seq:
 *     stat.bfree    => fixnum
 *
 *  Free blocks in filesystem.
 */

VALUE
rb_fsstat_bfree( VALUE self)
{
    return INT2NUM(get_statfs(self)->f_bfree);
}

/*
 *  call-seq:
 *     stat.bavail    => fixnum
 *
 *  Free blocks avail to non-superuser.
 */

VALUE
rb_fsstat_bavail( VALUE self)
{
    return INT2NUM(get_statfs(self)->f_bavail);
}

/*
 *  call-seq:
 *     stat.files    => fixnum
 *
 *  Total file nodes in filesystem.
 */

VALUE
rb_fsstat_files( VALUE self)
{
    return INT2NUM(get_statfs(self)->f_files);
}

/*
 *  call-seq:
 *     stat.ffree    => fixnum
 *
 *  Free nodes avail to non-superuser.
 */

VALUE
rb_fsstat_ffree( VALUE self)
{
    return INT2NUM(get_statfs(self)->f_ffree);
}


/*
 *  call-seq:
 *     stat.fsid    => fixnum
 *
 *  Filesystem id.
 */

#ifdef __FSID_T_TYPE
    /* Linux */
    #define FSID_val __val
#else
    #define FSID_val val
#endif

VALUE
rb_fsstat_fsid( VALUE self)
{
    struct statfs *s;
    VALUE r;
    int i;

    s = get_statfs( self);
    i = 2;
    r = rb_ary_new2( i);
    RARRAY( r)->len = i;
    while (i > 0) {
        --i;
        rb_ary_store( r, i, INT2NUM(s->f_fsid.FSID_val[i]));
    }
    return r;
}


/*
 *  call-seq:
 *     stat.bytes    => fixnum
 *
 *  Total data bytes in filesystem.
 */

VALUE
rb_fsstat_bytes( VALUE self)
{
    struct statfs *s;

    s = get_statfs( self);
    return rb_funcall( INT2NUM(s->f_blocks), id_mul, 1, INT2NUM(s->f_bsize));
}

/*
 *  call-seq:
 *     stat.free    => num
 *
 *  Free bytes in filesystem.
 */

VALUE
rb_fsstat_free( VALUE self)
{
    struct statfs *s;

    s = get_statfs( self);
    return rb_funcall( INT2NUM(s->f_bfree), id_mul, 1, INT2NUM(s->f_bsize));
}

/*
 *  call-seq:
 *     stat.avail    => num
 *
 *  Free bytes avail to non-superuser.
 */

VALUE
rb_fsstat_avail( VALUE self)
{
    struct statfs *s;

    s = get_statfs( self);
    return rb_funcall( INT2NUM(s->f_bavail), id_mul, 1, INT2NUM(s->f_bsize));
}


/*
 *  call-seq:
 *     stat.pfree    => fixnum
 *
 *  Free percentage in filesystem.
 */

VALUE
rb_fsstat_pfree( VALUE self)
{
    struct statfs *s;

    s = get_statfs( self);
    return rb_float_new( 100.0 * s->f_bfree / s->f_blocks);
}

/*
 *  call-seq:
 *     stat.pavail    => fixnum
 *
 *  Free percentage avail to non-superuser.
 */

VALUE
rb_fsstat_pavail( VALUE self)
{
    struct statfs *s;

    s = get_statfs( self);
    return rb_float_new( 100.0 * s->f_bavail / s->f_blocks);
}


/*
 * call-seq:
 *   stat.inspect  =>  string
 *
 * Produce a nicely formatted description of <i>stat</i> with all available
 * information.
 */

VALUE
rb_fsstat_inspect( VALUE self)
{
    VALUE str;
    int i, m;
    static const struct {
        const char  *name;
        VALUE      (*func)(VALUE);
    } member[] = {
        { "type",   &rb_fsstat_type  },
        { "bsize",  &rb_fsstat_bsize },
        { "blocks", &rb_fsstat_blocks},
        { "bfree",  &rb_fsstat_bfree },
        { "bavail", &rb_fsstat_bavail},
        { "files",  &rb_fsstat_files },
        { "ffree",  &rb_fsstat_ffree },
        { "fsid",   &rb_fsstat_fsid  }
    };

    str = rb_str_buf_new2("#<");
    rb_str_buf_cat2(str, rb_obj_classname( self));
    rb_str_buf_cat2(str, " ");

    m = sizeof(member) / sizeof(member[0]);
    for (i = 0; i < m; i++) {
        VALUE v;

        if (i > 0)
            rb_str_buf_cat2( str, ", ");
        rb_str_buf_cat2( str, member[i].name);
        rb_str_buf_cat2( str, "=");
        rb_str_append( str, rb_inspect( (*member[i].func)( self)));
    }
    rb_str_buf_cat2( str, ">");
    OBJ_INFECT( str, self);

    return str;
}



void Init_filesys( void)
{
    VALUE rb_cFilesys;
    VALUE rb_cFilesysStat;

    rb_cFilesys = rb_define_class( "Filesys", rb_cObject);

    rb_cFilesysStat = rb_define_class_under( rb_cFilesys, "Stat", rb_cObject);
    rb_define_alloc_func( rb_cFilesysStat,  rb_fsstat_s_alloc);
    rb_define_method( rb_cFilesysStat, "initialize", rb_fsstat_init, 1);
    rb_define_method( rb_cFilesysStat, "initialize_copy", rb_fsstat_init_copy, 1);

    rb_define_method( rb_cFilesysStat, "type",   rb_fsstat_type  , 0);
    rb_define_method( rb_cFilesysStat, "bsize",  rb_fsstat_bsize , 0);
    rb_define_method( rb_cFilesysStat, "blocks", rb_fsstat_blocks, 0);
    rb_define_method( rb_cFilesysStat, "bfree",  rb_fsstat_bfree , 0);
    rb_define_method( rb_cFilesysStat, "bavail", rb_fsstat_bavail, 0);
    rb_define_method( rb_cFilesysStat, "files",  rb_fsstat_files , 0);
    rb_define_method( rb_cFilesysStat, "ffree",  rb_fsstat_ffree , 0);
    rb_define_method( rb_cFilesysStat, "fsid",   rb_fsstat_fsid  , 0);

    rb_define_method( rb_cFilesysStat, "bytes",  rb_fsstat_bytes, 0);
    rb_define_method( rb_cFilesysStat, "free",   rb_fsstat_free , 0);
    rb_define_method( rb_cFilesysStat, "avail",  rb_fsstat_avail, 0);
    rb_define_method( rb_cFilesysStat, "pfree",  rb_fsstat_pfree , 0);
    rb_define_method( rb_cFilesysStat, "pavail", rb_fsstat_pavail, 0);

    rb_define_method( rb_cFilesysStat, "inspect", rb_fsstat_inspect, 0);

    id_mul = rb_intern( "*");
}


/*
 *  filesys.h  --  File system tools
 */

#ifndef __FILESYS_H__
#define __FILESYS_H__

#include <ruby.h>


extern VALUE rb_fsstat_s_alloc( VALUE);
extern VALUE rb_fsstat_init( VALUE, VALUE);
extern VALUE rb_fsstat_init_copy( VALUE, VALUE);

extern VALUE rb_fsstat_type(   VALUE);
extern VALUE rb_fsstat_bsize(  VALUE);
extern VALUE rb_fsstat_blocks( VALUE);
extern VALUE rb_fsstat_bfree(  VALUE);
extern VALUE rb_fsstat_bavail( VALUE);
extern VALUE rb_fsstat_files(  VALUE);
extern VALUE rb_fsstat_ffree(  VALUE);
extern VALUE rb_fsstat_fsid(   VALUE);

extern VALUE rb_fsstat_bytes(  VALUE);
extern VALUE rb_fsstat_free(   VALUE);
extern VALUE rb_fsstat_avail(  VALUE);
extern VALUE rb_fsstat_pfree(  VALUE);
extern VALUE rb_fsstat_pavail( VALUE);

extern VALUE rb_fsstat_inspect( VALUE);

extern void Init_filesys( void);

#endif


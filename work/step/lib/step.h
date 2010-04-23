/*
 *  step.h  --  Simple Ruby Extensions
 */


#ifndef __STEP_H__
#define __STEP_H__

#include <ruby.h>


extern VALUE rb_str_notempty( VALUE str);
extern VALUE rb_str_eat( int, VALUE *, VALUE);
extern VALUE rb_str_cut_bang( VALUE, VALUE);
extern VALUE rb_str_clear( VALUE);
extern VALUE rb_str_head( VALUE, VALUE);
extern VALUE rb_str_rest( VALUE, VALUE);
extern VALUE rb_str_tail( VALUE, VALUE);
extern VALUE rb_str_starts_with( VALUE, VALUE);
extern VALUE rb_str_ends_with( VALUE, VALUE);
extern VALUE rb_ary_notempty( VALUE);
extern VALUE rb_ary_indexes( VALUE);
extern VALUE rb_ary_pick( VALUE);
extern VALUE rb_ary_rpick( VALUE);
#ifdef ARRAY_INDEX_WITH_BLOCK
extern VALUE rb_ary_index( int, VALUE *, VALUE);
extern VALUE rb_ary_rindex( int, VALUE *, VALUE);
#endif
extern VALUE rb_int_grammatical( VALUE, VALUE, VALUE);
extern VALUE rb_hash_notempty( VALUE);
extern VALUE rb_file_size( VALUE);
extern VALUE rb_match_begin( int, VALUE *, VALUE);
extern VALUE rb_match_end( int, VALUE *, VALUE);

extern void Init_step( void);

#endif


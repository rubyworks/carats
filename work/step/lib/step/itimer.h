/*
 *  itimer.h  --  Interval timer
 */


#ifndef __ITIMER_H__
#define __ITIMER_H__

#include <ruby.h>


extern VALUE rb_process_setitimer( int, VALUE *, VALUE);
extern VALUE rb_process_getitimer( VALUE obj);

extern void Init_itimer( void);

#endif


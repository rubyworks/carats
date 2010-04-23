/*
 *  itimer.c  --  Interval timer
 */


#include "itimer.h"

#include <math.h>

static void  step_sec_timeval( VALUE, struct timeval *t);
static VALUE step_timeval_sec( struct timeval *);


/*
 *  call-seq:
 *     Process.setitimer( interval = nil, value = nil)   -> nil
 *
 *  Set alarm timer. If <code>value</code> is nonzero, it is the
 *  expiration time to the first alarm. If it is zero, the timer is disabled.
 *  If <code>value</code> is nonzero and <code>interval</code> is zero,
 *  the alarm is triggered once.
 *
 */

VALUE
rb_process_setitimer( int argc, VALUE *argv, VALUE obj)
{
    VALUE isec;
    VALUE vsec;
    struct itimerval it;

    rb_scan_args( argc, argv, "02", &isec, &vsec);

    step_sec_timeval( isec, &it.it_interval);
    if (NIL_P(vsec) && !NIL_P(isec))
        it.it_value = it.it_interval;
    else
    step_sec_timeval( vsec, &it.it_value);

    if (setitimer( ITIMER_REAL, &it, NULL) < 0)
        rb_raise( rb_eSystemCallError, "setitimer failed.");
    return Qnil;
}

void
step_sec_timeval( VALUE secs, struct timeval *t)
{
    switch (TYPE(secs)) {
      case T_FIXNUM:
        t->tv_sec = FIX2LONG(secs), t->tv_usec = 0;
        if (t->tv_sec < 0)
            rb_raise( rb_eArgError, "time interval must be positive");
        break;

      case T_FLOAT:
        if (RFLOAT(secs)->value < 0.0)
            rb_raise( rb_eArgError, "time interval must be positive");
        else {
            double f, d;

            d = modf( RFLOAT(secs)->value, &f);
            t->tv_sec = (time_t) f, t->tv_usec = (time_t) (d*1e6+0.5);
            if (f != t->tv_sec)
                rb_raise( rb_eRangeError, "time interval out of Time range",
                    RFLOAT(secs)->value);
        }
        break;

      case T_BIGNUM:
        t->tv_sec = NUM2LONG(secs), t->tv_usec = 0;
        if (t->tv_sec < 0)
            rb_raise(rb_eArgError, "time interval must be positive");
        break;

      case T_NIL:
        t->tv_sec = 0, t->tv_usec = 0;
        break;

      default:
        rb_raise( rb_eTypeError, "can't convert %s into time interval",
                 rb_obj_classname( secs));
        break;
    }
}


/*
 *  call-seq:
 *     Process.getitimer -> [interval, value]
 *
 *  Returns the interval and the remaining seconds to next alarm.
 */

VALUE
rb_process_getitimer( VALUE obj)
{
    struct itimerval it;
    VALUE r;

    if (getitimer( ITIMER_REAL, &it) < 0)
        rb_raise( rb_eSystemCallError, "getitimer failed.");

    r = rb_ary_new2( 2);
    RARRAY( r)->len = 2;
    rb_ary_store( r, 0, step_timeval_sec( &it.it_interval));
    rb_ary_store( r, 1, step_timeval_sec( &it.it_value));
    return r;
}

VALUE
step_timeval_sec( struct timeval *t)
{
    VALUE r;
    if (t->tv_usec)
        r = rb_float_new( t->tv_sec + (1e-6 * t->tv_usec));
    else
        r = INT2NUM(t->tv_sec);
    return r;
}


void Init_itimer( void)
{
    rb_define_singleton_method( rb_mProcess, "setitimer", rb_process_setitimer, -1);
    rb_define_singleton_method( rb_mProcess, "getitimer", rb_process_getitimer, 0);
}


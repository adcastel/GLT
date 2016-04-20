/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */




#ifndef FAST_GLT_H
#define	FAST_GLT_H


#include <glt_common.h>

//Core functions

#include <glt.c>
#include <glt_wu.c>
#include <glt_mutex.c>
#include <glt_barrier.c>
#include <glt_condition.c>
#include <glt_timer.c>
#include <glt_util.c>

//Extended functions

#include <glt_event.c>
#include <glt_future_promise.c>
#include <glt_tls.c>
#include <glt_pool.c>
#include <glt_scheduler.c>
#include<glt_self.c>
#include<glt_thread.c>
#include <glt_massivethreads.c>
#include <glt_qthreads.c>

#endif	/* FAST_GLT_H */


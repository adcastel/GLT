/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

 int glt_can_log_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE
 void glt_log_start()
{
    myth_log_start();
}

 void glt_log_pause()
{
    myth_log_pause();
}

 void glt_log_flush()
{
    myth_log_flush();
}
 void glt_log_reset()
{
    myth_log_reset();
}

 void glt_log_annotate_ult(GLT_ult ult, char *name)
{
    myth_log_annotate_thread(ult,name);
}
#endif

 int glt_can_prof_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE
 void glt_sched_prof_start()
{
    myth_sched_prof_start();
}

 void glt_sched_prof_pause()
{
    myth_sched_prof_pause();
}
#endif

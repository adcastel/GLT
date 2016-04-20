/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_can_wsapi_functions()
{
    return 0;
}

GLT_func_prefix int glt_can_prof_functions()
{
    return 0;
}

GLT_func_prefix int glt_can_log_functions()
{
    return 0;
}


GLT_func_prefix int can_felock_functions()
{
    return 0;
}

GLT_func_prefix int can_extended_workunits()
{
    return 0;
}

#ifndef CORE

 GLT_func_prefix  void glt_wu_create_ex(GLT_ult * ult, GLT_workunit_f func, void * arg,
        GLT_workunit_o opt)
  {
      GLT_ERROR_MYTH;
  }
  
GLT_func_prefix  void glt_yield2()
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix  void glt_wu_detach(GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix  void glt_wu_set_cancel_state(int state, int *oldstate)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix  void glt_wu_set_cancel_type(int type, int *oldtype)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix  void glt_wu_test_cancel()
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix  void glt_wu_set_def_stack_size(size_t newsize)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix  void glt_felock_create(GLT_felock * felock)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_felock_free(GLT_felock felock)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_felock_lock(GLT_bool *lock, GLT_felock felock)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_felock_wait_lock(GLT_bool *lock, GLT_felock felock, int val)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_felock_unlock(GLT_bool *unlock, GLT_felock felock)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_felock_status(GLT_felock_status *status, GLT_felock felock)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_felock_set_unlock(GLT_felock felock, int val)
  {
      GLT_ERROR_MYTH;
  }


 
GLT_func_prefix void glt_log_start()
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_log_pause()
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_log_flush()
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_log_reset()
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_log_annotate_ult(GLT_ult ult, char *name)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_sched_prof_start()
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_sched_prof_pause()
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_runqueue_peek(GLT_ult *ult, int victim,void *ptr,size_t *psize)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_get_hint_size(size_t *size, GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_get_hint_ptr(void *ptr, GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_set_hint(GLT_ult ult,void **data,size_t *size)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_rand(int * rand)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_randrr(int *ret, int n)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_runqueue_take(GLT_ult * ult, int victim,GLT_wsapi_decide_f decidefn,void *udata)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_runqueue_pass(GLT_bool *pass, int target,GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_runqueue_push(GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_runqueue_pop(GLT_ult * ult)
  {
      GLT_ERROR_MYTH;
  }

GLT_func_prefix void glt_wsapi_set_stealfunc(GLT_wsapi_steal_f *out, GLT_wsapi_steal_f fn)
  {
      GLT_ERROR_MYTH;
  }
 
#endif

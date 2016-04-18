/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

 int can_felock_functions(){
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE
 void glt_felock_create(GLT_felock * felock)
{
    *felock = myth_felock_create();
}

 void glt_felock_free(GLT_felock felock)
{
    myth_felock_destroy(felock);
}

 void glt_felock_lock(GLT_bool *lock, GLT_felock felock)
{
    *lock = myth_felock_lock(felock);
}

 void glt_felock_wait_lock(GLT_bool *lock, GLT_felock felock, int val)
{
    *lock = myth_felock_wait_lock(felock,val);
}

 void glt_felock_unlock(GLT_bool *unlock, GLT_felock felock)
{
    *unlock = myth_felock_unlock(felock);
}
 void glt_felock_status(GLT_felock_status *status, GLT_felock felock)
{
    *status = myth_felock_status(felock);
}

 void glt_felock_set_unlock(GLT_felock felock, int val)
{
    myth_felock_set_unlock(felock,val);
}

#endif

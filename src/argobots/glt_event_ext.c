/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

//Event functions
int glt_can_event_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE
void glt_get_error_str(int errno, char *str, size_t *len)
{
    ABT_error_get_str (errno,str,len);
}

void glt_event_add_callbac (GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg, 
        int *cb_id)
{
    ABT_event_add_callback (event, ask_cb, ask_user_arg, act_cb, 
            act_user_arg, cb_id);
}

void glt_event_del_callback (GLT_event_kind event, int cb_id)
{
    ABT_event_del_callback (event, cb_id);
}
#endif
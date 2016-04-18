/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>
//self functions

 int glt_can_self()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

 void glt_self_get_type (GLT_unit_type *type)
{
    ABT_self_get_type (type);
}
 void glt_self_is_primary (GLT_bool *flag)
{
    ABT_self_is_primary (flag);
}

 void glt_self_on_primary_xstream (GLT_bool *flag)
{
    ABT_self_on_primary_xstream (flag);
}

 void glt_self_get_last_pool_id (int *pool_id)
{
    ABT_self_get_last_pool_id (pool_id);
}

 void glt_self_suspend (void)
{
    ABT_self_suspend ();
}

 void glt_self_get_arg (void **arg)
{
    ABT_self_get_arg (arg);
}

#endif
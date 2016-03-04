/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

 int glt_can_tls_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

 void glt_key_create (void(*destructor)(void *value), GLT_key *newkey)
{
    myth_key_create(newkey,destructor);
}

 void glt_key_free (GLT_key *key)
{
    myth_key_delete (*key);
}

 void glt_key_set (GLT_key key, void *value)
{
    myth_setspecific (key,value);
}

 void glt_key_get (GLT_key key, void **value)
{
    *value = myth_getspecific (key);
}
#endif

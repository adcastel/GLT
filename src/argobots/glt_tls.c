/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

//tls functions
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
    ABT_key_create (destructor,newkey);
}

void glt_key_free (GLT_key *key)
{
    ABT_key_free (key);
}

void glt_key_set (GLT_key key, void *value)
{
    ABT_key_set (key,value);
}

void glt_key_get (GLT_key key, void **value)
{
    ABT_key_get (key,value);
}
#endif
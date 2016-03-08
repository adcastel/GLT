/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

 int glt_can_serialize_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

 void glt_serialize(GLT_ult ult, GLT_pickle pickle)
{
    //myth_serialize(ult,pickle);
}

 void glt_deserialize(GLT_ult *ult, GLT_pickle pickle)
{
    //*ult = myth_deserialize(pickle);
}

 void glt_ext_deserialize(GLT_ult *ult, GLT_pickle pickle)
{
    //*ult = myth_ext_deserialize(pickle);
}
#endif
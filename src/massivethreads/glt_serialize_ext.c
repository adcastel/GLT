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
    return 0;
#endif
}

#ifndef CORE

/*
 void glt_serialize(GLT_ult ult, GLT_pickle pickle)
{
     GLT_LIB_ERROR;
         //This function is found in the header but not in the static or dynamic massivethreads libraries
    //myth_serialize(ult,pickle);
}

 void glt_deserialize(GLT_ult *ult, GLT_pickle pickle)
{
     GLT_LIB_ERROR;
         //This function is found in the header but not in the static or dynamic massivethreads libraries
    //*ult = myth_deserialize(pickle);
}

 void glt_ext_deserialize(GLT_ult *ult, GLT_pickle pickle)
{
     GLT_LIB_ERROR;
         //This function is found in the header but not in the static or dynamic massivethreads libraries
    //*ult = myth_ext_deserialize(pickle);
}
*/
#endif
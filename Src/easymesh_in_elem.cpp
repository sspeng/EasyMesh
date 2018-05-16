/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::in_elem(const Node *n)
{
 easy::timer.start("in_elem");

 int e;
 
 for(e=0; e<elem.size(); e++)    /* This must search through all elements ?? */
  {
   if(    area(n, &node[elem[e].i], &node[elem[e].j]) >= 0.0
       && area(n, &node[elem[e].j], &node[elem[e].k]) >= 0.0
       && area(n, &node[elem[e].k], &node[elem[e].i]) >= 0.0 )
   
   break;
  }
 easy::timer.stop("in_elem");

 return e;
}

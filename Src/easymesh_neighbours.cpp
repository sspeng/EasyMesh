/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::neighbours() 
/*--------------------------------------------------------------+
|  Counting the elements which surround each node.              |
|  It is important for the two functions: 'relax' and 'smooth'  |
+--------------------------------------------------------------*/
{ 
 int s;
 
 for(s=0; s<side.size(); s++)
   if(side[s].mark==0)
    {
     if(node[side[s].c].mark==0)
       node[side[s].c].Nne++;
       
     if(node[side[s].d].mark==0)
       node[side[s].d].Nne++;
    }

 return 0;
}

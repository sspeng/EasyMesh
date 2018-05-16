/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::smooth()
{
 int it, s, n, e;
 
 for(it=0; it<10; it++)
  {    
   for(s=0; s<side.size(); s++)
     if(side[s].mark==0)
      {
       if(node[side[s].c].mark==0)
	{node[side[s].c].sumx += node[side[s].d].x;
	 node[side[s].c].sumy += node[side[s].d].y;}
       
       if(node[side[s].d].mark==0)
	{node[side[s].d].sumx += node[side[s].c].x;
	 node[side[s].d].sumy += node[side[s].c].y;}
      }
    
   for(n=0; n<node.size(); n++)
     if(node[n].mark==0)
      {node[n].x=node[n].sumx/node[n].Nne; node[n].sumx=0.0;
       node[n].y=node[n].sumy/node[n].Nne; node[n].sumy=0.0;}
  }
       
 for(e=0; e<elem.size(); e++)
   if(elem[e].mark!=OFF)
     circles(e);

 return 0;
}

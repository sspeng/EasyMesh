/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::relax()
{
 int s, T, E;
 
 for(T=6; T>=3; T--)
   for(s=0; s<side.size(); s++)
     if(side[s].mark==0)
       if( (node[side[s].a].mark==0) &&
	   (node[side[s].b].mark==0) &&
	   (node[side[s].c].mark==0) &&
	   (node[side[s].d].mark==0) )
      {
       E =   node[side[s].c].Nne + node[side[s].d].Nne 
	   - node[side[s].a].Nne - node[side[s].b].Nne;

       if(E==T) 
	{node[side[s].a].Nne++; node[side[s].b].Nne++; 
	 node[side[s].c].Nne--; node[side[s].d].Nne--;  
	 swap_side(s);}
      }

 return 0;
}

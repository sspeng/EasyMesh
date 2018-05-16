/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::compress()
{
 int n, s, e;
 int new_elem=0, new_node=0, new_side=0;

 for(n=0; n<node.size(); n++) node[n].new_numb=OFF;
 for(e=0; e<elem.size(); e++) elem[e].new_numb=OFF;
 for(s=0; s<side.size(); s++) side[s].new_numb=OFF;

/*-------------------------------+
|  Searching the first element.  |
|  It is the first which is ON   |
+-------------------------------*/
 for(e=0; e<elem.size(); e++)
   if(elem[e].mark!=OFF)
     break;

/*----------------------------------------------------------+
|  Assigning numbers 0 and 1 to the nodes of first element  |
+----------------------------------------------------------*/
 node[elem[e].i].new_numb  = new_node; new_node++;
 node[elem[e].j].new_numb  = new_node; new_node++;

/*%%%%%%%%%%%%%%%%%%%%%%%%%
%                         %
%  Renumeration of nodes  %
%                         % 
%%%%%%%%%%%%%%%%%%%%%%%%%*/
 new_node=0;
 for(n=0; n<node.size(); n++)
  {
   if(node[n].mark!=OFF)
    {
     node[n].new_numb=new_node;
     new_node++;
    }
  }

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                             %
%  Renumeration of triangles  %
%                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
 new_elem=0;
 for(e=0; e<elem.size(); e++)
  {
   if(elem[e].mark!=OFF)
    {
     elem[e].new_numb=new_elem;
     new_elem++;
    }
  }

/*%%%%%%%%%%%%%%%%%%%%%%%%%
%                         %
%  Renumeration of sides  %
%                         %
%%%%%%%%%%%%%%%%%%%%%%%%%*/
 new_side=0;
 for(s=0; s<side.size(); s++)
  {
   if(side[s].mark!=OFF)
    {
     side[s].new_numb=new_side;
     new_side++;
    }
  }
 return 0;
}

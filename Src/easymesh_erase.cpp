/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
void EasyMesh::erase(int ins)
{
 int s, n, e;

 int a, b, c;

/*======================================+
|  If EasyMesh was used for mesh gene-  |
|  ration  with insertion of new nodes  |
+======================================*/
 if(ins==ON)
  { 
/*--------------------------+
|  Negative area check for  |
|  elimination of elements  |
+--------------------------*/
   for(e=0; e<elem.size(); e++)
     if( (node[elem[e].i].chain==node[elem[e].j].chain) &&
         (node[elem[e].j].chain==node[elem[e].k].chain) &&
         ( (chain[node[elem[e].i].chain].area<0.0) &&
	   (node[elem[e].i].chain>0) || (node[elem[e].i].chain==0) ) &&
         (chain[node[elem[e].i].chain].type==CLOSED) )
      {
       a = std::min( std::min(elem[e].i, elem[e].j), elem[e].k );
       c = std::max( std::max(elem[e].i, elem[e].j), elem[e].k );
       b = elem[e].i+elem[e].j+elem[e].k - a - c;

       if(a<3)
         elem[e].mark=OFF;

       else if(area(&node[a], &node[b], &node[c]) < 0.0)
         elem[e].mark=OFF;
      }

   for(e=0; e<elem.size(); e++)
    {  
     if(elem[e].ei!=OFF)
       if(elem[elem[e].ei].mark==OFF) elem[e].ei=OFF;

     if(elem[e].ej!=OFF)
       if(elem[elem[e].ej].mark==OFF) elem[e].ej=OFF;

     if(elem[e].ek!=OFF)
       if(elem[elem[e].ek].mark==OFF) elem[e].ek=OFF;
    }

/*-----------------------+
|  Elimination of sides  |
+-----------------------*/
   for(s=0; s< 3; s++)
     side[s].mark=OFF;

   for(s=3; s<side.size(); s++)
     if( (elem[side[s].ea].mark==OFF) && (elem[side[s].eb].mark==OFF) )
       side[s].mark=OFF;

   for(s=3; s<side.size(); s++)
     if(side[s].mark!=OFF)
      {
       if(elem[side[s].ea].mark==OFF) {side[s].ea=OFF; side[s].a=OFF;}
       if(elem[side[s].eb].mark==OFF) {side[s].eb=OFF; side[s].b=OFF;}
      }

/*-----------------------+
|  Elimination of nodes  |
+-----------------------*/
   for(n=0; n< 3; n++)
     node[n].mark=OFF;
  }
/*===================================+
|  If EasyMesh was used for just to  |
|  craete Delaunay and Voronoi mesh  |
|    of an existing set of points    |
+===================================*/
 else if(ins==OFF)
  {
/*--------------------------+
|  Elimination of elements  |
+--------------------------*/
   for(e=0; e<elem.size(); e++)
     if( elem[e].i < 3 || elem[e].j < 3 || elem[e].k < 3 )  
       elem[e].mark=OFF;

   for(e=0; e<elem.size(); e++)
    {if(elem[elem[e].ei].mark==OFF) elem[e].ei=OFF;
     if(elem[elem[e].ej].mark==OFF) elem[e].ej=OFF;
     if(elem[elem[e].ek].mark==OFF) elem[e].ek=OFF;}

/*-----------------------+
|  Elimination of sides  |
+-----------------------*/
   for(s=0; s< 3; s++)
     side[s].mark=OFF;

   for(s=3; s<side.size(); s++)
     if( (elem[side[s].ea].mark==OFF) && (elem[side[s].eb].mark==OFF) )
       side[s].mark=OFF;

   for(s=3; s<side.size(); s++)
     if(side[s].mark!=OFF)
      {
       if(elem[side[s].ea].mark==OFF) {side[s].ea=OFF; side[s].a=OFF;}
       if(elem[side[s].eb].mark==OFF) {side[s].eb=OFF; side[s].b=OFF;}
      }

/*-----------------------+
|  Elimination of nodes  |
+-----------------------*/
   for(n=0; n< 3; n++)
     node[n].mark=OFF;
  }

}

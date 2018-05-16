/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
real dist(const Node *na, const Node *nb)
{
 return sqrt(   ((*nb).x-(*na).x)*((*nb).x-(*na).x)
	      + ((*nb).y-(*na).y)*((*nb).y-(*na).y) );
}

/*==========================================================================*/
int EasyMesh::bowyer(int n)
{
 int e, s, swap;
 Node vor;

 do  
  { 
   swap=0;
   for(s=0; s<side.size(); s++)
   if(side[s].mark==0)
/* if( !( (node[side[s].c].inserted>1 && node[side[s].d].bound==OFF 
          && side[s].s<(node[side[s].c].F+node[side[s].d].F) ) ||
	  (node[side[s].d].inserted>1 && node[side[s].c].bound==OFF 
          && side[s].s<(node[side[s].c].F+node[side[s].d].F) ) ) ) */
    {
     if(side[s].a==n)
      {e=side[s].eb; 
       if(e!=OFF)
	{vor.x=elem[e].xv; 
	 vor.y=elem[e].yv;
	 if( dist(&vor, &node[n]) < elem[e].R )
	  {swap_side(s); swap=1;}}}
   
     else if(side[s].b==n)
      {e=side[s].ea; 
       if(e!=OFF)
	{vor.x=elem[e].xv; 
	 vor.y=elem[e].yv;
	 if( dist(&vor, &node[n]) < elem[e].R )
	  {swap_side(s); swap=1;}}}
    }
  }
 while(swap==1);

 return 0;
}

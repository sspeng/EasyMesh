/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::new_node()
/*---------------------------------------------------+
|  This function is very important.                  |
|  It determines the position of the inserted node.  |
+---------------------------------------------------*/
/*-------------------------------------------+ 
|  This function is taken from version 1.5d  | 
+-------------------------------------------*/
{
 easy::timer.start("new_node");

 int  n;
 real xM, yM, p, q, qx, qy, rhoM, rho_M, d;

 Node Ca;

/*-------------------------------------------------------------------------+
|  It's obvious that elements which are near the boundary, will come into  |
|  play first.                                                             |
|                                                                          |
|  However, some attention has to be payed for the case when two accepted  |
|  elements surround the ugly one                                          |
|                                                                          |
|  What if new points falls outside the domain                             |
+-------------------------------------------------------------------------*/
 int s=OFF;

 if(elem[ugly].ei!=OFF) 
 if(elem[elem[ugly].ei].state==DONE)   {s=elem[ugly].si; n=elem[ugly].i;}

 if(elem[ugly].ej!=OFF) 
 if(elem[elem[ugly].ej].state==DONE)   {s=elem[ugly].sj; n=elem[ugly].j;}

 if(elem[ugly].ek!=OFF) 
 if(elem[elem[ugly].ek].state==DONE)   {s=elem[ugly].sk; n=elem[ugly].k;}

 if(side[elem[ugly].si].mark > 0)      {s=elem[ugly].si; n=elem[ugly].i;}

 if(side[elem[ugly].sj].mark > 0)      {s=elem[ugly].sj; n=elem[ugly].j;}

 if(side[elem[ugly].sk].mark > 0)      {s=elem[ugly].sk; n=elem[ugly].k;}

 if(s==OFF) return -1;

 xM  = 0.5*(node[side[s].c].x + node[side[s].d].x);
 yM  = 0.5*(node[side[s].c].y + node[side[s].d].y);

 Ca.x = elem[ugly].xv;
 Ca.y = elem[ugly].yv;

 p  = 0.5*side[s].s;    /* not checked */

 qx = Ca.x-xM;
 qy = Ca.y-yM;
 q  = sqrt(qx*qx+qy*qy);

 rhoM = 0.577 *  0.5*(node[side[s].c].F + node[side[s].d].F);

 rho_M = std::min( std::max( rhoM, p), 0.5*(p*p+q*q)/q );

 if(rho_M < p) d=rho_M;
 else          d=rho_M+sqrt(rho_M*rho_M-p*p); 

/*---------------------------------------------------------------------+
|  The following line check can the new point fall outside the domain. |
|  However, I can't remember how it works, but I believe that it is    |
|  still a weak point of the code, particulary when there are lines    |
|  inside the domain                                                   |
+---------------------------------------------------------------------*/

 if( area(&node[side[s].c], &node[side[s].d], &Ca) *
     area(&node[side[s].c], &node[side[s].d], &node[n]) > 0.0 )
   insert_node(xM + d*qx/q,  yM + d*qy/q, ON, OFF, 0, 0, 0, OFF);
/*
 else
  {
   node[n].x = xM - d*qx/q;
   node[n].y = yM - d*qy/q;
   node[n].mark=6;   
   for(e=0; e<elem.size(); e++) 
     if(elem[e].i==n || elem[e].j==n || elem[e].k==n)
       circles(e);
  }
*/

 easy::timer.stop("new_node");

 return 0;
}

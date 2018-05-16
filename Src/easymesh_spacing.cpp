/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::spacing(int e, int n)
/*----------------------------------------------------------------+
|  This function calculates the value of the spacing function in  |
|  a new node 'n' which is inserted in element 'e' by a linear    |
|  approximation from the values of the spacing function in the   |
|  elements nodes.                                                |
+----------------------------------------------------------------*/
{
 real dxji, dxki, dyji, dyki, dx_i, dy_i, det, a, b;

 dxji = node[elem[e].j].x - node[elem[e].i].x;
 dyji = node[elem[e].j].y - node[elem[e].i].y;
 dxki = node[elem[e].k].x - node[elem[e].i].x;
 dyki = node[elem[e].k].y - node[elem[e].i].y;
 dx_i = node[n].x - node[elem[e].i].x;
 dy_i = node[n].y - node[elem[e].i].y;

 det = dxji*dyki - dxki*dyji;

 a = (+ dyki*dx_i - dxki*dy_i)/det;
 b = (- dyji*dx_i + dxji*dy_i)/det;

 node[n].F = node[elem[e].i].F + 
	     a*(node[elem[e].j].F - node[elem[e].i].F) +
	     b*(node[elem[e].k].F - node[elem[e].i].F);

 return 0;
}

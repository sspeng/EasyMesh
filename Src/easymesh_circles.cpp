/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::circles(int e)
/*---------------------------------------------------+
|  This function calculates radii of inscribed and   |
|  circumscribed circle for a given element (int e)  |
+---------------------------------------------------*/
{
 real x, y, xi, yi, xj, yj, xk, yk, xij, yij, xjk, yjk, num, den;
 real si, sj, sk, O;

 xi=node[elem[e].i].x; yi=node[elem[e].i].y;
 xj=node[elem[e].j].x; yj=node[elem[e].j].y;
 xk=node[elem[e].k].x; yk=node[elem[e].k].y;
   
 xij=0.5*(xi+xj); yij=0.5*(yi+yj);
 xjk=0.5*(xj+xk); yjk=0.5*(yj+yk);

 num = (xij-xjk)*(xj-xi) + (yij-yjk)*(yj-yi);
 den = (xj -xi) *(yk-yj) - (xk -xj) *(yj-yi);

 if(den>0)
  {
   elem[e].xv = x = xjk + num/den*(yk-yj);
   elem[e].yv = y = yjk - num/den*(xk-xj);

   elem[e].R  = sqrt( (xi-x)*(xi-x) + (yi-y)*(yi-y) );
  }

 si=side[elem[e].si].s;
 sj=side[elem[e].sj].s;
 sk=side[elem[e].sk].s;
 O =si+sj+sk;
 elem[e].Det = xi*(yj-yk) - xj*(yi-yk) + xk*(yi-yj);

 elem[e].xin = ( xi*si + xj*sj + xk*sk ) / O;
 elem[e].yin = ( yi*si + yj*sj + yk*sk ) / O;

 elem[e].r   = elem[e].Det / O;

 return 0;
}

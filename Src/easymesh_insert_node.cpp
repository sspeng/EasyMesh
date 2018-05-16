/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::insert_node(real x, real y, int spac,
	 int prev_n, int prev_s_mark, int mark, int next_s_mark, int next_n)
{
 int    i,j,k, e,ei,ej,ek, s,si,sj,sk;
 real sx, sy;

 node.increase_size(1); /* one new node */
 
 node[node.size()-1].x = x;
 node[node.size()-1].y = y;
 node[node.size()-1].mark = mark;

/* find the element which contains new node */ 
 e = in_elem(&node[node.size()-1]);

/* calculate the spacing function in the new node */
 if(spac==ON)
   spacing(e, node.size()-1);

 i =elem[e].i;  j =elem[e].j;  k =elem[e].k;
 ei=elem[e].ei; ej=elem[e].ej; ek=elem[e].ek; 
 si=elem[e].si; sj=elem[e].sj; sk=elem[e].sk; 
 
 elem.increase_size(2);
 side.increase_size(3);

/*---------------+
|  new elements  |
+---------------*/ 
 elem[elem.size()-2].i=node.size()-1;  
 elem[elem.size()-2].j=k;     
 elem[elem.size()-2].k=i;

 elem[elem.size()-1].i=node.size()-1;  
 elem[elem.size()-1].j=i;     
 elem[elem.size()-1].k=j; 
 
 elem[elem.size()-2].ei=ej;   
 elem[elem.size()-2].ej=elem.size()-1; 
 elem[elem.size()-2].ek=e;

 elem[elem.size()-1].ei=ek;   
 elem[elem.size()-1].ej=e;    
 elem[elem.size()-1].ek=elem.size()-2;
 
 elem[elem.size()-2].si=sj;   
 elem[elem.size()-2].sj=side.size()-2; 
 elem[elem.size()-2].sk=side.size()-3;

 elem[elem.size()-1].si=sk;   
 elem[elem.size()-1].sj=side.size()-1; 
 elem[elem.size()-1].sk=side.size()-2;
 
 elem[elem.size()-2].state=WAITING;
 elem[elem.size()-1].state=WAITING;
 elem[e].state            =WAITING;
 
/*------------+ 
|  new sides  |
+------------*/ 
 side[side.size()-3].c =k;    side[side.size()-3].d =node.size()-1; /* c-d */
 side[side.size()-3].a =j;    side[side.size()-3].b =i;             /* a-b */
 side[side.size()-3].ea=e;    side[side.size()-3].eb=elem.size()-2;
 
 side[side.size()-2].c =i;    side[side.size()-2].d =node.size()-1; /* c-d */
 side[side.size()-2].a =k;    side[side.size()-2].b =j;             /* a-b */
 side[side.size()-2].ea=elem.size()-2; side[side.size()-2].eb=elem.size()-1;
 
 side[side.size()-1].c =j;    side[side.size()-1].d =node.size()-1; /* c-d */
 side[side.size()-1].a =i;    side[side.size()-1].b =k;             /* a-b */
 side[side.size()-1].ea=elem.size()-1; side[side.size()-1].eb=e;       

 for(s=1; s<=3; s++)
  {sx = node[side[side.size()-s].c].x - node[side[side.size()-s].d].x;
   sy = node[side[side.size()-s].c].y - node[side[side.size()-s].d].y;
   side[side.size()-s].s = sqrt(sx*sx+sy*sy);}

 elem[e].i  = node.size()-1;
 elem[e].ej = elem.size()-2;
 elem[e].ek = elem.size()-1;
 elem[e].sj = side.size()-3;
 elem[e].sk = side.size()-1;

 if(side[si].a==i) {side[si].a=node.size()-1; side[si].ea=e;}
 if(side[si].b==i) {side[si].b=node.size()-1; side[si].eb=e;}
 
 if(side[sj].a==j) {side[sj].a=node.size()-1; side[sj].ea=elem.size()-2;}
 if(side[sj].b==j) {side[sj].b=node.size()-1; side[sj].eb=elem.size()-2;}
 
 if(side[sk].a==k) {side[sk].a=node.size()-1; side[sk].ea=elem.size()-1;} 
 if(side[sk].b==k) {side[sk].b=node.size()-1; side[sk].eb=elem.size()-1;} 

 if(ej!=-1)
  {if(elem[ej].ei==e) {elem[ej].ei=elem.size()-2;}
   if(elem[ej].ej==e) {elem[ej].ej=elem.size()-2;}
   if(elem[ej].ek==e) {elem[ej].ek=elem.size()-2;}}

 if(ek!=-1)
  {if(elem[ek].ei==e) {elem[ek].ei=elem.size()-1;}
   if(elem[ek].ej==e) {elem[ek].ej=elem.size()-1;}
   if(elem[ek].ek==e) {elem[ek].ek=elem.size()-1;}}

/* Find circumenters for two new elements, 
   and for the one who's segment has changed */
 circles(e);
 circles(elem.size()-2);
 circles(elem.size()-1);

 bowyer(node.size()-1);

/*-------------------------------------------------+
|  NEW ! Insert boundary conditions for the sides  |
+-------------------------------------------------*/
 for(s=3; s<side.size(); s++)
  {
   if(side[s].c==prev_n && side[s].d==node.size()-1) {side[s].mark=prev_s_mark;}
   if(side[s].d==prev_n && side[s].c==node.size()-1) {side[s].mark=prev_s_mark;}
   if(side[s].c==next_n && side[s].d==node.size()-1) {side[s].mark=next_s_mark;}
   if(side[s].d==next_n && side[s].c==node.size()-1) {side[s].mark=next_s_mark;}
  }

 return e;
}

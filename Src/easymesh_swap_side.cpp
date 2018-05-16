/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::swap_side(int s)
{
 int    a, b, c, d, ea, eb, eac, ead, ebc, ebd, sad, sac, sbc, sbd;
 real sx, sy;
 
 ea=side[s].ea; 
 eb=side[s].eb;
 a=side[s].a; b=side[s].b; c=side[s].c; d=side[s].d;

 if(elem[ea].ei==eb) {ead=elem[ea].ej; eac=elem[ea].ek; 
		      sad=elem[ea].sj; sac=elem[ea].sk;}
 
 if(elem[ea].ej==eb) {ead=elem[ea].ek; eac=elem[ea].ei; 
		      sad=elem[ea].sk; sac=elem[ea].si;}   
 
 if(elem[ea].ek==eb) {ead=elem[ea].ei; eac=elem[ea].ej;
		      sad=elem[ea].si; sac=elem[ea].sj;}

 if(elem[eb].ei==ea) {ebc=elem[eb].ej; ebd=elem[eb].ek;
		      sbc=elem[eb].sj; sbd=elem[eb].sk;}

 if(elem[eb].ej==ea) {ebc=elem[eb].ek; ebd=elem[eb].ei;
		      sbc=elem[eb].sk; sbd=elem[eb].si;}
 
 if(elem[eb].ek==ea) {ebc=elem[eb].ei; ebd=elem[eb].ej;
		      sbc=elem[eb].si; sbd=elem[eb].sj;}

 elem[ea].i =a;   elem[ea].j =b;   elem[ea].k =d;  
 elem[ea].ei=ebd; elem[ea].ej=ead; elem[ea].ek=eb;  
 elem[ea].si=sbd; elem[ea].sj=sad; elem[ea].sk=s;  
  
 elem[eb].i =a;   elem[eb].j =c;   elem[eb].k =b;  
 elem[eb].ei=ebc; elem[eb].ej=ea;  elem[eb].ek=eac;  
 elem[eb].si=sbc; elem[eb].sj=s;   elem[eb].sk=sac;  

 if(eac!=-1)
  {
   if(elem[eac].ei==ea) elem[eac].ei=eb;
   if(elem[eac].ej==ea) elem[eac].ej=eb;
   if(elem[eac].ek==ea) elem[eac].ek=eb; 
  }
 
 if(ebd!=-1)
  {
   if(elem[ebd].ei==eb) elem[ebd].ei=ea;
   if(elem[ebd].ej==eb) elem[ebd].ej=ea;
   if(elem[ebd].ek==eb) elem[ebd].ek=ea; 
  }
 
 if(side[sad].ea==ea) {side[sad].a=b;}
 if(side[sad].eb==ea) {side[sad].b=b;}

 if(side[sbc].ea==eb) {side[sbc].a=a;}
 if(side[sbc].eb==eb) {side[sbc].b=a;}

 if(side[sbd].ea==eb) {side[sbd].ea=ea; side[sbd].a=a;}
 if(side[sbd].eb==eb) {side[sbd].eb=ea; side[sbd].b=a;}
 
 if(a<b)
  {side[s].c=a; side[s].d=b; side[s].a=d; side[s].b=c;
   side[s].ea=ea; side[s].eb=eb;}
 else 
  {side[s].c=b; side[s].d=a; side[s].a=c; side[s].b=d;
   side[s].ea=eb; side[s].eb=ea;}

 sx = node[side[s].c].x - node[side[s].d].x;
 sy = node[side[s].c].y - node[side[s].d].y;
 side[s].s = sqrt(sx*sx+sy*sy);

 if(side[sac].ea==ea) {side[sac].ea=eb; side[sac].a=b;}
 if(side[sac].eb==ea) {side[sac].eb=eb; side[sac].b=b;}
 
 if(side[sad].ea==ea) {side[sad].a=b;}
 if(side[sad].eb==ea) {side[sad].b=b;}

 if(side[sbc].ea==eb) {side[sbc].a=a;}
 if(side[sbc].eb==eb) {side[sbc].b=a;}

 if(side[sbd].ea==eb) {side[sbd].ea=ea; side[sbd].a=a;}
 if(side[sbd].eb==eb) {side[sbd].eb=ea; side[sbd].b=a;}

 circles(ea);
 circles(eb);

 return 0;
}

/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::classify()
/*----------------------------------------------------------+
|  This function searches through all elements every time.  |
|  Some optimization will definitely bee needed             |
|                                                           |
|  But it also must me noted, that this function defines    |
|  the strategy for insertion of new nodes                  |
|                                                           |
|  It's MUCH MUCH better when the ugliest element is found  |
|  as one with highest ratio of R/r !!! (before it was      |
|  element with greater R)                                  |
+----------------------------------------------------------*/
{

 int e, ei, ej, ek,si,sj,sk;
 real ratio=-GREAT, F;

 ugly=OFF;

 easy::timer.start("classify 1");
 for(e=0; e<elem.size(); e++)
   if(elem[e].mark!=OFF && elem[e].state!=DONE)
    {
     ei=elem[e].ei; ej=elem[e].ej; ek=elem[e].ek;

     F=(node[elem[e].i].F + node[elem[e].j].F + node[elem[e].k].F)/3.0;

     elem[e].state=WAITING;

/*--------------------------+
|  0.577 is ideal triangle  |
+--------------------------*/
     if(elem[e].R < R_tol*F) elem[e].state=DONE; 

/*------------------------+
|  even this is possible  |
+------------------------*/
     if(ei!=OFF && ej!=OFF && ek!=OFF)
       if(elem[ei].state==DONE && elem[ej].state==DONE && elem[ek].state==DONE)
	 elem[e].state=DONE;
    }
 easy::timer.stop("classify 1");

/*--------------------------------------+
|  Diamond check. Is it so important ?  |
+--------------------------------------*/
 easy::timer.start("classify d");
 diamond();   
 easy::timer.stop("classify d");

/*------------------------------------------------+
|  First part of the trick:                       |
|    search through the elements on the boundary  |
+------------------------------------------------*/
 easy::timer.start("classify 2");
 for(e=0; e<elem.size(); e++)
   if(elem[e].mark!=OFF && elem[e].state!=DONE)
    {
     si=elem[e].si; sj=elem[e].sj; sk=elem[e].sk;

     if(side[si].mark!=0) elem[e].state=ACTIVE;
     if(side[sj].mark!=0) elem[e].state=ACTIVE;
     if(side[sk].mark!=0) elem[e].state=ACTIVE;
  
     if(elem[e].state==ACTIVE && elem[e].R/elem[e].r > ratio)
      {ratio=std::max(ratio, elem[e].R/elem[e].r);
       ugly=e;}
    }
 easy::timer.stop("classify 2");

/*-------------------------------------------------+
|  Second part of the trick:                       |
|    if non-acceptable element on the boundary is  |
|    found, ignore the elements inside the domain  |
+-------------------------------------------------*/
 easy::timer.start("classify 3");
 if(ugly==OFF)
   for(e=0; e<elem.size(); e++)
     if(elem[e].mark!=OFF)
      {
       if(elem[e].state!=DONE)
	{
	 ei=elem[e].ei; ej=elem[e].ej; ek=elem[e].ek;

	if(ei!=OFF) if(elem[ei].state==DONE) elem[e].state=ACTIVE;
  
	if(ej!=OFF) if(elem[ej].state==DONE) elem[e].state=ACTIVE;
  
	if(ek!=OFF) if(elem[ek].state==DONE) elem[e].state=ACTIVE;
  
	if(elem[e].state==ACTIVE && elem[e].R/elem[e].r > ratio)
	 {ratio=std::max(ratio, elem[e].R/elem[e].r);
	  ugly=e;}
	}
      }
 easy::timer.stop("classify 3");

 return 0;
}

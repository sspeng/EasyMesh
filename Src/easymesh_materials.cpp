/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::materials()
{
 int e, c, mater, over;
 int ei, ej, ek, si, sj, sk;

 for(e=0; e<elem.size(); e++)
   if(elem[e].mark!=OFF)   
     elem[e].material=OFF;

 for(c=0; c<Nc; c++)
  {
   if(point[c].inserted==0)
    {
     elem[in_elem(&point[c])].material=point[c].mark;
     mater=ON;
    }
  }

 if(mater==ON)
  {
   for(;;) 
    {      
     over=ON;

     for(e=0; e<elem.size(); e++)
       if(elem[e].mark!=OFF && elem[e].material==OFF)
	{
	 ei=elem[e].ei;
	 ej=elem[e].ej;
	 ek=elem[e].ek;

	 si=elem[e].si;
	 sj=elem[e].sj;
	 sk=elem[e].sk;

   
	 if(ei!=OFF)
	   if(elem[ei].material!=OFF && side[si].mark==0)
	    {
	     elem[e].material=elem[ei].material;
	     over=OFF;
	    }

	 if(ej!=OFF)
	   if(elem[ej].material!=OFF && side[sj].mark==0)
	    {
	     elem[e].material=elem[ej].material;
	     over=OFF;
	    }

	 if(ek!=OFF)
	   if(elem[ek].material!=OFF && side[sk].mark==0)
	    {
	     elem[e].material=elem[ek].material;
	     over=OFF;
	    }

	}

     if(over==ON) break;

    } /* for(iter) */

  }

 return 0;
}

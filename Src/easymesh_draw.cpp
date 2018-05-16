/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"
#include "draw_eps.h"

/*==========================================================================*/
int EasyMesh::draw_file(int eps, int epsDel, int epsVor)
/*-----------------------------------------------------------------+
|   eps: Let's say that drawing area is a4.                        |
|        In Postscript it means 595 x 842 points.                  |
+-----------------------------------------------------------------*/
{
 int  ea, eb;
 real xc, yc, xd, yd, xa, ya, xb, yb,
      xmax=-GREAT, xmin=+GREAT, ymax=-GREAT, ymin=+GREAT, scl_f, scl_p;
 
/*----------------+
|  Open the file  |
+----------------*/
 if(eps==ON) start_eps(eps_name); 

/*--------------------+
|  Compute the scale  |
+--------------------*/
 for(int n=0; n<node.size(); n++)
   if(node[n].mark!=OFF)
    {
     xmin=std::min(xmin, node[n].x); 
     ymin=std::min(ymin, node[n].y);
     xmax=std::max(xmax, node[n].x); 
     ymax=std::max(ymax, node[n].y);
    }
 scl_p =std::min( 822.0/(ymax-ymin+SMALL), 575.0/(xmax-xmin+SMALL) );

#if DEBUG == ON
/*----------------+
|  Draw elements  |
+----------------*/
 for(int e=0; e<elem.size(); e++)
   if(elem[e].mark!=OFF)
    {
     xa=node[elem[e].i].x;  ya=node[elem[e].i].y;  
     xb=node[elem[e].j].x;  yb=node[elem[e].j].y;  
     xc=node[elem[e].k].x;  yc=node[elem[e].k].y;  

     if(eps==ON) 
      { 
       if(elem[e].state == DONE)  
         solid_eps( (scl_p*xa), (scl_p*ya), 
                    (scl_p*xb), (scl_p*yb), 
                    (scl_p*xc), (scl_p*yc), 
                    0, 0, 2, 0.000);
       if(elem[e].state == ACTIVE)  
         solid_eps( (scl_p*xa), (scl_p*ya), 
                    (scl_p*xb), (scl_p*yb), 
                    (scl_p*xc), (scl_p*yc), 
                    0, 0, 5, 0.000);
       if(elem[e].state == WAITING)  
         solid_eps( (scl_p*xa), (scl_p*ya), 
                    (scl_p*xb), (scl_p*yb), 
                    (scl_p*xc), (scl_p*yc), 
                    0, 0, 3, 0.000);
       if(e==ugly)  
         solid_eps( (scl_p*xa), (scl_p*ya), 
                    (scl_p*xb), (scl_p*yb), 
                    (scl_p*xc), (scl_p*yc), 
                    0, 0, 6, 0.000);
      }
    }
#endif

/*----------------+
|  Draw boundary  |
+----------------*/
 for(int s=0; s<side.size(); s++)
   if(side[s].mark>0) /* It means, side is on the boundary */
    {
     xc=node[side[s].c].x; yc=node[side[s].c].y;
     xd=node[side[s].d].x; yd=node[side[s].d].y;

     if(eps==ON) 
       line_eps( (scl_p*xc), (scl_p*yc), 
	         (scl_p*xd), (scl_p*yd), 
	         0, 1, 0, 0.000);
    }
 
/*----------------+
|  Draw Delaunay  |
+----------------*/
 for(int s=0; s<side.size(); s++)
   if(side[s].mark==0) /* It means: side is in the domain */
    {
     xc=node[side[s].c].x; yc=node[side[s].c].y;
     xd=node[side[s].d].x; yd=node[side[s].d].y;

     if(eps==ON && epsDel==ON) 
       line_eps( (scl_p*xc), (scl_p*yc), 
	         (scl_p*xd), (scl_p*yd),
	         0, 0, 1, 0.000); /* style, width, color, le */
    }

/*---------------+
|  Draw Voronoi  |
+---------------*/
 for(int s=0; s<side.size(); s++)
   if(side[s].mark!=OFF)
    {
     if((ea=side[s].ea)!=OFF)
      {xa=elem[ea].xv;
       ya=elem[ea].yv;}
     else
      {xa=0.5*(node[side[s].c].x+node[side[s].d].x);
       ya=0.5*(node[side[s].c].y+node[side[s].d].y);}
     
     if((eb=side[s].eb)!=OFF)
      {xb=elem[eb].xv;
       yb=elem[eb].yv;}
     else
      {xb=0.5*(node[side[s].c].x+node[side[s].d].x);
       yb=0.5*(node[side[s].c].y+node[side[s].d].y);}
     
     if(eps==ON && epsVor==ON) 
       line_eps( (scl_p*xa), (scl_p*ya), 
	         (scl_p*xb), (scl_p*yb),
	         1, 0, 4, 2.000); /* style, width, color, le */
    }

/*-----------------+
|  Close the file  |
+-----------------*/
 if(eps==ON) end_eps(); 

 return 0;
}

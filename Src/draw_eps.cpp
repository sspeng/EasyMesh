/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "draw_eps.h"

using namespace std;

FILE *eps_file;

real xmin=INT_MAX;
real xmax=INT_MIN;
real ymin=INT_MAX;
real ymax=INT_MIN;

/*==========================================================================*/
int start_eps(const char * eps_name)
{
 if((eps_file=fopen(eps_name,"w"))==NULL)
  {
   printf("A file '%s' cannot be opened for output ! \n\n", eps_name);
   return 1;
  }
 else
  {
   fprintf(eps_file, "%%!PS-Adobe-2.0 EPSF-1.2\n");
   fprintf(eps_file, "%%%%Created by EasyMesh 2.3\n"); 
   fprintf(eps_file, "%%%%File: %s\n",eps_name); 
   fprintf(eps_file, "%%%%BoundingBox: (atend)\n");
   fprintf(eps_file, "save\n");
   fprintf(eps_file, "countdictstack\n");
   fprintf(eps_file, "mark\n");
   fprintf(eps_file, "newpath\n");

   fprintf(eps_file, "/cp   {closepath}    bind def\n");
   fprintf(eps_file, "/f    {fill}         bind def\n");
   fprintf(eps_file, "/l    {lineto}       bind def\n");
   fprintf(eps_file, "/m    {moveto}       bind def\n");
   fprintf(eps_file, "/s    {stroke}       bind def\n");
   fprintf(eps_file, "/srgb {setrgbcolor}  bind def\n");
   fprintf(eps_file, "/slw  {setlinewidth} bind def\n");
   fprintf(eps_file, "/sds  {setdash}      bind def\n");
  }

 return 0;
}

/*==========================================================================*/
int line_eps(real x1, real y1, 
	     real x2, real y2, 
             int style, int width, int color, float le)
{
 xmax = std::max(x1,xmax);
 xmin = std::min(x1,xmin);
 xmax = std::max(x2,xmax);
 xmin = std::min(x2,xmin);
 ymax = std::max(y1,ymax);
 ymin = std::min(y1,ymin);
 ymax = std::max(y2,ymax);
 ymin = std::min(y2,ymin);

 fprintf(eps_file, "%2d slw ", width);
 if(color==0) /* 0) -> 0 0 0 -> black */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 0.0, 0.0, 0.0);
 if(color==1) /* 1) -> 0 0 1 -> blue */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 0.0, 0.0, 1.0);
 if(color==2) /* 2) -> 0 1 0 -> green */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 0.0, 1.0, 0.0);
 if(color==3) /* 3) -> 0 1 1 -> cyan */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 0.0, 1.0, 1.0);
 if(color==4) /* 4) -> 1 0 0 -> red */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 1.0, 0.0, 0.0);
 if(color==5) /* 5) -> 1 0 1 -> magenta */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 1.0, 0.0, 1.0);
 if(color==6) /* 6) -> 1 1 0 -> brown */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 1.0, 1.0, 0.0);
 if(color==7) /* 7) -> 1 1 1 -> white */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 1.0, 1.0, 1.0);
 if(style==1) fprintf(eps_file, "[%f] 0 sds ", le);
 fprintf(eps_file, "%12.5f %12.5f m ", x1, y1);
 fprintf(eps_file, "%12.5f %12.5f l ", x2, y2);
 fprintf(eps_file, "s "); 
 if(style==1) fprintf(eps_file, "[] 0 sds ");
 fprintf(eps_file, "\n"); 

 /* style :  0 - solid, 1 - dashed, 2 - dotted */
 /* le    :  lenght for dashes                 */ 

 return 0;
}

/*==========================================================================*/
int solid_eps(real x1, real y1, 
	      real x2, real y2, 
	      real x3, real y3, 
              int style, int width, int color, float le)
{
 xmax = std::max(x1,xmax);
 xmin = std::min(x1,xmin);
 xmax = std::max(x2,xmax);
 xmin = std::min(x2,xmin);
 xmax = std::max(x3,xmax);
 xmin = std::min(x3,xmin);
 ymax = std::max(y1,ymax);
 ymin = std::min(y1,ymin);
 ymax = std::max(y2,ymax);
 ymin = std::min(y2,ymin);
 ymax = std::max(y3,ymax);
 ymin = std::min(y3,ymin);

 fprintf(eps_file, "%2d slw ", width);
 
 fprintf(eps_file, "%12.5f %12.5f m ", x1, y1);
 fprintf(eps_file, "%12.5f %12.5f l ", x2, y2);
 fprintf(eps_file, "%12.5f %12.5f l ", x3, y3);
 fprintf(eps_file, "cp ");

 if(color==0) /* 0) -> 0 0 0 -> black */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 0.0, 0.0, 0.0);
 if(color==1) /* 1) -> 0 0 1 -> blue */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 0.0, 0.0, 1.0);
 if(color==2) /* 2) -> 0 1 0 -> green */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 0.0, 1.0, 0.0);
 if(color==3) /* 3) -> 0 1 1 -> cyan */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 0.0, 1.0, 1.0);
 if(color==4) /* 4) -> 1 0 0 -> red */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 1.0, 0.0, 0.0);
 if(color==5) /* 5) -> 1 0 1 -> magenta */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 1.0, 0.0, 1.0);
 if(color==6) /* 6) -> 1 1 0 -> brown */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 1.0, 1.0, 0.0);
 if(color==7) /* 7) -> 1 1 1 -> white */
   fprintf(eps_file, "%4.2f %4.2f %4.2f srgb ", 1.0, 1.0, 1.0);

 fprintf(eps_file, "f ");
 fprintf(eps_file, "s\n"); 

 /* style :  0 - solid, 1 - dashed, 2 - dotted */
 /* le    :  lenght for dashes                 */ 

 return 0;
}

/*==========================================================================*/
int end_eps()
{
 fprintf(eps_file, "%%%%Trailer\n");
 fprintf(eps_file, "%%%%BoundingBox: %12.5f %12.5f %12.5f %12.5f\n", 
                                     xmin-5, ymin-5, xmax+5, ymax+5);
 fprintf(eps_file, "%%%%EOF\n");
 fclose(eps_file);
 return 0;
}


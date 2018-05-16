/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

#include "easymesh.h"

using namespace std;

/*==========================================================================*/
void EasyMesh::examples()
{
  FILE *out1, *out2;
  if( (out1=fopen("example_1.d", "w"))==NULL )
   {printf("Can't open file 'example_1.d' for output !");
    return;}
  if( (out2=fopen("example_2.d", "w"))==NULL )
   {printf("Can't open file 'example_2.d' for output !");
    return;}
  else
  {
    /* example 1 */
    fprintf(out1, "\n#*******************************************************");
    fprintf(out1, "\n");
    fprintf(out1, "\n  Everything enclosed inside the cashes is a comment.");   
    fprintf(out1, "\n");
    fprintf(out1, "\n  This input file is used to generate the triangular");
    fprintf(out1, "\n  mesh over the following domain:");
    fprintf(out1, "\n");
    fprintf(out1, "\n     3--------------------2");
    fprintf(out1, "\n     |                    |");
    fprintf(out1, "\n     |    5----6          |");
    fprintf(out1, "\n     |    |    |          |");
    fprintf(out1, "\n     |    |    |     8    |");
    fprintf(out1, "\n     |    |    |          |");
    fprintf(out1, "\n     |    4----7          |");
    fprintf(out1, "\n     |                    |");
    fprintf(out1, "\n     0--------------------1");
    fprintf(out1, "\n");
    fprintf(out1, "\n");
    fprintf(out1, "\n  Run EasyMesh with the command:");
    fprintf(out1, "\n");
    fprintf(out1, "\n  > EasyMesh example_1 +fig");
    fprintf(out1, "\n ");
    fprintf(out1, "\n  if you want to see the results with xfig,");
    fprintf(out1, "\n  or with");
    fprintf(out1, "\n");
    fprintf(out1, "\n  > EasyMesh example_1 +eps");
    fprintf(out1, "\n ");
    fprintf(out1, "\n  if you want to see the results with Ghostview,");
    fprintf(out1, "\n  or with");
    fprintf(out1, "\n");
    fprintf(out1, "\n  > EasyMesh example_1 +dxf");
    fprintf(out1, "\n");
    fprintf(out1, "\n  if you want to see the results with some tool that");
    fprintf(out1, "\n  suports Autodesk(TM) DXF format");
    fprintf(out1, "\n");
    fprintf(out1, "\n*******************************************************#");
    fprintf(out1, "\n");
    fprintf(out1, "\n#*********");
    fprintf(out1, "\n  POINTS");
    fprintf(out1, "\n*********#");
    fprintf(out1, "\n9 # number of points defining the boundary #");
    fprintf(out1, "\n");
    fprintf(out1, "\n# rectangular domain #");
    fprintf(out1, "\n#-------+-----+-----+---------+--------#");
    fprintf(out1, "\n# point |  x  |  y  | spacing | marker #");
    fprintf(out1, "\n#-------+-----+-----+---------+--------#"); 
    fprintf(out1, "\n   0:     0.0   0.0    0.1        1");
    fprintf(out1, "\n   1:     4.0   0.0    0.12       2");
    fprintf(out1, "\n   2:     4.0   1.6    0.12       2");
    fprintf(out1, "\n   3:     0.0   1.6    0.1        1");
    fprintf(out1, "\n");
    fprintf(out1, "\n# square hole #");
    fprintf(out1, "\n#-------+-----+-----+---------+--------#");
    fprintf(out1, "\n# point |  x  |  y  | spacing | marker #");
    fprintf(out1, "\n#-------+-----+-----+---------+--------#"); 
    fprintf(out1, "\n   4:     0.5   0.5    0.05       3");
    fprintf(out1, "\n   5:     0.5   1.1    0.05       3");
    fprintf(out1, "\n   6:     1.1   1.1    0.08       3");
    fprintf(out1, "\n   7:     1.1   0.5    0.08       3");
    fprintf(out1, "\n# node for coarsening #");
    fprintf(out1, "\n#-------+-----+-----+---------+--------#");
    fprintf(out1, "\n# point |  x  |  y  | spacing | marker #");
    fprintf(out1, "\n#-------+-----+-----+---------+--------#"); 
    fprintf(out1, "\n   9:     2.55  0.8    0.5        0");
    fprintf(out1, "\n");
    fprintf(out1, "\n#***********");
    fprintf(out1, "\n  SEGMENTS");
    fprintf(out1, "\n***********#");
    fprintf(out1, "\n9 # number of segments #");
    fprintf(out1, "\n");
    fprintf(out1, "\n# domain #");
    fprintf(out1, "\n#---------+-----+-----+--------#");
    fprintf(out1, "\n# segment | 1st | 2nd | marker #");
    fprintf(out1, "\n#---------+-----+-----+--------#");    
    fprintf(out1, "\n     0:      0     1      1");
    fprintf(out1, "\n     1:      1     2      2");
    fprintf(out1, "\n     2:      2     3      1");
    fprintf(out1, "\n     3:      3     0      1");
    fprintf(out1, "\n");
    fprintf(out1, "\n# hole #");
    fprintf(out1, "\n#---------+-----+-----+--------#");
    fprintf(out1, "\n# segment | 1st | 2nd | marker #");
    fprintf(out1, "\n#---------+-----+-----+--------#");
    fprintf(out1, "\n     4:      4     5      3");
    fprintf(out1, "\n     5:      5     6      3");
    fprintf(out1, "\n     6:      6     7      3");
    fprintf(out1, "\n     7:      7     4      3");
    fprintf(out1, "\n# coarsening node #");
    fprintf(out1, "\n#---------+-----+-----+--------#");
    fprintf(out1, "\n# segment | 1st | 2nd | marker #");
    fprintf(out1, "\n#---------+-----+-----+--------#");
    fprintf(out1, "\n     8:      8     8      0\n");
    printf("\nThe file 'example_1.d' created !\n");
    fclose(out1);

    /* example 2 */
    fprintf(out2, "\n#*******************************************************");
    fprintf(out2, "\n");
    fprintf(out2, "\n  Everything enclosed inside the cashes is a comment.");   
    fprintf(out2, "\n");
    fprintf(out2, "\n  This input file is used to generate the triangular");
    fprintf(out2, "\n  mesh over prescribed set of points. The points in ");
    fprintf(out2, "\n  this file are generated randomly and are different"); 
    fprintf(out2, "\n  for each run.");
    fprintf(out2, "\n");
    fprintf(out2, "\n  Run EasyMesh with the command:");
    fprintf(out2, "\n");
    fprintf(out2, "\n  > EasyMesh example_2 +fig");
    fprintf(out2, "\n ");
    fprintf(out2, "\n  if you want to see the results with xfig,");
    fprintf(out2, "\n  or with");
    fprintf(out2, "\n");
    fprintf(out2, "\n  > EasyMesh example_1 +eps");
    fprintf(out2, "\n ");
    fprintf(out2, "\n  if you want to see the results with Ghostview,");
    fprintf(out2, "\n  or with");
    fprintf(out2, "\n");
    fprintf(out2, "\n  > EasyMesh example_2 +dxf");
    fprintf(out2, "\n");
    fprintf(out2, "\n  if you want to see the results with some tool that");
    fprintf(out2, "\n  suports Autodesk(TM) DXF format");
    fprintf(out2, "\n");
    fprintf(out2, "\n*******************************************************#");
    fprintf(out2, "\n");
    {
      int i, N, d;
      real   r,y;
      time_t time1;
      char   times[12];
      time(&time1);
      sprintf(times,"%12ld",time1);
      N=15+atoi(&times[10]);
      d=atoi(&times[11]);
      fprintf(out2, "\n#--------#");
      fprintf(out2, "\n# Points #");
      fprintf(out2, "\n#--------#");
      fprintf(out2, "\n%4d", N);
      for(i=1;i<N*d+1;i++)
      {
        r= 0.0 + (1.0*rand()/(RAND_MAX+1.0));
        y= 0.0 + (6.2831853*rand()/(RAND_MAX+1.0));
        if(i%d == 0)
          fprintf(out2,"\n%4d:  %10.6lf  %10.6lf  100.0  1", 
                       i/d,  1.+r*cos(y), 1.+r*sin(y));
      }
      fprintf(out2,"\n#----------#");
      fprintf(out2,"\n# Segments #");
      fprintf(out2,"\n#----------#");
      fprintf(out2,"\n0");
    }

    printf("\nThe file 'example_2.d' created !\n");
    fclose(out2);
  }
}

/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

using namespace std;

/*==========================================================================*/
int EasyMesh::save()
{
 int  e, s, n, r_Nn=0, r_Ns=0, r_Ne=0;

 Node    r_node( node.size() );
 Side    r_side( side.size() );
 Element r_elem( elem.size() );

 FILE *out;
 
 for(n=0; n<node.size(); n++)
   if(node[n].mark!=OFF && node[n].new_numb!=OFF)
    {
     r_Nn++;
     r_node[node[n].new_numb].x    = node[n].x;
     r_node[node[n].new_numb].y    = node[n].y;
     r_node[node[n].new_numb].mark = node[n].mark;
    }

 for(e=0; e<elem.size(); e++)
   if(elem[e].mark!=OFF && elem[e].new_numb!=OFF)
    {
     r_Ne++;
     r_elem[elem[e].new_numb].i  = node[elem[e].i].new_numb;
     r_elem[elem[e].new_numb].j  = node[elem[e].j].new_numb;
     r_elem[elem[e].new_numb].k  = node[elem[e].k].new_numb;
     r_elem[elem[e].new_numb].si = side[elem[e].si].new_numb;
     r_elem[elem[e].new_numb].sj = side[elem[e].sj].new_numb;
     r_elem[elem[e].new_numb].sk = side[elem[e].sk].new_numb;
     r_elem[elem[e].new_numb].xv = elem[e].xv;
     r_elem[elem[e].new_numb].yv = elem[e].yv;
     r_elem[elem[e].new_numb].material = elem[e].material;

     if(elem[e].ei != -1)
       r_elem[elem[e].new_numb].ei = elem[elem[e].ei].new_numb;
     else
       r_elem[elem[e].new_numb].ei = -1;

     if(elem[e].ej != -1)
       r_elem[elem[e].new_numb].ej = elem[elem[e].ej].new_numb;
     else
       r_elem[elem[e].new_numb].ej = -1;

     if(elem[e].ek != -1)
       r_elem[elem[e].new_numb].ek = elem[elem[e].ek].new_numb;
     else
       r_elem[elem[e].new_numb].ek = -1;
    }

 for(s=0; s<side.size(); s++)
   if(side[s].mark!=OFF && side[s].new_numb!=OFF)
    {
     r_Ns++;
     r_side[side[s].new_numb].c    = node[side[s].c].new_numb;
     r_side[side[s].new_numb].d    = node[side[s].d].new_numb;
     r_side[side[s].new_numb].mark = side[s].mark;

     if(side[s].a != OFF)
      {r_side[side[s].new_numb].a  = node[side[s].a].new_numb;
       r_side[side[s].new_numb].ea = elem[side[s].ea].new_numb;}
     else
      {r_side[side[s].new_numb].a  = OFF;
       r_side[side[s].new_numb].ea = OFF;}

     if(side[s].b != OFF)
      {r_side[side[s].new_numb].b  = node[side[s].b].new_numb;
       r_side[side[s].new_numb].eb = elem[side[s].eb].new_numb;}
     else
      {r_side[side[s].new_numb].b  = OFF;
       r_side[side[s].new_numb].eb = OFF;}
    }

/*------------+
|             |
|  Node data  |
|             |
+------------*/
 name[len-1] = 'n';

 if((out=fopen(name, "w"))==NULL)
  {fprintf(stderr, "Cannot save file %s !\n", name);
   return 1;}
 
 fprintf(out, "%d\n", r_Nn);
 for(n=0; n<r_Nn; n++)
   fprintf(out, "%4d:  %18.15e %18.15e  %d\n",
		 n,
		 r_node[n].x, r_node[n].y, r_node[n].mark);
 fprintf(out, "----------------------------------------------------------\n");
 fprintf(out, "   n:  x                      y                       mark\n");
 fflush(out);
 fclose(out);

/*---------------+
|                |
|  Element data  |
|                |
+---------------*/
 name[len-1] = 'e';

 if((out=fopen(name, "w"))==NULL)
  {fprintf(stderr, "Cannot save file %s !\n", name);
   return 1;}

 fprintf(out, "%d\n", r_Ne);
 for(e=0; e<r_Ne; e++)
   fprintf(out, "%4d: %4d %4d %4d  %4d %4d %4d  %4d %4d %4d  %18.15e %18.15e  %4d\n",
		 e,
		 r_elem[e].i,  r_elem[e].j,  r_elem[e].k,
		 r_elem[e].ei, r_elem[e].ej, r_elem[e].ek,
		 r_elem[e].si, r_elem[e].sj, r_elem[e].sk,
		 r_elem[e].xv, r_elem[e].yv, r_elem[e].material);
 fprintf(out, "---------------------------------------------------");
 fprintf(out, "-------------------------------------------------------\n");
 fprintf(out, "   e:   i,   j,   k,   ei,  ej,  ek,   si,  sj,  sk");  
 fprintf(out, "   xV,                    yV                       sign\n");  
 fflush(out);
 fclose(out);

/*------------+
|             |
|  Side data  |
|             |
+------------*/
 name[len-1] = 's';

 if((out=fopen(name, "w"))==NULL)
  {fprintf(stderr, "Cannot save file %s !\n", name);
   return 1;}
 
 fprintf(out, "%d\n", r_Ns);
 for(s=0; s<r_Ns; s++)
   fprintf(out, "%4d:  %4d %4d %4d %4d  %d\n",
		 s, 
		 r_side[s].c,  r_side[s].d,
		 r_side[s].ea, r_side[s].eb, 
		 r_side[s].mark);
 fprintf(out, "--------------------------------\n");
 fprintf(out, "   s:    c    d   ea   eb   mark\n");
 fflush(out);
 fclose(out);

 return 0;
}

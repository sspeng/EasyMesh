/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

using namespace std;

/*==========================================================================*/
int load_i(FILE *in, int *numb)
{
 char dum, dummy[128];

 for(;;)
  {fscanf(in,"%s", dummy);
   if(dummy[0]=='#' && strlen(dummy)>1 && dummy[strlen(dummy)-1]=='#') {}
   else if(dummy[0]=='#') {do{fscanf(in,"%c", &dum);} while(dum!='#');}
   else                   {*numb=atoi(dummy); break;} }

 return 0; 
}

/*==========================================================================*/
int load_d(FILE *in, real *numb)
{
 char dum, dummy[128];

 for(;;)
  {fscanf(in,"%s", dummy);
   if(dummy[0]=='#' && strlen(dummy)>1 && dummy[strlen(dummy)-1]=='#') {}
   else if(dummy[0]=='#') {do{fscanf(in,"%c", &dum);} while(dum!='#');}
   else                   {*numb=atof(dummy); break;} }

 return 0; 
}

/*==========================================================================*/
int load_s(FILE *in, char *string)
{
 char dum, dummy[128];

 for(;;)
  {fscanf(in,"%s", dummy);
   if(dummy[0]=='#' && strlen(dummy)>1 && dummy[strlen(dummy)-1]=='#') {}
   else if(dummy[0]=='#') {do{fscanf(in,"%c", &dum);} while(dum!='#');}
   else                   {strcpy(string, dummy); break;} }

 return 0; 
}

/*==========================================================================*/
int EasyMesh::load(int *ins)
{
 int  c, n, s, Fl, M, chains;
 char dummy[80];
 real xmax=-GREAT, xmin=+GREAT, ymax=-GREAT, ymin=+GREAT, xt, yt, gab;

 FILE *in;

 int m;
 real xO, yO, xN, yN, L, Lx, Ly, dLm, ddL, L_tot;
 
 std::vector<int> inserted;

/*----------+
|           |
|  Loading  |
|           |
+----------*/
 if((in=fopen(name, "r"))==NULL)
  {fprintf(stderr, "Cannot load file %s !\n", name);
   return 1;}

 load_i(in, &Nc);
 inserted.resize(Nc); 
 for(n=0; n<Nc; n++)
  {
   load_s(in, dummy);     
   load_d(in, &point[n].x);
   load_d(in, &point[n].y);
   load_d(in, &point[n].F);
   load_i(in, &point[n].mark);

   xmax=std::max(xmax, point[n].x); ymax=std::max(ymax, point[n].y);
   xmin=std::min(xmin, point[n].x); ymin=std::min(ymin, point[n].y);

   point[n].inserted=0; /* it is only loaded */
  }

 load_i(in, &Fl);
 segment.resize(Fl+1);
 chain  .resize(Fl+1);
 segment[Fl].n0=-1;
 segment[Fl].n1=-1;

 for(s=0; s<Fl; s++)
  {
   load_s(in, dummy);
   load_i(in, &segment[s].n0);
   load_i(in, &segment[s].n1);
   load_i(in, &segment[s].mark);
  }
 fclose(in);

/*----------------------+
   counting the chains
+----------------------*/
 chains=0;
 chain[chains].s0=0;
 for(s=0; s<Fl; s++)
  {
   point[segment[s].n0].inserted++;
   point[segment[s].n1].inserted++;

   segment[s].chain           = chains;

   if(segment[s].n1!=segment[s+1].n0)
    {chain[chains].s1=s;
     chains++;
     chain[chains].s0=s+1;}
  }

/*------------------------------------------------+
   correct the spacing functions where necessary
+------------------------------------------------*/
 for(s=0; s<Fl; s++)
  {
   xO=point[segment[s].n0].x; yO=point[segment[s].n0].y;
   xN=point[segment[s].n1].x; yN=point[segment[s].n1].y; 

   Lx=(xN-xO); Ly=(yN-yO); L=sqrt(Lx*Lx+Ly*Ly);

   if( (point[segment[s].n0].F+point[segment[s].n1].F > L ) &&
       (segment[s].n0 != segment[s].n1) )
    {point[segment[s].n0].F = std::min(point[segment[s].n0].F, L);
     point[segment[s].n1].F = std::min(point[segment[s].n1].F, L);} 
  }

/*-------------------------------------+
   counting the nodes on each segment
+-------------------------------------*/
 for(s=0; s<Fl; s++)
  {
   xO=point[segment[s].n0].x; yO=point[segment[s].n0].y;
   xN=point[segment[s].n1].x; yN=point[segment[s].n1].y; 

   Lx=(xN-xO); Ly=(yN-yO); L=sqrt(Lx*Lx+Ly*Ly);

   if(point[segment[s].n1].F+point[segment[s].n0].F<=L)
    {dLm=0.5*(point[segment[s].n0].F+point[segment[s].n1].F);
     segment[s].N=(int)ceil(L/dLm);}
   else
     segment[s].N=1;
  }

/*---------------------------------------+
   check if the chain is closed or open
+---------------------------------------*/
 for(n=0; n<chains; n++)
  {
   if( segment[chain[n].s0].n0 == segment[chain[n].s1].n1 )
    {chain[n].type=CLOSED;}

   if( segment[chain[n].s0].n0 != segment[chain[n].s1].n1 )
    {chain[n].type=OPEN;}

   if( (point[segment[chain[n].s0].n0].inserted==1) &&
       (point[segment[chain[n].s1].n1].inserted==1) )
    {chain[n].type=INSIDE;}
  }

/*------------+
|             |
|  Inserting  |
|             |
+------------*/
 xt = 0.5*(xmax+xmin);
 yt = 0.5*(ymax+ymin);

 gab=std::max((xmax-xmin),(ymax-ymin));
 
 node.increase_size(3);
 node[2].x = xt;                node[2].y = yt + 2.8*gab; 
 node[0].x = xt - 2.0*gab;      node[0].y = yt - 1.4*gab; 
 node[1].x = xt + 2.0*gab;      node[1].y = yt - 1.4*gab; 
 node[2].inserted=2;
 node[1].inserted=2;
 node[0].inserted=2;
/*
 node[2].type=;
 node[1].type=;
 node[0].type=;
*/
 node[2].next=1;
 node[1].next=0;
 node[0].next=2;

 elem.increase_size(1);
 elem[0].i =0;  elem[0].j = 1; elem[0].k = 2;
 elem[0].ei=-1; elem[0].ej=-1; elem[0].ek=-1;
 elem[0].si= 1; elem[0].sj= 2; elem[0].sk= 0;
 
 side.increase_size(3);
 side[0].c=0; side[0].d=1; side[0].a=2; side[0].b=-1; 
 side[1].c=1; side[1].d=2; side[1].a=0; side[1].b=-1; 
 side[2].c=0; side[2].d=2; side[2].a=-1; side[2].b=1;  
 side[0].ea= 0; side[0].eb=-1;
 side[1].ea= 0; side[1].eb=-1; 
 side[2].ea=-1; side[2].eb= 0;

 for(n=0; n<Nc; n++)
   point[n].new_numb=OFF;

/*-experiment-*/
  {
   real tot_area, ave_area, ave_F;
   int    ave_N;
/*----------------------------------------------------+
|  from version 1.5 calculate area for closed chains  |
|  to see which of them are the holes                 |
+----------------------------------------------------*/
   tot_area=0.0;

   for(c=0; c<chains; c++)
    {
     for(s=chain[c].s0; s<=chain[c].s1; s++)
      {
       xO=point[segment[s].n0].x; yO=point[segment[s].n0].y;
       xN=point[segment[s].n1].x; yN=point[segment[s].n1].y; 

       chain[c].area += (xO-xN)*(yO+yN)*0.5;
      }

     if(chain[c].type==CLOSED)
       tot_area += chain[c].area;
    }
  }

 for(c=0; c<chains; c++)
  {
   for(s=chain[c].s0; s<=chain[c].s1; s++)
    {
     xO=point[segment[s].n0].x; yO=point[segment[s].n0].y;
     xN=point[segment[s].n1].x; yN=point[segment[s].n1].y; 

/*===============
*  first point  *
===============*/
     if( point[segment[s].n0].new_numb == OFF )
      {
       if(s==chain[c].s0) /* first segment in the chain */
	{
	 insert_node(xO, yO, OFF,
	 OFF,  OFF, point[segment[s].n0].mark, OFF, OFF);
	}

       else if(s==chain[c].s1 && segment[s].N==1)
	{
	 insert_node(xO, yO, OFF,
	 node.size()-1, segment[s-1].mark,
	 point[segment[s].n0].mark,
	 segment[s].mark, point[segment[chain[c].s1].n1].new_numb);
	}

       else
	{
	 insert_node(xO, yO, OFF,
	 node.size()-1, segment[s-1].mark, point[segment[s].n0].mark, OFF, OFF);
	}

       node[node.size()-1].next     = node.size();     /* node.size()-1 is index of inserted node */
       node[node.size()-1].chain    = segment[s].chain;
       node[node.size()-1].F        = point[segment[s].n0].F;
       point[segment[s].n0].new_numb=node.size()-1;
      }

     Lx=(xN-xO);  Ly=(yN-yO);  L=sqrt(Lx*Lx+Ly*Ly);
     dLm=L/segment[s].N;

     if(point[segment[s].n0].F + point[segment[s].n1].F <= L)
      { 
       if(point[segment[s].n0].F > point[segment[s].n1].F)
	{M=-segment[s].N/2; ddL=(point[segment[s].n1].F-dLm)/M;}
       else
	{M=+segment[s].N/2; ddL=(dLm-point[segment[s].n0].F)/M;}
      }

/*=================
*  middle points  *
=================*/
     L_tot=0;
     if(point[segment[s].n0].F + point[segment[s].n1].F <= L)
       for(m=1; m<abs(segment[s].N); m++)
	{
	 L_tot+=(dLm-M*ddL);
  
	 if(point[segment[s].n0].F > point[segment[s].n1].F)
	  {M++; if(M==0 && segment[s].N%2==0) M++;}
	 else
	  {M--; if(M==0 && segment[s].N%2==0) M--;}

	 if(s==chain[c].s1 && m==(abs(segment[s].N)-1))
	  {insert_node(xO+Lx/L*L_tot, yO+Ly/L*L_tot, OFF,
	   node.size()-1, segment[s].mark, segment[s].mark, segment[s].mark, point[segment[s].n1].new_numb);
	   node[node.size()-1].next = node.size();}

	 else if(m==1)
	  {insert_node(xO+Lx/L*L_tot, yO+Ly/L*L_tot, OFF,
	   point[segment[s].n0].new_numb, segment[s].mark, segment[s].mark, OFF, OFF);
	   node[node.size()-1].next = node.size();}

	 else
	  {insert_node(xO+Lx/L*L_tot, yO+Ly/L*L_tot, OFF,
	   node.size()-1, segment[s].mark, segment[s].mark, OFF, OFF);
	   node[node.size()-1].next = node.size();}

	 node[node.size()-1].chain    = segment[s].chain;
	 node[node.size()-1].F        = 0.5*(node[node.size()-2].F + (dLm-M*ddL));
	}

/*==============
*  last point  * -> just for the inside chains
==============*/
     if( (point[segment[s].n1].new_numb == OFF) && (s==chain[c].s1) )
      {
       insert_node(xN, yN, OFF,
       node.size()-1, segment[s].mark, point[segment[s].n1].mark, OFF, OFF);
       node[node.size()-1].next     = OFF;
       node[node.size()-1].chain    = segment[s].chain;
       node[node.size()-1].F        = point[segment[s].n1].F;
      }

     if( chain[c].type==CLOSED && s==chain[c].s1)
       node[node.size()-1].next     = point[segment[chain[c].s0].n0].new_numb;

     if( chain[c].type==OPEN && s==chain[c].s1)
       node[node.size()-1].next     = OFF;

    }  /* segments */
  }  /* chains */
 
/*===================================+
|  If EasyMesh was used for just to  |
|  craete Delaunay and Voronoi mesh  |
|    of an existing set of points    |
+===================================*/
 if(chains == 0)
  {
   for(n=0;n<Nc;n++)
     insert_node(point[n].x,point[n].y,OFF,OFF,OFF,point[n].mark,OFF,OFF); 
   *ins = OFF;
  }

 return 0;
}

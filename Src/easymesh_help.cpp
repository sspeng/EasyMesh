/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include <cstdio>
#include "easymesh.h"

using namespace std;

/*==========================================================================*/
void EasyMesh::help(const char * name)
{
  printf("\n********************************************************");
  printf("\n****************                       *****************");
  printf("\n****************   PROGRAM: EasyMesh   *****************");
  printf("\n****************                       *****************");
  printf("\n****************  Date: 12. 12. 2007.  *****************");
  printf("\n****************                       *****************");
  printf("\n****************  Author Bojan NICENO  *****************");
  printf("\n****************                       *****************");
  printf("\n****************  bojan.niceno@psi.ch  *****************");
  printf("\n****************                       *****************");
  printf("\n********************************************************");
  printf("\n\nUsage: %s  [<options>] <NAME>", name);
  printf("\n\nNote: <NAME> and [<options>] can be entered in any order");
  printf("\n\n===============");
  printf("\n=== OPTIONS ===");
  printf("\n===============");
  printf("\n\nValid options are:");
  printf("\n   +a [0..6]   bee more agressive when meshing");
  printf("\n   -d          don't triangulate domain, just boundary");
  printf("\n   -m          without any messages");
  printf("\n   -r          without mesh relaxation");
  printf("\n   -s          without Laplacian smoothing");
  printf("\n   +eps [D,V]  create drawing in eps format");
  printf("\n   +example    create example input files and exit");
  printf("\n\nNote 1: After +a option, you should specify the agressivity");
  printf("\n        level which is an integer value from 0 to 6. The more");
  printf("\n        agressive you are, the chances of getting the final "); 
  printf("\n        mesh are better, but the mesh quality is poorer.");
  printf("\n\nNote 2: Input (and output) file can have entities such as");
  printf("\n        nodes, segments, elements, and sides numbered from 0");
  printf("\n        or from 1. By default, the output file will have the"); 
  printf("\n        same numbering as the input file.");
  printf("\n\nNote 3: If you want eps output with Delaunay or Voronoi");
  printf("\n        mesh only, specify D or V after +eps option.");
  printf("\n        If you don't specify anything after +eps option,");
  printf("\n        EasyMesh will draw both meshes.");
  printf("\n\n>>>>>>>>>>>>>");
  printf("\n>>> INPUT >>>");
  printf("\n>>>>>>>>>>>>>");
  printf("\n\nInput file (NAME.d) has the following format");
  printf("\n  first line:          <Nbp>");
  printf("\n  following Nbp lines: <point:> <x> <y> <spacing> <marker>");
  printf("\n  one line:            <Nbs>");
  printf("\n  following Nbs lines: <segment:> <start_point> <end_point> <marker>");
  printf("\n\n  where:");
  printf("\n    Nbn     is the number of points defining the boundary");
  printf("\n    Nbp     is the number of sides defining the boundary");
  printf("\n    marker  is the boundary condition marker");
  printf("\n\nNote: Input file has to end with the extension: .d !");
  printf("\n\n<<<<<<<<<<<<<<");
  printf("\n<<< OUTPUT <<<");
  printf("\n<<<<<<<<<<<<<<");
  printf("\n\nEasyMesh produces the following three output files:");
  printf("\n  NAME.n");
  printf("\n  NAME.e");
  printf("\n  NAME.s");
  printf("\n\nNode file (NAME.n) has the following format:");
  printf("\n  first line:         <Nn>");
  printf("\n  following Nn lines: <node:> <x> <y> <marker> ");
  printf("\n  last two lines:     comments inserted by the program ");
  printf("\n\n  where:");
  printf("\n  Nn      is the number of nodes");
  printf("\n  x, y    are the node coordinates");
  printf("\n  marker  is the node boundary marker");
  printf("\n\nElement file (NAME.e) has the following format:");
  printf("\n  first line          <Ne> ");
  printf("\n  following Ne lines: <element:> <i> <j> <k> <ei> <ej> <ek> <si> <sj> <sk> <xV> <yV> <marker> ");
  printf("\n  last two lines:     comments inserted by the program ");
  printf("\n\n  where:");
  printf("\n    Ne          is the number of elements");
  printf("\n    i,   j,  k  are the nodes belonging to the element, ");
  printf("\n    ei, ej, ek  are the neighbouring elements,");
  printf("\n    si, sj, sk  are the element sides. ");
  printf("\n    xV, yV      are the coordinates of the element circumcenter");
  printf("\n    marker      is the side boundary marker");
  printf("\n\nSide file (NAME.s) has the following format:");
  printf("\n  first line:         <Ns> ");
  printf("\n  following Ns lines: <side:> <c> <d> <ea> <eb> <marker> "); 
  printf("\n  last two lines:     comments inserted by the program ");
  printf("\n\n  where:");
  printf("\n    Ns      is the number of sides");
  printf("\n    c,  d   are the starting and ending node of the side,");
  printf("\n    ea, eb  are the elements on the left and on the right of the side.");
  printf("\n\nNote: If eb equals to -1, it means that the right element does not exists,");
  printf("\n      i.e. the side is on the boundary !");  
  printf("\n\n");
}

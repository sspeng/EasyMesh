/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef OPTIONS_H
#define OPTIONS_H

#include "easymesh_constants.h"

///////////////
//           //
//  Options  //
//           //
///////////////
class Options {

 public:
   Options() {d=ON, ins=ON, r=ON, s=ON,
              eps=OFF, epsDel=OFF, epsVor=OFF, 
              m=ON, exa=OFF;}

   int d, ins, r, s;
   int eps, epsDel, epsVor;
   int m, exa;
};

#endif

/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef CHAIN_H
#define CHAIN_H

/////////////////////////////////////
//                                 //
//  Chain (defined in input file)  //
//                                 //
/////////////////////////////////////
class Chain
 {
  public:
    Chain() {s0 = s1 = type = 0;
             area = 0.0;}

    int s0, s1, type;
    real area;
 };


#endif

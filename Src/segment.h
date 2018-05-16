/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef SEGMENT_H
#define SEGMENT_H

///////////////////////////////////////
//                                   //
//  Segment (defined in input file)  //
//                                   //
///////////////////////////////////////
class Segment
 {
  public:
    Segment() {n0 = n1 = 0;
               N = 0; chain = 0; bound = 0; mark = 0;}

    int n0, n1;
    int N; int chain; int bound; int mark;
 };
 
#endif

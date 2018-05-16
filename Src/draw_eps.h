/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef DRAW_EPS_H
#define DRAW_EPS_H

#include <algorithm>
#include <climits>
#include <cstdio>
#include "precision.h"

int start_eps(const char * eps_name);
int line_eps(real x1, real y1, 
             real x2, real y2, 
             int style, int width, int color, float le);
int solid_eps(real x1, real y1, 
              real x2, real y2, 
              real x3, real y3, 
              int style, int width, int color, float le);
int end_eps();

#endif

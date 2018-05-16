/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef EASYMESH_DEF_H
#define EASYMESH_DEF_H

#define DEBUG OFF                /* set this ON if you wish to debug        */ 

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm> /* min & max */

#include "precision.h"

#ifndef PI
#define PI    3.14159265359
#endif

#define SMALL ((real)1e-30)
#define GREAT ((real)1e+30)

/*---------------------------+
|  Definitions for elements  |
+---------------------------*/
#define ON      0 
#define OFF    -1       /* element is switched off */
#define ACTIVE  3
#define DONE    4
#define WAITING 5

/*-------------------------+
|  Definitions for chains  |
+-------------------------*/
#define CLOSED 0
#define OPEN   1
#define INSIDE 2

#endif

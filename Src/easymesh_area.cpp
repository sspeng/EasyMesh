/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
real EasyMesh::area(const Node *na, const Node *nb, const Node *nc)
{
 return 0.5 * (   ((*nb).x-(*na).x)*((*nc).y-(*na).y) 
		- ((*nb).y-(*na).y)*((*nc).x-(*na).x));
}

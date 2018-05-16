/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef PRINT_H
#define PRINT_H

#include<iostream>

#define PR(x) std::cout << "FILE: "   << __FILE__ \
                        << ", LINE: " << __LINE__ \
                        << ", " << #x " = " << x  \
                        << std::endl;

#define MS(x) std::cout << "FILE: "   << __FILE__ \
                        << ", LINE: " << __LINE__ \
                        << ", " << #x             \
                        << std::endl;

#endif


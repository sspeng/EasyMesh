/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef EASYMESH_H
#define EASYMESH_H

#include "element.h"
#include "side.h"
#include "node.h"
#include "segment.h"
#include "chain.h"
#include "options.h"
#include "timer.h"

#define TEMPORARY_MAX_NODES 10000

////////////////
//            //
//  EasyMesh  //
//            //
////////////////
class EasyMesh {

  public:
    /*------------+
    |  Functions  |
    +------------*/
    EasyMesh() : R_tol(0.7), 
                 elem (TEMPORARY_MAX_NODES*2),
                 side (TEMPORARY_MAX_NODES*3),
                 node (TEMPORARY_MAX_NODES),
                 point(TEMPORARY_MAX_NODES/2) {}
    int algor(int argc, char *argv[]);

  private:
      
    /*-------+
    |  Data  |
    +-------*/
    int Nc;                 /* number of chains */
    int ugly;               /* ugliest element in the domain  */
    real R_tol;             /* tolerated circumscribed radii. */

    char name[80]; int len; /* problem name  */
    char eps_name[81];      /* eps file name */

    Element elem;
    Side    side;
    Node    node;
    Node    point;

    std::vector<Segment> segment;
    std::vector<Chain>   chain;

    /*------------+
    |  Functions  |
    +------------*/
    int load(int *ins);
    void erase(int ins);
    int classify();
    int new_node();
    int in_elem(const Node*);
    int neighbours();
    int relax();
    int circles(int e);
    int smooth();
    int compress();
    int materials();
    int spacing(int e, int n);
    int swap_side(int s);
    int diamond();
    int bowyer(int n);
    int save();
    void help(const char *);
    void examples();
    real area(const Node *na, const Node *nb, const Node *nc);
    void parse(int argc, char *argv[], Options * options);
    int insert_node(real x, real y, int spac,
        	 int prev_n, int prev_s_mark, int mark, int next_s_mark, int next_n);
    int draw_file(int eps, int epsDel, int epsVor);
};

#endif

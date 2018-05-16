/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef NODE_H
#define NODE_H

////////////
//        //
//  Node  //
//        //
////////////
class Node
 {
  public:
    Node(const int n) : stride(2048) {nd.resize( n ); pos=0;}
    Node()            : stride(2048) 
     {pos = 0;
      x = y = F = sumx = sumy = 0.0;
      Nne      = 0;
      mark     = 0;
      next     = 0;
      chain    = 0;
      inserted = 0;
      new_numb = 0;} /* do nothing */

    int size() {return pos;}
    void increase_size(const int inc) {
      pos+=inc;
      if(pos>=nd.size()) nd.resize(nd.size()+stride);
    }

    real x, y, F;
    real sumx, sumy;
    int    Nne;
    int mark;             /* is it off */
    int next;             /* next node in the boundary chain */
    int chain;            /* on which chains is the node */
    int inserted;
    int new_numb;         /* used for renumeration */

    std::vector<Node> nd;
    Node & operator [] (const int i) {return nd.at(i);}

  private:
    unsigned pos;
    int      stride;
 };

#endif

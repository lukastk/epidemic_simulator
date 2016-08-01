#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
public:
  int index;
  int id;
  short* state;
  int state_length;
  Node** edges;
  int edges_length;
  double* edge_weights;

  bool is_sensitive();
  bool is_infected();

  Node();
  ~Node();
};

#endif

#ifndef NETWORK_CONSTRUCTOR_H
#define NETWORK_CONSTRUCTOR_H

#include <vector>
#include <set>
#include <map>
#include <iostream>

#include "node.h"

struct Edge {
  int source;
  int target;
  double weight;
};

class NetworkConstructor {
private:
  std::vector<Edge*> edges;

  bool is_lattice;

public:
  ~NetworkConstructor();

  Node** nodes;
  int nodes_length;

  Node*** node_lattice;
  int lattice_width;
  int lattice_height;

  void add_edge(int source, int target, double weight);
  void generate_nodes_array();

  void create_lattice(int width, int height);

};

#endif

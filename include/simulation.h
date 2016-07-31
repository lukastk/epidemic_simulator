#ifndef SIMULATION_H
#define SIMULATION_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <set>
#include <iostream>

#include "node.h"
#include "infection_model.h"
#include "SIR_model.h"

class Simulation {
private:
  InfectionModel** infection_models;
  int infection_models_length;

  Node** nodes;
  int nodes_length;

  std::set<int> node_update_set;

public:

  boost::random::mt19937 random;

  Simulation(Node** nodes, int nodes_length, InfectionModel** infection_models, int infection_models_length);
  ~Simulation();

  Node** get_nodes();
  int get_nodes_length();

  void initialize();
  void update();

  void print_node_states();

};

#endif

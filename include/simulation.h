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

  /**
   * Initializes the infection models by supplying them with a random number generator. The function also sets all the states of the infection models to S.
   */
  void initialize();

  /**
   * Goes through the array of nodes, and puts the nodes that should be updated into the node_update_set.
   */
  void refresh_node_update_list();

  void update();

  void print_node_states();

  /**
   * Returns true if the simulation has reached a steady state. This essentially means that the node_update_set is empty.
   */
  bool is_in_steady_state();

};

#endif

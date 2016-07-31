#ifndef INFECTION_MODEL_H
#define INFECTION_MODEL_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <set>
#include <iostream>

#include "node.h"

class InfectionModel {
private:
  short state_index;

public:
  InfectionModel(int state_index);
  virtual ~InfectionModel();

  virtual void try_infect(Node* source, Node* target, std::set<int>* node_update_set) = 0;
  virtual bool update_node(Node* node, std::set<int>* node_update_set) = 0;
  int get_infection_index();
  void set_node_state(Node* node, short state);
  short get_node_state(Node* node);

  virtual void set_random_generator(boost::random::mt19937* random) = 0;

  virtual bool node_should_be_updated(Node* node) = 0;
};

#endif

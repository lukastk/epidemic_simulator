#ifndef SIR_MODEL_H
#define SIR_MODEL_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <set>
#include <iostream>

#include "node.h"
#include "infection_model.h"

class SIRModel : public InfectionModel {
private:
  double p_infect;
  double p_infect_sensitive;
  double p_recover;
  boost::random::uniform_real_distribution<double> rand_dist;
  boost::random::mt19937* random;

public:
  SIRModel(short state_index, double p_infect, double p_infect_sensitive, double p_recover);
  ~SIRModel();

  void try_infect(Node* source, Node* target, std::set<int>* node_update_set);
  bool update_node(Node* node, std::set<int>* node_update_set);

  void set_random_generator(boost::random::mt19937* random);

  bool node_should_be_updated(Node* node);

  static const short STATE_S = 0;
  static const short STATE_I = 1;
  static const short STATE_R = 2;
};

#endif

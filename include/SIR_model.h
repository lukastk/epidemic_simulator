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
  boost::random::uniform_real_distribution<double> rand_dist;
  boost::random::mt19937* random;

public:
  double p_infect;
  double p_coinfect;
  double p_recover;

  SIRModel(short state_index, double p_infect, double p_coinfect, double p_recover);
  SIRModel(short state_index);
  ~SIRModel();

  void try_infect(Node* source, Node* target, std::set<int>* node_update_set);
  bool update_node(Node* node, std::set<int>* node_update_set);

  void set_random_generator(boost::random::mt19937* random);

  bool node_should_be_updated(Node* node);

  /**
   * Copies onto an integer array the number of nodes in each state of the SIRModel, given an array of nodes. The passed array must be of size 3.
   * @param out - The array that the data will be output to.
   * @param nodes - The array of nodes
   * @param nodes_length - Length of array
   * @param node_state_index - The index that the infection's state is stored on on the node's state array.
   */
  void count_nodes_in_states(int* out, Node** nodes, int nodes_length, int node_state_index);

  static const short STATE_S = 0;
  static const short STATE_I = 1;
  static const short STATE_R = 2;
};

#endif

#include "SIR_model.h"

SIRModel::SIRModel(short state_index, double p_infect, double p_coinfect, double p_recover) : InfectionModel(state_index) {
  this->p_infect = p_infect;
  this->p_coinfect = p_coinfect;
  this->p_recover = p_recover;

  rand_dist = boost::random::uniform_real_distribution<double>(0, 1);
}

SIRModel::SIRModel(short state_index) : SIRModel::SIRModel(state_index, -1, -1, -1) {
}

SIRModel::~SIRModel() {
}

void SIRModel::try_infect(Node* source, Node* target, std::set<int>* node_update_set) {
  double p = rand_dist(*random);

  bool is_infected = get_node_state(target) == STATE_I;
  bool is_recovered = get_node_state(target) == STATE_R;

  if (!is_infected && !is_recovered) {

    if (!target->is_sensitive() && p < p_infect) {
      set_node_state(target, STATE_I);
      node_update_set->insert(target->index);
    } else if (target->is_sensitive() && p < p_coinfect) {
      set_node_state(target, STATE_I);
      node_update_set->insert(target->index);
    }
  }
}

bool SIRModel::update_node(Node* node, std::set<int>* node_update_set) {
  short state = get_node_state(node);
  bool stay_in_update_list = true;

  switch (state) {
    case STATE_S: {
      stay_in_update_list = false;
    } break;
    case STATE_I: {
      //std::cout << "id: " << node->id << std::endl;
      for (int i = 0; i < node->edges_length; i++) {
        //std::cout << node->edges[i]->index << std::endl;
        try_infect(node, node->edges[i], node_update_set);
      }
      //std::cout << "" << std::endl;

      double p = rand_dist(*random);

      if (p < p_recover) {
        set_node_state(node, STATE_R);
        stay_in_update_list = false;
      }
    } break;
    case STATE_R: {
      stay_in_update_list = false;
    } break;
    default: {
      throw 10;
    }
  }

  return stay_in_update_list;
}

void SIRModel::set_random_generator(boost::random::mt19937* random) {
  this->random = random;
}

bool SIRModel::node_should_be_updated(Node* node) {
  return get_node_state(node) == STATE_I;
}

void SIRModel::count_nodes_in_states(int* out, Node** nodes, int nodes_length, int node_state_index) {
  out[0] = 0;
  out[1] = 0;
  out[2] = 0;

  for (int i = 0; i < nodes_length; i++) {
    Node* node = nodes[i];

    int state = node->state[node_state_index];

    if (state < 0 || state > 2) {
      std::cerr << "State of node is out of bounds for SIRModel: " << state << std::endl;
    }

    out[state]++;
  }
}

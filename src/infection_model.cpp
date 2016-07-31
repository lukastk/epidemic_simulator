#include "infection_model.h"

InfectionModel::InfectionModel(int state_index) {
  this->state_index = state_index;
}

InfectionModel::~InfectionModel() {
}

int InfectionModel::get_infection_index() {
  return state_index;
}

void InfectionModel::set_node_state(Node* node, short state) {
  node->state[state_index] = state;
}

short InfectionModel::get_node_state(Node* node) {
  return node->state[state_index];
}

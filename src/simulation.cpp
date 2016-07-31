#include "simulation.h"

Simulation::Simulation(Node** nodes, int nodes_length, InfectionModel** infection_models, int infection_models_length) {
  this->nodes = nodes;
  this->nodes_length = nodes_length;
  this->infection_models = infection_models;
  this->infection_models_length = infection_models_length;

  random = boost::random::mt19937();
}

Simulation::~Simulation() {
  /*for (int i = 0; i < infection_models_length; i++) {
    delete infection_models[i];
  }
  delete infection_models;

  for (int i = 0; i < nodes_length; i++) {
    delete nodes[i];
  }
  delete nodes;
  */
}

void Simulation::initialize() {
  for (int j = 0; j < infection_models_length; j++) {
    infection_models[j]->set_random_generator(&random);
  }

  for (int i = 0; i < nodes_length; i++) {
    nodes[i]->state = new short[infection_models_length];
    nodes[i]->state_length = infection_models_length;

    for (int j = 0; j < infection_models_length; j++) {
      nodes[i]->state[j] = 0;
    }
  }
}

void Simulation::refresh_node_update_list() {
  for (int i = 0; i < nodes_length; i++) {
    bool node_should_be_updated = false;

    for (int j = 0; j < infection_models_length; j++) {
      node_should_be_updated = infection_models[j]->node_should_be_updated(nodes[i]) || node_should_be_updated;
    }

    if (node_should_be_updated) {
      node_update_set.insert(i);
    }
  }
}

int t = 0;

void Simulation::update() {

  std::set<int> add_to_update_set;

  Node* node;
  InfectionModel* im;
  for (std::set<int>::iterator it = node_update_set.begin(); it != node_update_set.end(); ++it) {
      int node_id = *it;
      node = nodes[node_id];

      bool keep_node_in_update_set = false;

      for (int i = 0; i < infection_models_length; i++) {
        im = infection_models[i];

        bool x = im->update_node(node, &add_to_update_set);
        keep_node_in_update_set = x || keep_node_in_update_set;
      }

      if (!keep_node_in_update_set) {
        node_update_set.erase(it);
      }
  }

  //std::cout << "-------" << std::endl;
  node_update_set.insert(add_to_update_set.begin(), add_to_update_set.end());
}

Node** Simulation::get_nodes() {
  return nodes;
}

int Simulation::get_nodes_length() {
  return nodes_length;
}

void Simulation::print_node_states() {
  for (int i = 0; i < nodes_length; i++) {
    std::cout << nodes[i]->state[0] << std::endl;
  }
}

bool Simulation::is_in_steady_state() {
  return node_update_set.size() == 0;
}

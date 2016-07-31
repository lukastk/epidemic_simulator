#include "node.h"

Node::~Node() {
  delete edges;
}

bool Node::is_sensitive() {
  bool sensitive = false;

  for (int i = 0; i < state_length; i++) {
    sensitive = (state[i] != 0) || sensitive;
  }

  return sensitive;
}

bool Node::is_infected() {
  bool infected = false;

  for (int i = 0; i < state_length; i++) {
    infected = (state[i] == 1) || infected;
  }

  return infected;
}

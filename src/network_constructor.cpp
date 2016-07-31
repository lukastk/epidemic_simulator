#include "network_constructor.h"

NetworkConstructor::~NetworkConstructor() {

}

void NetworkConstructor::add_edge(int source, int target, double weight) {
  Edge* edge = new Edge();
  edge->source = source;
  edge->target = target;
  edge->weight = weight;

  edges.push_back(edge);
}

void NetworkConstructor::generate_nodes_array() {
  std::vector<Node*> nodes;
  std::set<int> existing_nodes;

  std::map<int, int> id_to_index;
  std::map<int, std::vector<Edge*>*> id_to_edge_list;

  Node* node;
  for (std::vector<Edge*>::iterator it = edges.begin(); it != edges.end(); ++it) {
    int source = (*it)->source;
    int target = (*it)->target;

    if (existing_nodes.find(source) == existing_nodes.end()) {
      Node* node = new Node();
      node->id = source;
      node->index = nodes.size();

      nodes.push_back(node);

      id_to_index.insert( std::pair<int,int>( node->id , node->index ) );
      id_to_edge_list.insert( std::pair< int, std::vector<Edge*>* > ( node->id , new std::vector<Edge*>() ));
    }

    if (existing_nodes.find(target) == existing_nodes.end()) {
      node = new Node();
      node->id = target;
      node->index = nodes.size();

      nodes.push_back(node);

      id_to_index.insert( std::pair<int,int>( node->id , node->index ) );
      id_to_edge_list.insert( std::pair< int, std::vector<Edge*>* > ( node->id , new std::vector<Edge*>() ));
    }

    existing_nodes.insert(source);
    existing_nodes.insert(target);

    id_to_edge_list[source]->push_back(*it);
  }

  Node* target_node;
  for (std::set<int>::iterator it = existing_nodes.begin(); it != existing_nodes.end(); ++it) {
    node = nodes[ id_to_index[*it] ];
    std::vector<Edge*>* edge_list = id_to_edge_list[*it];

    node->edges_length = edge_list->size();
    node->edges = new Node*[node->edges_length];
    node->edge_weights = new double[node->edges_length];

    int edge_index = 0;

    for (std::vector<Edge*>::iterator edge_it = edge_list->begin(); edge_it != edge_list->end(); ++edge_it) {
      int target = (*edge_it)->target;
      double weight = (*edge_it)->weight;
      target_node = nodes[ id_to_index[ target ] ];

      node->edges[edge_index] = target_node;
      node->edge_weights[edge_index] = weight;

      edge_index++;
    }
  }

  Node** nodes_arr = new Node*[nodes.size()];
  int node_index = 0;
  for (std::vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
    nodes_arr[node_index] = *it;
    node_index++;
  }

  this->nodes_length = nodes.size();
  this->nodes = nodes_arr;

  if (is_lattice) {
    node_lattice = new Node**[lattice_width];

    for (int i = 0; i < lattice_width; i++) {
      node_lattice[i] = new Node*[lattice_height];
    }

    int node_index = 0;

    for (int x = 0; x < lattice_width; x++) {
      for (int y = 0; y < lattice_height; y++) {

        node_lattice[x][y] = this->nodes[node_index];
        node_index++;

      }
    }
  }
}

void NetworkConstructor::create_lattice(int width, int height) {

  int weight = 1;

  int** lat = new int*[width];

  int id = 0;
  for (int x = 0; x < width; x++) {
    lat[x] = new int[height];

    for (int y = 0; y < height; y++) {
      lat[x][y] = id;
      id++;
    }
  }

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int id_up, id_down, id_left, id_right;

      if (x != 0) {
        id_left = lat[x - 1][y];
      } else {
        id_left = lat[width -1][y];
      }

      if (y != 0) {
        id_up = lat[x][y - 1];
      } else {
        id_up = lat[x][height - 1];
      }

      if (x != width - 1) {
        id_right = lat[x + 1][y];
      } else {
        id_right = lat[0][y];
      }

      if (y != height - 1) {
        id_down = lat[x][y + 1];
      } else {
        id_down = lat[x][0];
      }

      int id = lat[x][y];

      add_edge(id, id_up, weight);
      add_edge(id, id_down, weight);
      add_edge(id, id_left, weight);
      add_edge(id, id_right, weight);

      //std::cout << id << ": " << id_up << " " << id_down << " " << id_left << " " << id_right << " " << std::endl;
    }
  }
/*
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int id = x*height + y;
      int id_up = id + 1;
      int id_down = id - 1;
      int id_left = id - width;
      int id_right = id + width;

      if (y == 0) {
        id_down = (x + 1)*height - 1;
      } else if (y == height - 1) {
        id_up = (x / width)*height;
      }

      if (x == 0) {
        id_left = (width - 1)*height + y;
      } else if (x == width - 1) {
        id_right = y;
      }

      add_edge(id, id_up, weight);
      add_edge(id, id_down, weight);
      add_edge(id, id_left, weight);
      add_edge(id, id_right, weight);

    }
  }
  */

  for (int x = 0; x < width; x++) {
    delete lat[x];
  }
  delete lat;

  is_lattice = true;
  lattice_width = width;
  lattice_height = height;
}

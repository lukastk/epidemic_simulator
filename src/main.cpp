#include "graphics_main.h"

using namespace std;

/*int main() {
  NetworkConstructor nc;

  InfectionModel** infection_models = new InfectionModel*[1];
  infection_models[0] = new SIRModel(0, 0.2, 0.4, 0.4);


  nc.add_edge(0, 1, 1);
  nc.add_edge(0, 2, 1);
  nc.add_edge(0, 3, 1);
  nc.add_edge(1, 2, 1);
  nc.add_edge(2, 3, 1);
  nc.add_edge(3, 0, 1);
  nc.add_edge(2, 0, 1);


  nc.create_lattice(5, 5);
  nc.generate_nodes_array();

  Node** nodes = nc.nodes;
  int nodes_length = nc.nodes_length;

  Node*** node_lattice = nc.node_lattice;

  Simulation* sim = new Simulation(nodes, nodes_length, infection_models, 1);

  nodes[0]->state[0] = 1;
  sim->initialize();

  for (int i = 0; i < 10; i++) {
    //sim->print_node_states();
    //std::cout << "---" << std::endl;

    sim->update();
  }

}
*/

int main( int argc, char* args[] ) {

  int squareSize = 2;
  int delay = 0;

  int lattice_w = 300;
  int lattice_h = 300;

  int time_stop = -1;

  /** SIM INIT **/

  NetworkConstructor nc;

  int infection_models_length = 2;
  InfectionModel** infection_models = new InfectionModel*[2];


  double p_infection = 0.5;
  double p_infection_sensitive = 0.99;
  double p_recover = 1.0;

  int seed = std::time(0);
  std::cout << "\nSeed: " << seed << std::endl;

  infection_models[0] = new SIRModel(0, p_infection, p_infection_sensitive, p_recover);
  ((SIRModel*)infection_models[0])->set_random_seed(seed);
  infection_models[1] = new SIRModel(1, p_infection, p_infection_sensitive, p_recover);
  ((SIRModel*)infection_models[1])->set_random_seed(seed);

  /*
  nc.add_edge(0, 1, 1);
  nc.add_edge(0, 2, 1);
  nc.add_edge(0, 3, 1);
  nc.add_edge(1, 2, 1);
  nc.add_edge(2, 3, 1);
  nc.add_edge(3, 0, 1);
  nc.add_edge(2, 0, 1);
  */

  nc.create_lattice(lattice_w, lattice_h);
  nc.generate_nodes_array();

  Node** nodes = nc.nodes;
  int nodes_length = nc.nodes_length;

  Node*** node_lattice = nc.node_lattice;
  int lattice_width = nc.lattice_width;
  int lattice_height = nc.lattice_height;

  Simulation* sim = new Simulation(nodes, nodes_length, infection_models, infection_models_length);

  node_lattice[100][50]->state[0] = SIRModel::STATE_I;
  node_lattice[3][3]->state[1] = SIRModel::STATE_I;

  sim->initialize();

  for (int i = 0; i < infection_models_length; i++) {
    delete infection_models[i];
  }
  delete infection_models;

	delete sim;

  return 0;
}

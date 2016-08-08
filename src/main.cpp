#include "main.h"

using namespace std;

int main( int argc, char* args[] ) {

  /** Simulation parameters **/

  int arg_i = 1;

  int lattice_w = atoi(args[arg_i++]);
  int lattice_h = atoi(args[arg_i++]);

  int run_per_set_of_parameters = atoi(args[arg_i++]);

  double min_p_infect = atof(args[arg_i++]);
  double max_p_infect = atof(args[arg_i++]);
  double d_p_infect = atof(args[arg_i++]);

  double min_p_coinfect = atof(args[arg_i++]);
  double max_p_coinfect = atof(args[arg_i++]);
  double d_p_coinfect = atof(args[arg_i++]);

  double min_p_recover = atof(args[arg_i++]);
  double max_p_recover = atof(args[arg_i++]);
  double d_p_recover = atof(args[arg_i++]);

  char* output_dir = args[arg_i++];

  /** Initialization **/

  NetworkConstructor nc;

  int infection_models_length = 2;
  InfectionModel** infection_models = new InfectionModel*[infection_models_length];

  int seed = std::time(0);
  std::cout << "\nSeed: " << seed << std::endl;

  infection_models[0] = new SIRModel(0);
  infection_models[1] = new SIRModel(1);

  // Create separate array with clear SIR instantiations

  SIRModel** sir_models = new SIRModel*[infection_models_length];
  sir_models[0] = (SIRModel*) infection_models[0];
  sir_models[1] = (SIRModel*) infection_models[1];

  nc.create_lattice(lattice_w, lattice_h);
  nc.generate_nodes_array();

  Node** nodes = nc.nodes;
  int nodes_length = nc.nodes_length;

  Node*** node_lattice = nc.node_lattice;

  Simulation* sim = new Simulation(nodes, nodes_length, infection_models, infection_models_length);
  sim->random.seed(seed);

  /** Initialize output **/

  std::ofstream sim_output;
  sim_output.open(output_dir);

  /** Run simulation **/

  int time;
  int* data = new int[3];

  sim_output << "p_i, p_c, p_r, ";

  for (int r = 0; r < run_per_set_of_parameters; r++) {
    sim_output << "time_" << r << ", ";
    sim_output << "S1_" << r << ", ";
    sim_output << "I1_" << r << ", ";
    sim_output << "R1_" << r << ", ";
    sim_output << "S2_" << r << ", ";
    sim_output << "I2_" << r << ", ";
    sim_output << "R2_" << r << ", ";

    if (r != run_per_set_of_parameters - 1) {
      sim_output << "RR_" << r << ", ";
    } else {
      sim_output << "RR_" << r;
    }
  }

  sim_output << endl;

  /* Start simulation */

  // Random distribution to randomize where the infection starts each simulation
  boost::random::mt19937 rng;
  boost::random::uniform_int_distribution<> rand_int(0,lattice_w-1);

  double p_infect = min_p_infect;
  double p_coinfect;
  double p_recover;

  while (p_infect <= max_p_infect) {

    p_coinfect = min_p_coinfect;

    while (p_coinfect <= max_p_coinfect) {

      p_recover = min_p_recover;

      while (p_recover <= max_p_recover) {

        cout << "Running with p_i: " << p_infect << ", p_c: " << p_coinfect << ", p_r: " << p_recover << endl;

        sim_output << p_infect << ", ";
        sim_output << p_coinfect << ", ";
        sim_output << p_recover << ", ";

        for (int r = 0; r < run_per_set_of_parameters; r++) {

          sir_models[0]->p_infect = p_infect;
          sir_models[0]->p_coinfect = p_coinfect;
          sir_models[0]->p_recover = p_recover;
          sir_models[1]->p_infect = p_infect;
          sir_models[1]->p_coinfect = p_coinfect;
          sir_models[1]->p_recover = p_recover;

          sim->initialize();

          // Randomize the start of each infection

          int infection_x = rand_int(rng);
          int infection_y = rand_int(rng);

          node_lattice[infection_x][infection_y]->state[0] = SIRModel::STATE_I;
          node_lattice[infection_x][infection_y]->state[1] = SIRModel::STATE_I;

          sim->refresh_node_update_list();

          time = 0;

          while (!sim->is_in_steady_state()) {
              sim->update();
              time++;
          }

          sim_output << time << ", ";

          sir_models[0]->count_nodes_in_states(data, nodes, nc.nodes_length, 0);

          sim_output << data[0] << ", " << data[1] << ", " << data[2] << ", ";

          sir_models[1]->count_nodes_in_states(data, nodes, nc.nodes_length, 1);

          sim_output << data[0] << ", " << data[1] << ", " << data[2] << ", ";

          if (r != run_per_set_of_parameters - 1) {
            sim_output << count_RR(nodes, nc.nodes_length) << ", ";
          } else {
            sim_output << count_RR(nodes, nc.nodes_length);
          }

          //cout << "Run " << r + 1 <<  " complete" << endl;
        }

        sim_output << endl;

        p_recover += d_p_recover;
      }

      p_coinfect += d_p_coinfect;
    }

    p_infect += d_p_infect;
  }

  delete[] data;
  delete[] nodes;
  delete[] infection_models;

  /** Close output **/

  sim_output.close();

  return 0;
}

/**
 * Counts the number of nodes that have been infected with both infections
 */
int count_RR(Node** nodes, int nodes_length) {
  int num_of_RR = 0;

  for (int i = 0; i < nodes_length; i++) {
    Node* node = nodes[i];

    if (node->state[0] == SIRModel::STATE_R && node->state[1] == SIRModel::STATE_R) {
      num_of_RR++;
    }
  }

  return num_of_RR;
}

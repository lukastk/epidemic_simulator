#include "graphics_main.h"

using namespace std;

int main( int argc, char* args[] ) {

  int squareSize = 1;
  int delay = 0;

  int lattice_w = 200;
  int lattice_h = 200;

  int time_stop = -1;

  /** SIM INIT **/

  NetworkConstructor nc;

  int infection_models_length = 2;
  InfectionModel** infection_models = new InfectionModel*[2];


  double p_infect = 0.6;
  double p_coeinfect = 0.3;
  double p_recover = 1.0;

  int seed = std::time(0);
  std::cout << "\nSeed: " << seed << std::endl;

  infection_models[0] = new SIRModel(0, p_infect, p_coeinfect, p_recover);
  infection_models[1] = new SIRModel(1, p_infect, p_coeinfect, p_recover);

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
  sim->random.seed(seed);

  sim->initialize();

  node_lattice[50][50]->state[0] = SIRModel::STATE_I;
  node_lattice[80][80]->state[1] = SIRModel::STATE_I;

  sim->refresh_node_update_list();

  /** END **/

	//The window we'll be rendering to
  SDL_Window* window = NULL;

  //The surface contained by the window
  SDL_Surface* screenSurface = NULL;

	//Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );

		return 1;
    }

	//Create window
	window = SDL_CreateWindow( "Epidemic Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return 1;
	}

	//Get window surface
	screenSurface = SDL_GetWindowSurface( window );

	bool quit = false;


	SDL_Event e;

	int time_n = 0;

	while (!quit) {

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

		int margin_x = 10;
		int margin_y = 10;

		SDL_Rect worldRect;
		worldRect.x = margin_x;
		worldRect.y = margin_y;
		worldRect.w = squareSize*lattice_width;
		worldRect.h = squareSize*lattice_height;

		SDL_FillRect( screenSurface, &worldRect, SDL_MapRGB( screenSurface->format, 11, 0xFF, 0xFF ) );

		for (int y = 0; y < lattice_height; y++) {
			for (int x = 0; x < lattice_width; x++) {

				//Draw traces

				SDL_Rect rect;
				rect.x = x*squareSize + margin_x;
				rect.y = y*squareSize + margin_y;
				rect.w = squareSize;
				rect.h = squareSize;

				//Color c = Color(10*sim->getNumOfAntsAt(y, x), 0, 0);

        Color c;

				if (node_lattice[x][y]->state[0] == 0 && node_lattice[x][y]->state[1] == 0) {
          c.G = 255;
        } else {
          c.G = 0;
        }

        if (node_lattice[x][y]->state[0] == 1) {
          c.R = 255;
        } else if (node_lattice[x][y]->state[0] == 2) {
          c.R = 100;
        }

        if (node_lattice[x][y]->state[1] == 1) {
          c.B = 255;
        } else if (node_lattice[x][y]->state[1] == 2) {
          c.B = 100;
        }

        if (node_lattice[x][y]->state[0] == 2 && node_lattice[x][y]->state[1] == 2) {
          c.R = 50;
          c.G = 50;
          c.B = 50;
        }

				SDL_FillRect( screenSurface, &rect, SDL_MapRGB( screenSurface->format, c.R, c.G, c.B ) );
			}
		}

		SDL_UpdateWindowSurface( window );


		SDL_Delay( delay );

    if (time_n == time_stop) {
      break;
    }

    sim->update();

		time_n += 1;
	}

	//Destroy window
  SDL_DestroyWindow( window );

  //Quit SDL subsystems
  SDL_Quit();

  delete[] nodes;
  delete[] infection_models;

  return 0;
}

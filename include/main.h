#ifndef MAIN_H
#define GRAPHMAIN_HCIS_MAIN_H

#include <stdio.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "simulation.h"
#include "network_constructor.h"

int count_RR(Node** nodes, int nodes_length);

#endif

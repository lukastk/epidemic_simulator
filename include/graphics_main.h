#ifndef GRAPHCIS_MAIN_H
#define GRAPHCIS_MAIN_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <ctime>
#include <iostream>

#include "simulation.h"
#include "network_constructor.h"

struct Color {
	char R;
	char G;
	char B;

	Color() : R(0), G(0), B(0) {}
	Color(char _R, char _G, char _B) : R(_R), G(_G), B(_B) {}
};
typedef struct Color Color;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

#endif

#ifndef GAME_SET_VISUALIZER_H
#define GAME_SET_VISUALIZER_H

/* import libraries */
/******************************************/
#include <fstream> // read write file
#include <iostream> // read write screen
#include <vector>
#include <string>
using namespace std;

#include "../../game_controller/environment/environment.h"
#include "../../game_controller/environment/data_structures.h"

/* class definition */
/******************************************/
class game_set_visualizer
{
	public:
		static void display_game_board(environment *game_set);

	private:
		// Disallow creating an instance of this object
		game_set_visualizer(){}

		// utility methods
		static void display_country_info(struct country *c);
};

#endif 
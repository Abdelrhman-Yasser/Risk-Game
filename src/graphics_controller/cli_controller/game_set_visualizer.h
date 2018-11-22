#ifndef GAME_SET_VISUALIZER_H
#define GAME_SET_VISUALIZER_H

/* import libraries */
/******************************************/
#include <fstream> // read write file
#include <iostream> // read write screen
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib> // for system calls

#define WAIT_TIME 1 // in seconds
#include <unistd.h> // for thread sleep - in order to see agent action

using namespace std;

#include "../../game_controller/environment/environment.h"
#include "../../game_controller/environment/data_structures.h"

/* class definition */
/******************************************/
class game_set_visualizer
{
	public:
		static void display_game_board(environment *game_set, gameplay_id player_turn, agent_type p_type, int reserve_troops_count, action a_type);
		static void display_winner_banner(gameplay_id winner_id);

	private:
		// Disallow creating an instance of this object
		game_set_visualizer(){}

		// display helpers
		static void display_country_info(struct country *c);
		static void display_banner(string title);
		static void display_continents(environment *game_set);
		static void display_player_perspective(gameplay_id player_id, environment *game_set);
		static void announce_player_turn(gameplay_id player_turn, agent_type p_type, int reserve_troops_count);

		// utilities
		static string enum_agent_type_to_string(agent_type p_type);
		static string enum_gameplay_id_to_string(gameplay_id player_id);
		static string enum_action_to_string(action a_type);
};

#endif 

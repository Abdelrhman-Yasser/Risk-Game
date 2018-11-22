#ifndef GUI_ENGINE_H
#define GUI_ENGINE_H

/* import libraries */
/******************************************/
#include "../../game_engine/environment/environment.h"
#include "../../game_engine/player/player_factory.h"
#include "../../game_engine/player/player.h"
#include "../../game_engine/environment/data_structures.h"

using namespace std;

/* class definition */
/******************************************/
class gui_engine
{

	private:
		environment game_environment;
		player *player1;
		player *player2;
		gameplay_id player_turn;

	public:
		/* constructor */
		gui_engine(char *map_init_file_dir, char *pop_init_file_dir, agent_type p1_type, agent_type p2_type);
		~gui_engine();

		/* interface methods */
		void start_new_game();

};

#endif 

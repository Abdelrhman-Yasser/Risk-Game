#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

/* import libraries */
/******************************************/
#include <string>
#include "../environment/environment.h"
#include "player.h"
#include "./humans/human.h"
//#include "./agents/greedy_agent.h"
#include "../environment/data_structures.h"

/* class definition */
/******************************************/


class player_factory
{
	private:
		environment *game_environment;

	public:
		/* constructor */
		player_factory(environment *game_environment);
		~player_factory();

		/* interface methods */
		player *create_player(player_type p_type, gameplay_id player_id);

};

#endif 

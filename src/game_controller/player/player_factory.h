#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

/* import libraries */
/******************************************/
#include <string>
#include "../environment/environment.h"
#include "../environment/data_structures.h"

#include "player.h"
#include "./humans/human.h"
#include "./agents/simple_agents/passive_agent.h"
#include "./agents/simple_agents/aggressive_agent.h"


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
		player *create_player(agent_type p_type, gameplay_id player_id);

};

#endif 

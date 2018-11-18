#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

/* import libraries */
/******************************************/
#include <string>
#include "../environment/environment.h"
#include "player.h"
#include "./humans/human.h"
#include "./agents/greedy_agent.h"


/* class definition */
/******************************************/


class player_factory
{
	private:
		enum p_type = {HUMAN, GREEDY}; // player types
		environment *game_environment;

	public:
		/* constructor */
		player_factory(environment *game_environment);
		~player_factory();

		/* interface methods */
		player create_player(enum p_type);

};

#endif 

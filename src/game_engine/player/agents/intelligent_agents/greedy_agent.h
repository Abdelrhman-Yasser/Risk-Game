#ifndef GREEDY_AGENT_H
#define GREEDY_AGENT_H

/* import libraries */
/******************************************/
#include <string>
#include "../../player.h"
#include "../../../environment/environment.h"
#include "../../../environment/data_structures.h"


/* class definition */
/******************************************/
class greedy_agent: public player
{

	public:
		/* constructor */
		greedy_agent(environment *game_environment, gameplay_id player_id);
		greedy_agent();
		~greedy_agent();

		/* strategy methods */
		int deploy_reserve_troops(int reserve_count); // deploy bonuce troops (if any)
		int march_troops(); // march troops to get ready for invasion
		int invade(); // attempts invasion

};

#endif 

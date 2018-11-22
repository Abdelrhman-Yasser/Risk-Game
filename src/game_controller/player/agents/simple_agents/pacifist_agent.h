#ifndef PACIFIST_AGENT_H
#define PACIFIST_AGENT_H

/* import libraries */
/******************************************/
#include <string>
#include <climits> // for MAX_INT var
#include "../../player.h"
#include "../../../environment/environment.h"
#include "../../../environment/data_structures.h"


/* class definition */
/******************************************/
class pacifist_agent: public player
{

	public:
		/* constructor */
		pacifist_agent(environment *game_environment, gameplay_id player_id);
		pacifist_agent();
		~pacifist_agent();

		/* strategy methods */
		int deploy_reserve_troops(int reserve_count); // deploy bonuce troops (if any)
		int march_troops(); // march troops to get ready for invasion
		int invade(); // attempts invasion

};

#endif 

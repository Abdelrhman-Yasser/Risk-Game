#ifndef PASSIVE_AGENT_H
#define PASSIVE_AGENT_H

/* import libraries */
/******************************************/
#include <string>
#include <climits>
#include <unistd.h>
#include "../../player.h"
#include "../../../environment/environment.h"
#include "../../../environment/data_structures.h"

#define WAIT_TIME 3 // in seconds


/* class definition */
/******************************************/
class passive_agent: public player
{

	public:
		/* constructor */
		passive_agent(environment *game_environment, gameplay_id player_id);
		passive_agent();
		~passive_agent();

		/* strategy methods */
		int deploy_reserve_troops(int reserve_count); // deploy bonuce troops (if any)
		int march_troops(); // march troops to get ready for invasion
		int invade(); // attempts invasion

	private:
		int get_user_input(char *country_name); 

};

#endif 

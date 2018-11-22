#ifndef AGGRESSIVE_AGENT_H
#define AGGRESSIVE_AGENT_H

/* import libraries */
/******************************************/
#include <string>
#include "../../player.h"
#include "../../../environment/environment.h"
#include "../../../environment/data_structures.h"


/* class definition */
/******************************************/
class aggressive_agent: public player
{

	public:
		/* constructor */
		aggressive_agent(environment *game_environment, gameplay_id player_id);
		aggressive_agent();
		~aggressive_agent();

		/* strategy methods */
		int deploy_reserve_troops(int reserve_count); // deploy bonuce troops (if any)
		int march_troops(); // march troops to get ready for invasion
		int invade(); // attempts invasion

	private:
		int max_troops_country_id = -1;
		//int get_user_input(char *country_name); 

};

#endif 

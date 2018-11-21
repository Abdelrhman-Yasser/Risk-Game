#ifndef HUMAN_H
#define HUMAN_H

/* import libraries */
/******************************************/
#include <string>
#include "../player.h"
#include "../../environment/environment.h"
#include "../../environment/data_structures.h"


/* class definition */
/******************************************/
class human: public player
{

	public:
		/* constructor */
		human(environment *game_environment, gameplay_id player_id);
		human();
		~human();

	protected:
		/* strategy methods */
		int deploy_reserve_troops(int reserve_count); // deploy bonuce troops (if any)
		int march_troops(); // march troops to get ready for invasion
		int invade(); // attempts invasion

	private:
		int get_user_input(char *country_name); 

};

#endif 

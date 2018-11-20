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

		/* interface methods */
		int make_move();

	private:
		int get_user_input(char *country_name); 

};

#endif 

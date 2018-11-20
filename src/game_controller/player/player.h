#ifndef PLAYER_H
#define PLAYER_H

/* import libraries */
/******************************************/
#include <string>
#include "../environment/environment.h"
#include "../environment/data_structures.h"


/* class definition */
/******************************************/
class player
{

	protected:
		environment *game_environment;
		player_type p_type;
		gameplay_id player_id;

	public:
		/* constructor */
		player(environment *game_environment, gameplay_id player_id);
		player();
		~player();

		/* interface methods */
		virtual int make_move(); // implements algorthim
		player_type get_type();
		gameplay_id get_gameplay_id();

};

#endif 

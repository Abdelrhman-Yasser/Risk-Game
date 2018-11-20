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

	public:
		/* constructor */
		player(environment *game_environment);
		player();
		~player();

		/* interface methods */
		virtual int make_move(); // implements algorthim
		player_type get_type();

};

#endif 

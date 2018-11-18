#ifndef PLAYER_H
#define PLAYER_H

/* import libraries */
/******************************************/
#include <string>
#include "../environment/environment.h"


/* class definition */
/******************************************/
enum player_type = {HUMAN, GREEDY};

class player
{

	protected:
		environment *game_environment;
		string army_color;

	public:
		/* constructor */
		player(environment *game_environment);
		~player();

		/* interface methods */
		virtual int make_move(); // implements algorthim

};

#endif 

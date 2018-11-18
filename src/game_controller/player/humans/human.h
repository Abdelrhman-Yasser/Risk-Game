#ifndef HUMAN_H
#define HUMAN_H

/* import libraries */
/******************************************/
#include <string>
#include "../player.h"
#include "../../environment/environment.h"


/* class definition */
/******************************************/
class human: public player
{

	public:
		/* constructor */
		human(environment *game_environment);
		~human();

		/* interface methods */
		int make_move();

	private:
		string get_user_input(); 

};

#endif 

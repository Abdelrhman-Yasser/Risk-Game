#ifndef GREEDY_AGENT_H
#define GREEDY_AGENT_H

/* import libraries */
/******************************************/
#include <string>
#include "../player.h"
#include "../../environment/environment.h"


/* class definition */
/******************************************/
class greedy_agent: public player
{

	public:
		/* constructor */
		greedy_agent(environment *game_environment);
		~greedy_agent();

		/* interface methods */
		int make_move();

	private:
		//string get_user_input(); 

};

#endif 

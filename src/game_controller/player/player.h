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
		// attributes
		environment *game_environment;
		player_type p_type;
		gameplay_id player_id;

		// strategy methods
		virtual int deploy_reserve_troops(int reserve_count); // deploy bonuce troops (if any)
		virtual int march_troops(); // march troops to get ready for invasion
		virtual int invade(); // attempts invasion

	public:
		/* constructor */
		player(environment *game_environment, gameplay_id player_id);
		player();
		~player();

		/* interface methods */
		int play_turn(int reserve_count);
		
		/* some getters */
		player_type get_type();
		gameplay_id get_gameplay_id();

};

#endif 

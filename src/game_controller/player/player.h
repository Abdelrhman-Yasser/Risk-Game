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
		int reserve_troops = 0;

	public:
		/* constructor */
		player(environment *game_environment, gameplay_id player_id);
		player();
		~player();

		/* interface methods */
		// strategy methods
		virtual int deploy_reserve_troops(int reserve_count); // deploy bonuce troops (if any)
		virtual int march_troops(); // march troops to get ready for invasion
		virtual int invade(); // attempts invasion
		
		/* some getters and setters */
		player_type get_type();
		gameplay_id get_gameplay_id();
		void set_reserve_troops(int reserve_troops);
		int get_reserve_troops();

};

#endif 

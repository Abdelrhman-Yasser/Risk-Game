#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

/* import libraries */
/******************************************/
#include "./environment/environment.h"
#include "./player/player_factory.h"
#include "./player/player.h"


/* class definition */
/******************************************/
class game_controller
{

	private:
		static const char init_file_dir[] = "./"; // directory of board init file
		environment *game_environment;
		player *player1;
		player *player2;
		enum player_turn;

	public:
		/* constructor */
		game_controller(enum player1_type, enum player2_type);
		~game_controller();

		/* interface methods */
		void start_new_game();

};

#endif 

#include "game_controller.h"

/* game init */
/*************************************/
game_controller::game_controller(enum player1_type, enum player2_type)
{
	// init environment
	this->environment = game_environment();
	this->game_environment.init(this->init_file_dir);

	// init players
	player_factory p_factory(&this->environment);
	this->player1 = player_factory.create_player(player1_type);
	this->player2 = player_factory.create_player(player2_type);

	// player turn
	this->player_turn = player1_type;
}

game_controller::~game_controller()
{
	// TODO
}

/* interface methods */
/*************************************/
void
start_new_game()
{
	// players take turns
	while(game_environment.get_game_status() == 1)
	{
		if(player_turn == player1.type)
		{
			// play
			player1.make_move();
			// change turns
			player_turn = player2.type;
			continue;
		}
		if(player_turn == player2.type)
		{
			// play
			player2.make_move();
			// change turns
			player_turn = player1.type;
			continue;
		}

	}

	// game ends
	string winner = environment.get_winner();
    std::cout << "Game Winner : " << winner << std::endl;

}
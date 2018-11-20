#include "game_controller.h"

/* game init */
/*************************************/
game_controller::game_controller(char *map_init_file_dir, char *ownership_init_file_dir, player_type p1_type, player_type p2_type)
{
	// init environment
	this->game_environment = environment(map_init_file_dir);

	// init players
	player_factory p_factory(&game_environment);
	this->player1 = p_factory.create_player(p1_type);
	this->player2 = p_factory.create_player(p2_type);

	// player turn
	this->player_turn = p1_type;
}

game_controller::~game_controller()
{
	// TODO
}

/* interface methods */
/*************************************/
void
game_controller::start_new_game()
{

	// players take turns
	while(game_environment.get_game_status() == 1)
	{
		// display game set
		system("clear");
		game_set_visualizer::display_game_board(&game_environment);

		// take turns
		if(player_turn == player1->get_type())
		{
			// play
			player1->make_move();
			// change turns
			player_turn = player2->get_type();
			continue;
		}
		if(player_turn == player2->get_type())
		{
			// play
			player2->make_move();
			// change turns
			player_turn = player1->get_type();
			continue;
		}

	}

	// game ends
	string winner = game_environment.get_winner();
    cout << "Game Winner : " << winner << std::endl;

}
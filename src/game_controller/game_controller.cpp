#include "game_controller.h"

/* game init */
/*************************************/
game_controller::game_controller(char *map_init_file_dir, char *ownership_init_file_dir, player_type p1_type, player_type p2_type)
{
	// init environment
	this->game_environment = environment(map_init_file_dir);

	// init players
	player_factory p_factory(&game_environment);
	this->player1 = p_factory.create_player(p1_type, gameplay_id::P1);
	this->player2 = p_factory.create_player(p2_type, gameplay_id::P2);

	// player turn
	this->player_turn = gameplay_id::P1;
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
	while(game_environment.get_game_status() == status::ONGOING)
	{
		// display game set
		game_set_visualizer::display_game_board(&game_environment);

		// take turns
		if(player_turn == player1->get_gameplay_id())
		{
			game_set_visualizer::announce_player_turn(player_turn, player1_reserve_troops);
			// play turn
			player1_reserve_troops = player1->play_turn(player1_reserve_troops);
			// change turns
			player_turn = player2->get_gameplay_id();
			continue;
		}
		if(player_turn == player2->get_gameplay_id())
		{
			game_set_visualizer::announce_player_turn(player_turn, player2_reserve_troops);
			// play turn
			player2_reserve_troops = player2->play_turn(player2_reserve_troops);
			// change turns
			player_turn = player1->get_gameplay_id();
			continue;
		}

	}

	// game ends
	gameplay_id winner = game_environment.get_winner();
	game_set_visualizer::display_winner_banner(winner);
    

}
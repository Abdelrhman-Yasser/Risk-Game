/* canvas variables */
/*****************************************/
var player1 = "";
var player2 = "";

var player_turn = "";
var game_status = "";

var country_list = [];
var border_list = [];
var continent_list = [];


/* gameplay controller */
/*****************************************/
function start_new_game()
{
	player *curr_player;
	// players take turns
	while(game_environment.get_game_status() == status::ONGOING)
	{
		// identify player currently playing
		curr_player = player1;
		if(player_turn == player2->get_gameplay_id())
		{
			curr_player = player2;
		}

		// strategy methods
		// 01. deploy reserve troops
		if(curr_player->get_reserve_troops() != 0)
		{
			gameset_visualizer::display_game_board(&game_environment, curr_player->get_gameplay_id(), curr_player->get_agent_type(), curr_player->get_reserve_troops(), action::DEPLOY);
			curr_player->deploy_reserve_troops(curr_player->get_reserve_troops());
			curr_player->set_reserve_troops(0);
		}
		// 02. march neiboring troops
		gameset_visualizer::display_game_board(&game_environment, curr_player->get_gameplay_id(), curr_player->get_agent_type(), curr_player->get_reserve_troops(), action::MARCH);
		curr_player->march_troops();
		// 03. attempt invasion
		gameset_visualizer::display_game_board(&game_environment, curr_player->get_gameplay_id(), curr_player->get_agent_type(), curr_player->get_reserve_troops(), action::INVADE);
		int reward = curr_player->invade();
		curr_player->set_reserve_troops(reward);

		// change turns
		player_turn = player1->get_gameplay_id();
		if(curr_player->get_gameplay_id() == player1->get_gameplay_id())
		{
			player_turn = player2->get_gameplay_id();
		}

	}

	// game ends
	gameplay_id winner = game_environment.get_winner();
	gameset_visualizer::display_winner_banner(winner);
}

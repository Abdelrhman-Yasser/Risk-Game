/* gameplay controller */
/*****************************************/
function gameplay_controller_start_game()
{
	console.log("game started");
	/*var curr_player;
	// players take turns
	while(game_status.toLowerCase() == "ongoing")
	{
		// identify player currently playing
		curr_player = "p1";
		if(player_turn.toLowerCase() == "p2")
		{
			curr_player = "p2";
		}

		// strategy methods
		// 01. deploy reserve troops
		if(curr_player->get_reserve_troops() != 0)
		{
			curr_player->deploy_reserve_troops(curr_player->get_reserve_troops());
			curr_player->set_reserve_troops(0);
		}
		// 02. march neiboring troops
		curr_player->march_troops();
		// 03. attempt invasion
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
	gameset_visualizer::display_winner_banner(winner);*/
}
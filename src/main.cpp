/* import libraries */
/*************************************/
#include "./graphics_engine/cli_engine/cli_engine.h"
#include "./game_engine/environment/data_structures.h"

/* run game as CLI */
/*************************************/
void
run_cli_game()
{
	char map_init_file_dir[] = "map_init.txt";
	char pop_init_file_dir[] = "population_init.txt";

	agent_type p1_type = agent_type::HUMAN;
	agent_type p2_type = agent_type::GREEDY;

	cli_engine game(map_init_file_dir, pop_init_file_dir, p1_type, p2_type);
	game.start_new_game();
}

/* main function */
/*************************************/
int
main(int argc, char const *argv[]) 
{ 
    
    run_cli_game();
    //run_gui_game();
    return 0; 
}

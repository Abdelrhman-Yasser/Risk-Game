#include "../../../../src/graphics_engine/cli_engine/cli_engine.h"
#include "../../../../src/game_engine/environment/data_structures.h"


#include <iostream> // read write screen
#include <string>
#include <vector>

using namespace std;

/* test 01 */
/******************************************/
void
test_cli_engine(){

	char map_init_file_dir[] = "map_init.txt";
	char pop_init_file_dir[] = "population_init.txt";

	agent_type p1_type = agent_type::HUMAN;
	agent_type p2_type = agent_type::GREEDY;

	cli_engine game(map_init_file_dir, pop_init_file_dir, p1_type, p2_type);
	game.start_new_game();
}




/* main function */
/******************************************/
int main()
{
	test_cli_engine();
	return 0;
}
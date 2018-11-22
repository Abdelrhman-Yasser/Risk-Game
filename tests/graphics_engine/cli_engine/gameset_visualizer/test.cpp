#include "../../../../src/game_engine/environment/environment.h"
#include "../../../../src/game_engine/environment/data_structures.h"
#include "../../../../src/graphics_engine/cli_engine/utilities/gameset_visualizer.h"

#include <iostream> // read write screen
#include <string>
#include <vector>

using namespace std;

/* test 01 */
/******************************************/
void
test_game_visualizer()
{
	// init file directory
	char map_init_file_dir[] = "./map_init.txt";
	char pop_init_file_dir[] = "./population_init.txt";

	// game environment
	environment game_set(map_init_file_dir, pop_init_file_dir);

	// display environment
	gameset_visualizer::display_game_board(&game_set, gameplay_id::P1, agent_type::HUMAN, 7, action::DEPLOY);
}

/* main function */
/******************************************/
int
main()
{
	test_game_visualizer();
	return 0;
}
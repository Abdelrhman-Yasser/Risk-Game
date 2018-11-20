#include "../../../src/game_controller/environment/environment.h"
#include "../../../src/game_controller/environment/data_structures.h"
#include "../../../src/graphics_controller/cli_controller/game_set_visualizer.h"

#include <iostream> // read write screen
#include <string>
#include <vector>

using namespace std;

/* test 01 */
/******************************************/
void
test_cli_game_display()
{
	// init file directory
	char init_file_dir[] = "./game_init.txt";

	// game environment
	environment game(init_file_dir);

	// display environment
	game_set_visualizer::display_game_board(&game);
}

/* main function */
/******************************************/
int
main()
{
	test_cli_game_display();
	return 0;
}
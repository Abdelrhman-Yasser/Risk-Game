#include "../../../src/game_controller/game_controller.h"
#include "../../../src/game_controller/environment/data_structures.h"


#include <iostream> // read write screen
#include <string>
#include <vector>

using namespace std;

/* test 01 */
/******************************************/
void
test_game_controller(){

	char map_init_file_dir[] = "map_init.txt";
	char ownership_init_file_dir[] = "map_init.txt";
	game_controller game(map_init_file_dir, ownership_init_file_dir, agent_type::HUMAN, agent_type::PASSIVE);
	game.start_new_game();
}




/* main function */
/******************************************/
int main()
{
	test_game_controller();
	return 0;
}
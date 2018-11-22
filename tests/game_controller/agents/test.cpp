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
	char pop_init_file_dir[] = "population_init.txt";

	agent_type p1_type = agent_type::HUMAN;
	agent_type p2_type = agent_type::GREEDY;

	game_controller game(map_init_file_dir, pop_init_file_dir, p1_type, p2_type);
	game.start_new_game();
}




/* main function */
/******************************************/
int main()
{
	test_game_controller();
	return 0;
}
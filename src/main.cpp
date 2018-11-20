/* import libraries */
/*************************************/
#include "./game_controller/game_controller.h"
#include "./game_controller/environment/data_structures.h"


/* main function */
/*************************************/
int
main(int argc, char const *argv[]) 
{ 
    char map_init_file_dir[] = "map_init.txt";
	char ownership_init_file_dir[] = "map_init.txt";
	game_controller game(map_init_file_dir, ownership_init_file_dir, player_type::HUMAN, player_type::HUMAN);
	game.start_new_game();
    
    return 0; 
}

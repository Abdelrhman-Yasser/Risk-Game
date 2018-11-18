/* import libraries */
/*************************************/
#include "./game_controller/game_controller.h"


/* main function */
/*************************************/
int
main(int argc, char const *argv[]) 
{ 
    enum player1_type = HUMAN;
    enum player2_type = GREEDY;

    game_controller controller(player1_type, player2_type);
    controller.start_new_game();
    
    return 0; 
}

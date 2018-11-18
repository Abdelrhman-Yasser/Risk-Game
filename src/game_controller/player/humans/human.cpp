#include "human.h"

/* init player */
/******************************************/
/* constructor */
human::human(environment *game_environment)
{
	player::player(game_environment);
}

/* destructor */
human::~human()
{
	// TODO
}


/* interface methods */
/******************************************/
int
human::make_move()
{
	// get user input
	string user_input = get_user_input();

	// apply move
	this->game_environment.invade(/* some move */);
}


/* internal methods */
/******************************************/
string
human::get_user_input()
{
	// scan user command
	char user_input[1024] = {0};
	printf("Enter Valid Move: ");
	scanf("%s", user_input);

	return user_input;
}
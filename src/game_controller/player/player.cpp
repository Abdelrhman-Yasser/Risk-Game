/* import libraries */
/******************************************/
#include "player.h"

/* constructor */
player::player(environment *game_environment)
{
	this->game_environment = game_environment;
}

player::player()
{
	// nothing
}

/* destructor */
player::~player()
{
	// TODO
}


player_type
player::get_type()
{
	return this->p_type;
}

int
player::make_move()
{
	// nothing
	cout << "from player.cpp" << endl;
	return 0;
}
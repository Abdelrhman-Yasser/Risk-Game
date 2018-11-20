/* import libraries */
/******************************************/
#include "player.h"

/* constructor */
player::player(environment *game_environment, gameplay_id player_id)
{
	this->game_environment = game_environment;
	this->player_id = player_id;
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

gameplay_id
player::get_gameplay_id()
{
	return this->player_id;
}

int
player::make_move()
{
	// nothing
	cout << "from player.cpp" << endl;
	return 0;
}
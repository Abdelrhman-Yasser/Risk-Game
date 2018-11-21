#include "player.h"

/* constructor */
/******************************************/
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

/* some getters */
/******************************************/
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

void
player::set_reserve_troops(int reserve_troops)
{
	this->reserve_troops = reserve_troops;
}
int
player::get_reserve_troops()
{
	return this->reserve_troops;
}

/* strategy methods */
/******************************************/
int
player::deploy_reserve_troops(int reserve_count)
{
	// nothing
	cout << "from player.cpp" << endl;
	return 0;
}

int
player::march_troops()
{
	// nothing
	cout << "from player.cpp" << endl;
	return 0;
}

int
player::invade()
{
	// nothing
	cout << "from player.cpp" << endl;
	return 0;
}


/* interface methods */
/******************************************/
/*int
player::play_turn(int reserve_count)
{
	int sucess;
	// 01. deploy reserve/bonuce (required)
	if(reserve_count != 0)
	{
		sucess = deploy_reserve_troops(reserve_count);
		if(sucess == 0){
			cout << "something went wrong" << endl;
		}
	}
	// 02. march troops (optional - can skip)
	march_troops();
	// 03. make invasion (optional - can skip)
	int reward = invade();
	return reward; // returns new reward
}*/
#include "player_factory.h"

/* game init */
/*************************************/
player_factory::player_factory(environment *game_environment)
{
	this->environment = game_environment;
}

player_factory::~player_factory()
{
	// TODO
}

/* interface methods */
/*************************************/
player
create_player(enum player_type)
{
	if(player_type == p_type.HUMAN)
	{
		human tmp(game_environment);
		return &tmp;
	}

	if(player_type == p_type.GREEDY)
	{
		greedy_agent tmp(game_environment);
		return &tmp;
	}

}
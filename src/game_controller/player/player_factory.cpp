#include "player_factory.h"

/* game init */
/*************************************/
player_factory::player_factory(environment *game_environment)
{
	this->game_environment = game_environment;
}

player_factory::~player_factory()
{
	// TODO
}

/* interface methods */
/*************************************/
player*
player_factory::create_player(player_type p_type, gameplay_id player_id)
{
	if(p_type == player_type::HUMAN)
	{
		human *tmp = new human(game_environment, player_id);
		return tmp;
	}

	/*if(p_type == player_type::GREEDY)
	{
		greedy_agent tmp(game_environment);
		return &tmp;
	}*/

}
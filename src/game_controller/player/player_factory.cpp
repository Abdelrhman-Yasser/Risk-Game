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
player_factory::create_player(agent_type p_type, gameplay_id player_id)
{
	if(p_type == agent_type::HUMAN)
	{
		human *tmp = new human(game_environment, player_id);
		return tmp;
	}

	if(p_type == agent_type::PASSIVE)
	{
		passive_agent *tmp = new passive_agent(game_environment, player_id);
		return tmp;
	}

	if(p_type == agent_type::AGGRESSIVE)
	{
		aggressive_agent *tmp = new aggressive_agent(game_environment, player_id);
		return tmp;
	}

	if(p_type == agent_type::PACIFIST)
	{
		pacifist_agent *tmp = new pacifist_agent(game_environment, player_id);
		return tmp;
	}

	if(p_type == agent_type::GREEDY)
	{
		greedy_agent *tmp = new greedy_agent(game_environment, player_id);
		return tmp;
	}

}
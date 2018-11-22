#include "greedy_agent.h"

/* init player */
/******************************************/
/* constructor */
greedy_agent::greedy_agent(environment *game_environment, gameplay_id player_id) : player(game_environment, player_id){
	this->p_type = agent_type::GREEDY;	
}

greedy_agent::greedy_agent()
{
	// TODO
}

/* destructor */
greedy_agent::~greedy_agent()
{
	// TODO
}

/* utility methods */
/******************************************/


/* interface methods */
/******************************************/
int
greedy_agent::deploy_reserve_troops(int reserve_count)
{
	return 1;
}

int
greedy_agent::march_troops()
{
	// no marching - UNKNOWN
	return 1;
}

int
greedy_agent::invade()
{
	return 0; // no invasion
}


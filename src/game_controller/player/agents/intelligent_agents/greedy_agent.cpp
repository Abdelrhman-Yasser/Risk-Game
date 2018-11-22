#include "greedy_agent.h"

/* init player */
/******************************************/
/* constructor */
greedy_agent::greedy_agent(environment *game_environment)
{
	player::player(game_environment);
}

/* destructor */
greedy_agent::~greedy_agent()
{
	// TODO
}


/* interface methods */
/******************************************/
int
greedy_agent::make_move()
{
	// apply greedy algorithm

	// make move
	this->game_environment.invade(/* some move */);
}


/* internal methods */
/******************************************/

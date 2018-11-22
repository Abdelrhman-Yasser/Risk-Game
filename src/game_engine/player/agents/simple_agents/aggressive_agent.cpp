#include "aggressive_agent.h"

/* init player */
/******************************************/
/* constructor */
aggressive_agent::aggressive_agent(environment *game_environment, gameplay_id player_id) : player(game_environment, player_id){
	this->p_type = agent_type::AGGRESSIVE;	
}

aggressive_agent::aggressive_agent()
{
	// TODO
}

/* destructor */
aggressive_agent::~aggressive_agent()
{
	// TODO
}

/* utility methods */
/******************************************/


/* interface methods */
/******************************************/
int
aggressive_agent::deploy_reserve_troops(int reserve_count)
{
	// deploy to country with max troops - PASSIVE
	int max_troops_country_id = -1;
	int max_troops_count = 0;

	// get country with min troops
	vector<struct country>::iterator ptr;
	for (ptr = game_environment->get_country_list()->begin(); ptr < game_environment->get_country_list()->end(); ptr++) 
	{
		if(ptr->owner_id == this->get_gameplay_id())
		{
			if(ptr->troops_count > max_troops_count)
			{
				max_troops_count = ptr->troops_count;
				max_troops_country_id = ptr->id;
			}
		}
	}
	this->max_troops_country_id = max_troops_country_id;

	// depoly troops
	game_environment->deploy_reserve_troops(player_id, max_troops_country_id, reserve_count);
	return 1;
}

int
aggressive_agent::march_troops()
{
	// no marching - UNKNOWN
	return 1;
}

int
aggressive_agent::invade()
{
	// invade with the country with max troops
	int i = game_environment->get_country_list()->at(this->max_troops_country_id - 1).troops_count;

	// find neighboring enemy that we can invade
	vector<struct border>::iterator ptr;
	for (ptr = game_environment->get_border_list()->begin(); ptr < game_environment->get_border_list()->end(); ptr++) 
	{
		// country on 1st side of border
		if(ptr->country1 == this->max_troops_country_id)
		{
			// check if neighbor is enemy
			if(game_environment->get_country_list()->at(ptr->country2 - 1).owner_id == player_id)
			{
				continue;
			}
			// attempt invasion
			int j = game_environment->get_country_list()->at(ptr->country2 - 1).troops_count;
			if(i - j > 1) // do invade
			{
				int reward = this->game_environment->invade(player_id, this->max_troops_country_id, ptr->country2);
				return reward;
			}
		}
		// country on 2nd side of border
		if(ptr->country2 == this->max_troops_country_id)
		{
			// check if neighbor is enemy
			if(game_environment->get_country_list()->at(ptr->country1 - 1).owner_id == player_id)
			{
				continue;
			}
			// attempt invasion
			int j = game_environment->get_country_list()->at(ptr->country1 - 1).troops_count;
			if(i - j > 1) // do invade
			{
				int reward = this->game_environment->invade(player_id, this->max_troops_country_id, ptr->country1);
				return reward;
			}
		}
	}

	return 0; // no invasion
}


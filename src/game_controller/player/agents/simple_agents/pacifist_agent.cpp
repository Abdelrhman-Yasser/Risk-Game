#include "pacifist_agent.h"

/* init player */
/******************************************/
/* constructor */
pacifist_agent::pacifist_agent(environment *game_environment, gameplay_id player_id) : player(game_environment, player_id){
	this->p_type = agent_type::PACIFIST;	
}

pacifist_agent::pacifist_agent()
{
	// TODO
}

/* destructor */
pacifist_agent::~pacifist_agent()
{
	// TODO
}

/* utility methods */
/******************************************/


/* interface methods */
/******************************************/
int
pacifist_agent::deploy_reserve_troops(int reserve_count)
{
	// deploy to country with least troops - PASSIVE
	int min_troops_country_id = -1;
	int min_troops_count = INT_MAX;

	// get country with min troops
	vector<struct country>::iterator ptr;
	for (ptr = game_environment->get_country_list()->begin(); ptr < game_environment->get_country_list()->end(); ptr++) 
	{
		if(ptr->owner_id == this->get_gameplay_id())
		{
			if(ptr->troops_count < min_troops_count)
			{
				min_troops_count = ptr->troops_count;
				min_troops_country_id = ptr->id;
			}
		}
	}

	// depoly troops
	game_environment->deploy_reserve_troops(player_id, min_troops_country_id, reserve_count);
	return 1;
}

int
pacifist_agent::march_troops()
{
	// no marching - UNKNOWN
	return 1;
}

int
pacifist_agent::invade()
{
	int min_troops_country_id = -1;

	return 0; // no invasion
}


#include "passive_agent.h"

/* init player */
/******************************************/
/* constructor */
passive_agent::passive_agent(environment *game_environment, gameplay_id player_id) : player(game_environment, player_id){
	this->p_type = agent_type::PASSIVE;	
}

passive_agent::passive_agent()
{
	// TODO
}

/* destructor */
passive_agent::~passive_agent()
{
	// TODO
}

/* utility methods */
/******************************************/
int
passive_agent::get_user_input(char *msg)
{
	// scan user command
	int user_input;
	cout << msg;
	scanf("%d", &user_input);

	return user_input;
}


/* interface methods */
/******************************************/
int
passive_agent::deploy_reserve_troops(int reserve_count)
{
	cout << "\t<< deploy reserve troops >>" << endl;
	sleep(WAIT_TIME);
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
passive_agent::march_troops()
{
	// no marching - PASSIVE
	cout << "\t<< march troops >>" << endl;
	sleep(WAIT_TIME);
	return 1;
}

int
passive_agent::invade()
{
	// no invasion - PASSIVE
	cout << "\t<< attempt invasion >>" << endl;
	sleep(WAIT_TIME);
	return 0;
}


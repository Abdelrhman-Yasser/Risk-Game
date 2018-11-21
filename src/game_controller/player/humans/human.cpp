#include "human.h"

/* init player */
/******************************************/
/* constructor */
human::human(environment *game_environment, gameplay_id player_id) : player(game_environment, player_id){
	this->p_type = player_type::HUMAN;	
}

human::human()
{
	// TODO
}

/* destructor */
human::~human()
{
	// TODO
}

/* utility methods */
/******************************************/
int
human::get_user_input(char *msg)
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
human::deploy_reserve_troops(int reserve_count)
{
	// get user input
	cout << "\t<< deploy reserve troops >>" << endl;
	int target_country = get_user_input("deploy TO : \t");

	// depoly troops
	game_environment->deploy_reserve_troops(player_id, target_country, reserve_count);
	return 1;
}

int
human::march_troops()
{
	// get user input
	cout << "\t<< march troops >>" << endl;
	int skip_flag = get_user_input("MARCH? 1/0 : \t");
	if(skip_flag != 1){return 0;}

	int from_country_id = get_user_input("march FROM : \t");
	int to_country_id = get_user_input("march TO : \t");
	int troops_count = get_user_input("troops count : \t");

	// apply move
	this->game_environment->march_troops(player_id, from_country_id, to_country_id, troops_count);
	return 1;
}

int
human::invade()
{
	// get user input
	cout << "\t<< attempt invasion >>" << endl;
	int skip_flag = get_user_input("INVADE? 1/0 : \t");
	if(skip_flag != 1){return 0;} // no reward

	int from_country_id = get_user_input("invade FROM : \t");
	int to_country_id = get_user_input("invade TARGET : ");

	// apply move
	int reward = this->game_environment->invade(player_id, from_country_id, to_country_id);
	return reward;
}


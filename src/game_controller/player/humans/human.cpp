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


/* interface methods */
/******************************************/
int
human::make_move()
{
	//cout << "from human.cpp" << endl;
	// get user input
	int from_country_id = get_user_input("FROM");
	int to_country_id = get_user_input("TO");

	// apply move
	this->game_environment->invade(player_id, from_country_id, to_country_id);
}


/* internal methods */
/******************************************/
int
human::get_user_input(char *country_name)
{
	// scan user command
	int user_input;
	cout << "enter " << country_name << " country : ";
	scanf("%d", &user_input);

	return user_input;
}
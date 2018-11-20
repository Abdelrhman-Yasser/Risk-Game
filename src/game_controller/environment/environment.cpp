#include "environment.h"

/* init game environment */
/******************************************/
/* constructor */
environment::environment(char *map_init_file_dir)
{
	// game map
	init_game_map(map_init_file_dir);
	// country ownership and troops count
	//init_ownership();
	// game status
	this->game_status = 1;
	this->winner = "none";

}

/* destructor */
environment::environment()
{
	// nothing
}

/* destructor */
environment::~environment()
{
	// TODO
}

void
environment::init_game_map(char *map_init_file_dir)
{
	// parse input file
	file_parser parser(map_init_file_dir);

	// create countries
	// for testing purpose - game population
	int country_count = parser.get_country_count();
	int counter = 1;
	int player_id = 1;
	while(counter <= country_count)
	{
		struct country tmp;
		tmp.id = counter;
		tmp.troops_count = 5;
		tmp.p_type = player_type::HUMAN; // dummy creation

		if(player_id == 1)
		{
			tmp.o_id = owner_id::P1;
			player_id = 2;
		}else{
			tmp.o_id = owner_id::P2;
			player_id = 1;
		}
		
		this->country_list.push_back(tmp);
		counter++;
	}

	// create borders
	parser.obtain_border_list(&(this->border_list));

	// create continents
	parser.obtain_continent_list(&(this->continent_list));
}

void
environment::init_ownership(char *ownership_init_file_dir)
{

}

/* getter methods */
/******************************************/
int
environment::get_game_status()
{
	return this->game_status;
}

string
environment::get_winner()
{
	return this->winner;
}

vector<struct country> 
*environment::get_country_list()
{
	return &country_list;
}

vector<struct border> 
*environment::get_border_list()
{
	return &border_list;
}

vector<struct continent> 
*environment::get_continent_list()
{
	return &continent_list;
}


/*environment*
environment::get_game_environment()
{
	return *this;
}*/

/* interface methods */
/******************************************/
int
environment::invade(int from_country_id, int to_country_id)
{
	// apply move
	// update troops count and ownership
	int i = country_list.at(from_country_id).troops_count;
	int j = country_list.at(to_country_id).troops_count;
	if((i - j) > 1) // successfull invasion
	{
		// reduce troops
		country_list.at(from_country_id).troops_count = i-2;
		country_list.at(from_country_id).troops_count = j-2;
		// prompt user to distribute new troops
		int reward = 2;
			// prompt user
			// apply command

	}else{ // unsucessfull invasion
		
	}

	// check continent ownership

	// update game status

}
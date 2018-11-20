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
		tmp.p_type = player_type::HUMAN; // dummy creation

		if(player_id == 1)
		{
			tmp.troops_count = 5;
			tmp.owner_id = gameplay_id::P1;
			player_id = 2;
		}else{
			tmp.troops_count = 3;
			tmp.owner_id = gameplay_id::P2;
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

/* interface methods */
/******************************************/
int
environment::invade(gameplay_id current_player, int from_country_id, int to_country_id)
{
	/* 00. checks */
	// check there's a border
	if(border_exists(from_country_id, to_country_id) == 0){return 0;} // throws exception
	// check invader owns 'from_country'
	if(is_owner(current_player, from_country_id) == 0){return 0;} // throws exception

	/* 01. apply move */
	// update troops count and ownership
	int i = country_list.at(from_country_id - 1).troops_count;
	int j = country_list.at(to_country_id - 1).troops_count;
	if((i - j) > 1) // successfull invasion
	{
		// reduce troops
		country_list.at(from_country_id - 1).troops_count = i-2;
		country_list.at(to_country_id - 1).troops_count = j-2;
		
		// update ownership
		country_list.at(to_country_id - 1).p_type = country_list.at(from_country_id - 1).p_type;
		country_list.at(to_country_id - 1).owner_id = country_list.at(from_country_id - 1).owner_id;

		// prompt user to distribute new troops
		int reward = 2;
		// prompt user to distribute troops
		// apply command

	}else{ // unsucessfull invasion
		
	}

	/* 02. check continent ownership */

	/* 03. update game status */


	return 1;

}


int
environment::border_exists(int country1_id, int country2_id)
{
	vector<struct border>::iterator ptr;
	for (ptr = border_list.begin(); ptr < border_list.end(); ptr++) 
	{
		if((ptr->country1 == country1_id) && (ptr->country2 == country2_id))
		{return 1;}

		if((ptr->country1 == country2_id) && (ptr->country2 == country1_id))
		{return 1;}

	}
	return 0;
}

int
environment::is_owner(gameplay_id test_player, int country_id)
{
	return country_list.at(country_id - 1).owner_id == test_player;
}

/*
int
environment::owns_continent(owner_id test_player, )
{

}*/
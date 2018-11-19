#include "environment.h"

/* init game environment */
/******************************************/
/* constructor */
environment::environment(char *init_file_dir)
{
	// parse input file
	file_parser parser(init_file_dir);

	// create countries
	this->country_list = vector<struct country>();
	int count = file_parser.get_country_count();
	for(count > 0)
	{
		struct country tmp;
		tmp.id = 1;
		tmp.troops_count = 0;
		tmp.owner = NONE;
		this->country_list.push_back(tmp);
	}

	// create borders
	parser.obtain_border_list(&(this->border_list));

	// create continents
	parser.obtain_continent_list(&(this->continent_list));

	// game status
	this->game_status = 1;
}

/* destructor */
environment::~environment()
{
	// TODO
}

/* interface methods */
/******************************************/
int
environment::invade()
{
	
}

/* getter methods */
/******************************************/
int
environment::get_game_status()
{
	return this->game_status;
}

environment*
environment::get_game_environment()
{
	return *this;
}


#include "environment.h"

/* init game environment */
/******************************************/
/* constructor */
environment::environment(char *init_file_dir)
{
	// parse input file
	file_parser parser(init_file_dir);

	// create countries
	int country_count = parser.get_country_count();
	int counter = 1;
	while(counter <= country_count)
	{
		struct country tmp;
		tmp.id = counter;
		tmp.troops_count = 0;
		tmp.owner = 0;//tmp.owner = NONE; 
		this->country_list.push_back(tmp);
		counter++;
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
environment::invade(int from_country_id, int to_country_id)
{
	
}

/* getter methods */
/******************************************/
int
environment::get_game_status()
{
	return this->game_status;
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
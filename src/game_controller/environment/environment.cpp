#include "environment.h"

/* init game environment */
/******************************************/
/* constructor */
environment::environment(string init_file_dir)
{
	// nothing
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


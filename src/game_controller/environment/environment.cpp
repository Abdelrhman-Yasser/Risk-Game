#include "environment.h"

/* init game environment */
/******************************************/
/* constructor */
environment::environment()
{
	// nothing
}

/* destructor */
environment::~environment()
{
	// TODO
}

int
environment::init(string init_file_dir, enum p1_type, enum p2_type)
{
	// initialize
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


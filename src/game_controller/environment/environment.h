#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

/* import libraries */
/******************************************/
#include <string>


/* class definition */
/******************************************/
class environment
{

	private:
		// vector<node> city_list;
		// vector<edge> border_list;
		// vector<vector<node> > continents;
		int game_status;

	public:
		/* constructor */
		environment();
		~environment();

		/* interface methods */
		int invade(/* some move */);
		int get_game_status();
		environment *get_game_environment();

	private:
		/* interface methods */
		int init(string init_file_dir, enum p1_type, enum p2_type);

};

#endif 

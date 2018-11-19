#ifndef CONTAINER
#define ENVIRONMENT_H

/* import libraries */
/******************************************/
#include <string>


/* global variables */
/******************************************/
struct country {
	enum owner_type; // HUMAN, GREEDY
	int troops_count;
	int id;
}

struct border {
	struct country *country1;
	struct country *country2;
}


/* class definition */
/******************************************/
class environment
{
	private:
		vector<country> country_list;
		vector<border> border_list;
		vector<vector<country> > continent_list;
		int game_status;

	public:
		/* constructor */
		environment(string init_file_dir);
		~environment();

		/* interface methods */
		int invade(int from_country_id, int to_country_id); // attempts to make move
		int get_game_status();
		environment *get_game_environment();

};

#endif 
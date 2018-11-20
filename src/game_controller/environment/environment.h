#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

/* import libraries */
/******************************************/
#include <string>
#include "data_structures.h"
#include "../utilities/file_parser.h"

using namespace std;


/* class definition */
/******************************************/
class environment
{
	private:
		vector<struct country> country_list;
		vector<struct border> border_list;
		vector<struct continent> continent_list;
		int game_status;
		string winner;

		// utility methods
		void init_game_map(char *map_init_file_dir); // game map (country, border, continent)
		void init_ownership(char *ownership_init_file_dir); // country ownership, and troops count
		int border_exists(int country1_id, int country2_id); // checks if there's border between two given countries
		int is_owner(gameplay_id test_player, int country_id); // checks ownership of country for given player

	public:
		/* constructor */
		environment(char *map_init_file_dir);
		environment();
		~environment();

		/* interface methods */
		int invade(gameplay_id current_player, int from_country_id, int to_country_id); // attempts to make move

		// some getters
		int get_game_status();
		string get_winner();
		vector<struct country> *get_country_list();
		vector<struct border> *get_border_list();
		vector<struct continent> *get_continent_list();


};

#endif 
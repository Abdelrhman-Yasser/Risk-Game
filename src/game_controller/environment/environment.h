#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

/* import libraries */
/******************************************/
#include <string>
#include "data_structures.h"
#include "../utilities/file_parser.h"

using namespace std;
#define INVASION_REWARD 2

/* class definition */
/******************************************/
class environment
{
	private:
		vector<struct country> country_list;
		vector<struct border> border_list;
		vector<struct continent> continent_list;
		status game_status;
		gameplay_id winner;

		// utility methods
		void init_game_map(char *map_init_file_dir); // game map (country, border, continent)
		void init_ownership(char *ownership_init_file_dir); // country ownership, and troops count
		int border_exists(int country1_id, int country2_id); // checks if there's border between two given countries
		int is_owner(gameplay_id test_player, int country_id); // checks ownership of country for given player
		int owns_continent(gameplay_id test_player, int continent_id);
		gameplay_id game_ended(gameplay_id test_player);

	public:
		/* constructor */
		environment(char *map_init_file_dir);
		environment();
		~environment();

		/* interface methods */
		int deploy_reserve_troops(gameplay_id owner_id, int target_country_id, int reserve_count);
		int march_troops(gameplay_id owner_id, int from_country_id, int to_country_id, int troops_count);
		int invade(gameplay_id owner_id, int from_country_id, int to_country_id); // attempts to make move

		// some getters
		status get_game_status();
		gameplay_id get_winner();
		vector<struct country> *get_country_list();
		vector<struct border> *get_border_list();
		vector<struct continent> *get_continent_list();


};

#endif 
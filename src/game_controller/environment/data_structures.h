#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/* import libraries */
/******************************************/
#include <vector>
using namespace std;

/* definitions - environment variables */
/******************************************/
enum player_type {HUMAN, GREEDY}; // agent type
enum gameplay_id {P1, P2, NONE}; // player 1 or 2 or ...
enum status {ONGOING, ENDED};

struct country {
	gameplay_id owner_id; // p1 or p2
	int troops_count;
	int id;
	int continent_id;
};

struct border {
	int country1; // index of country1
	int country2; // index of country2
};

struct continent {
	int reward;
	gameplay_id owner_id = gameplay_id::NONE;
	vector<int> country_list; // indices of comprising countries
};



#endif 
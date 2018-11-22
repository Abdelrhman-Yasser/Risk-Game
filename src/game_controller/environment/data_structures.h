#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/* import libraries */
/******************************************/
#include <vector>
using namespace std;

/* definitions - environment variables */
/******************************************/
enum agent_type {HUMAN, PASSIVE, AGGRESSIVE, PACIFIST, GREEDY}; // agent type
enum gameplay_id {NONE, P1, P2}; // player 1 or 2 or ...
enum status {ONGOING, ENDED};
enum action {DEPLOY, MARCH, INVADE};

struct country {
	gameplay_id owner_id; // p1 or p2
	int troops_count;
	int id;
	int continent_id = -1;
};

struct border {
	int country1; // ID of country1
	int country2; // ID of country2
};

struct continent {
	int reward;
	gameplay_id owner_id = gameplay_id::NONE;
	vector<int> country_list; // indices of comprising countries
};



#endif 
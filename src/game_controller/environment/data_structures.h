#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/* import libraries */
/******************************************/
#include <vector>
using namespace std;

/* definitions - environment variables */
/******************************************/
enum player_type {NONE, HUMAN, GREEDY}; // agent type
enum gameplay_id {P1, P2}; // player 1 or 2 or ...

struct country {
	player_type p_type; // HUMAN, GREEDY
	gameplay_id owner_id; // p1 or p2
	int troops_count;
	int id;
};

struct border {
	int country1; // index of country1
	int country2; // index of country2
};

struct continent {
	int reward;
	vector<int> country_list; // indices of comprising countries
};



#endif 
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/* import libraries */
/******************************************/
#include <vector>
using namespace std;

/* definitions - environment variables */
/******************************************/
struct country {
	//enum player_type owner; // HUMAN, GREEDY
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

struct init_info {
	int country_count;
	int border_count;
	int continent_count;

	vector<struct border> edge_list;
	vector<struct continent> continent_list;
};



#endif 
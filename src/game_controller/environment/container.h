#ifndef CONTAINER_H
#define CONTAINER_H

/* definitions */
/******************************************/
#include <vector>
using namespace std;

struct edge {
	int point1;
	int point2;
};

struct continent {
	int reward;
	vector<int> country_list;
};

struct init_info {
	int country_count;
	int border_count;
	int continent_count;

	vector<struct edge> edge_list;
	vector<struct continent> continent_list;
};

#endif 
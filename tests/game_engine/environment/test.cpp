#include "../../../src/game_engine/environment/environment.h"
#include "../../../src/game_engine/environment/data_structures.h"

#include <iostream> // read write screen
#include <string>
#include <vector>

using namespace std;

/* test 01 */
/******************************************/
void
test_game_init ()
{
	// init file directory
	char map_init_file_dir[] = "./map_init.txt";
	char pop_init_file_dir[] = "./population_init.txt";

	// game environment
	environment game(map_init_file_dir, pop_init_file_dir);

	// data structures
	vector<struct country> country_list;
	vector<struct border> border_list;
	vector<struct continent> continent_list;

	// test counts
	cout << "testing counts : ----------------------------------" << endl;
	cout << "country count : " << game.get_country_list()->size() << endl;
	cout << "border count : " << game.get_border_list()->size() << endl;
	cout << "continent count : " << game.get_continent_list()->size() << endl;

	// test edge list
	cout << "testing edge list : -------------------------------" << endl;
	vector<struct border>::iterator ptr1;
	for (ptr1 = game.get_border_list()->begin(); ptr1 < game.get_border_list()->end(); ptr1++) 
	{
		cout << "edge : " << ptr1->country1 << "\t" << ptr1->country2 << endl;
	}

	// test continents
	cout << "testing continents : ------------------------------" << endl;
	vector<struct continent>::iterator ptr2;
	for (ptr2 = game.get_continent_list()->begin(); ptr2 < game.get_continent_list()->end(); ptr2++) 
	{
		cout << "continent (i) : " << endl;
		cout << "reward = " << ptr2->reward << endl;

		cout << "countries : " << endl;
		vector<int>::iterator ptr3;
		for (ptr3 = ptr2->country_list.begin(); ptr3 < ptr2->country_list.end(); ptr3++) 
		{
			cout << *ptr3 << "\t";
		}
		cout << endl;
	}
}

/* main function */
/******************************************/
int
main()
{
	test_game_init();
	return 0;
}
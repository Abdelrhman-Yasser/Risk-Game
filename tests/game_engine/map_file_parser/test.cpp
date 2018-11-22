#include "../../../src/game_engine/utilities/io_handler.h"
#include "../../../src/game_engine/utilities/map_file_parser.h"
#include "../../../src/game_engine/environment/data_structures.h"

#include <iostream> // read write screen
#include <string>
#include <vector>

using namespace std;

/* test 01 */
/******************************************/
void
test_map_file_parser ()
{
	// data structures
	vector<struct country> country_list;
	vector<struct border> border_list;
	vector<struct continent> continent_list;

	// initialize file parser
	char init_file_dir[] = "./map_init.txt";
	map_file_parser parser(init_file_dir);

	// get borders
	parser.obtain_border_list(&border_list);

	// get continents
	parser.obtain_continent_list(&continent_list);

	// test counts
	cout << "testing counts : ----------------------------------" << endl;
	cout << "country count : " << parser.get_country_count() << endl;
	cout << "border count : " << parser.get_border_count() << endl;
	cout << "continent count : " << parser.get_continent_count() << endl;

	// test edge list
	cout << "testing edge list : -------------------------------" << endl;
	vector<struct border>::iterator ptr1;
	for (ptr1 = border_list.begin(); ptr1 < border_list.end(); ptr1++) 
	{
		cout << "edge : " << ptr1->country1 << "\t" << ptr1->country2 << endl;
	}

	// test continents
	cout << "testing continents : ------------------------------" << endl;
	vector<struct continent>::iterator ptr2;
	for (ptr2 = continent_list.begin(); ptr2 < continent_list.end(); ptr2++) 
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
int main()
{
	test_map_file_parser();
	return 0;
}
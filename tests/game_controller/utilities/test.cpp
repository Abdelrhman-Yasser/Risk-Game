#include "../../../src/game_controller/utilities/io_handler.h"
#include "../../../src/game_controller/utilities/file_parser.h"
#include "../../../src/game_controller/environment/data_structures.h"

#include <iostream> // read write screen
#include <string>
#include <vector>

using namespace std;

/* test 01 */
/******************************************/
void
test_io_handler(){

	// read data from file
	char file_dir[] = "game_init.txt";
	vector<string> tmp;
	io_handler::read_file(file_dir, &tmp);

	// read data
	vector<string>::iterator ptr;
	for (ptr = tmp.begin()+1; ptr < tmp.end(); ptr++) 
	{
		cout << "line : " << *ptr << endl;
	}
}

/* test 02 */
/******************************************/
void
test_file_parser ()
{
	// data structures
	vector<struct country> country_list;
	vector<struct border> border_list;
	vector<struct continent> continent_list;

	// initialize file parser
	char init_file_dir[] = "./game_init.txt";
	file_parser parser(init_file_dir);

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
	//test_io_handler();
	test_file_parser();
	return 0;
}
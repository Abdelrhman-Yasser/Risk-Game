#include "io_handler.h"
#include "file_parser.h"
#include "../environment/container.h"

#include <iostream> // read write screen
#include <string>
#include <vector>

using namespace std;

/* main testing */
/******************************************/
int test_io_handler () {

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

	return 0;
}



/* main testing */
/******************************************/
int test_file_parser () {

	// read data from file
	char file_dir[] = "game_init.txt";
	vector<string> file_data;
	io_handler::read_file(file_dir, &file_data);

	// parse input file
	struct init_info data;
	file_parser::parse_file(&file_data, &data);

	// test counts
	cout << "testing counts : ----------------------------------" << endl;
	cout << "country count : " << data.country_count << endl;
	cout << "border count : " << data.border_count << endl;
	cout << "continent count : " << data.continent_count << endl;

	// test edge list
	cout << "testing edge list : -------------------------------" << endl;
	vector<struct edge>::iterator ptr1;
	for (ptr1 = data.edge_list.begin(); ptr1 < data.edge_list.end(); ptr1++) 
	{
		cout << "edge : " << ptr1->point1 << "\t" << ptr1->point2 << endl;
	}

	// test continents
	cout << "testing continents : ------------------------------" << endl;
	vector<struct continent>::iterator ptr2;
	for (ptr2 = data.continent_list.begin(); ptr2 < data.continent_list.end(); ptr2++) 
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

	

	

	return 0;
}


int main()
{
	test_file_parser();
	return 0;
}
#include "../../../src/game_engine/utilities/population_file_parser.h"
#include "../../../src/game_engine/environment/data_structures.h"


#include <iostream> // read write screen
#include <string>
#include <vector>

using namespace std;

/* test 01 */
/******************************************/
void
test_population_file_parser(){

	// create dummy list of countries
	vector<struct country> country_list;

	// parse init data
	char population_init_file_dir[] = "population_init.txt";
	population_file_parser pop_parser(population_init_file_dir);
	pop_parser.populate_countries(&country_list);

	// visualize country data
	vector<struct country>::iterator ptr;
	for (ptr = country_list.begin(); ptr < country_list.end(); ptr++) 
	{
		cout << "country : (id = " << ptr->id << "),\t(owner = " << ptr->owner_id << "),\t(troops count = " << ptr->troops_count << ")" << endl;
	}

}


/* main function */
/******************************************/
int main()
{
	test_population_file_parser();
	return 0;
}
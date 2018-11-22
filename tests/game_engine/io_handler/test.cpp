#include "../../../src/game_engine/utilities/io_handler.h"

#include <iostream> // read write screen
#include <string>
#include <vector>

using namespace std;

/* test 01 */
/******************************************/
void
test_io_handler(){

	// read data from file
	char file_dir[] = "map_init.txt";
	vector<string> tmp;
	io_handler::read_file(file_dir, &tmp);

	// read data
	vector<string>::iterator ptr;
	for (ptr = tmp.begin()+1; ptr < tmp.end(); ptr++) 
	{
		cout << "line : " << *ptr << endl;
	}
}


/* main function */
/******************************************/
int main()
{
	test_io_handler();
	return 0;
}
#ifndef IO_HANDLER_H
#define IO_HANDLER_H

/* import libraries */
/******************************************/
#include <fstream> // read write file
#include <iostream> // read write screen
#include <vector>
#include <string>
using namespace std;

/* class definition */
/******************************************/
class io_handler
{
	public:
		static void read_file(char file_dir[], vector<string> *init_data);

	private:
		// Disallow creating an instance of this object
		io_handler(){}
};

#endif 

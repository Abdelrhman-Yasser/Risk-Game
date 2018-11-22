#ifndef POPULATION_FILE_PARSER_H
#define POPULATION_FILE_PARSER_H

/* import libraries */
/******************************************/
#include <fstream> // read write file
#include <iostream> // read write screen
#include <vector>
#include <string>
#include <cstring>
#include "io_handler.h"
#include "../environment/data_structures.h" // data structures of environment

using namespace std;

/* class definition */
/******************************************/
class population_file_parser
{
	private:
		// attributes
		vector<string> buffered_file; // buffered file (line by line)

		// utilities
		void tokenize(string target_line, vector<string> *tokens);
	
	public:
		population_file_parser(char *pop_init_file_dir);
		void populate_countries(vector<struct country> *country_list);
};

#endif 

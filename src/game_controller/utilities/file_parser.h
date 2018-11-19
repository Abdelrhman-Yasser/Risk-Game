#ifndef FILE_PARSER_H
#define FILE_PARSER_H

/* import libraries */
/******************************************/
#include <fstream> // read write file
#include <iostream> // read write screen
#include <vector>
#include <string>
#include <cstring>
#include "../environment/container.h" // data structures of environment

using namespace std;

/* class definition */
/******************************************/
class file_parser
{
	public:
		static void parse_file(vector<string> *init_file_lines, struct init_info *init_info_container);

	private:
		// Disallow creating an instance of this object
		file_parser(){}

		// utility functions
		static vector<string> tokenize(string target_line);
		static void obtain_count(vector<string> *init_file_lines, struct init_info *init_info_container);
		static int parse_count(int line_number, vector<string> *init_file_lines);
		static void obtain_edge_list(vector<string> *init_file_lines, struct init_info *init_info_container);
		static void obtain_continent_list(vector<string> *init_file_lines, struct init_info *init_info_container);
};

#endif 

#include "file_parser.h"
#define LSH_TOK_DELIM " \t\r\n();" // delimiter used in string tokenization


/* tokenization function */
/******************************************/
vector<string>
file_parser::tokenize(string target_line)
{
	// abide by the interface
	vector<string> tokens;
	char line[target_line.length()];
	strcpy(line, target_line.c_str());

	// actual tokenize
    char *token;
    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL)
    {
      tokens.push_back(string(token));
      token = strtok(NULL, LSH_TOK_DELIM);
    }

    return tokens;
}

/* parse attribute counts */
/******************************************/
int
file_parser::parse_count(int line_number, vector<string> *init_file_lines)
{
	/*
		gets count of countries, borders, and continents
		simple specify attributes and line in which count is specified
	*/
	string line = init_file_lines->at(line_number); // gets specified line
	vector<string> line_token = tokenize(line); // split by spaces
    int count = std::stoi(line_token.at(1)); // get desired count
	return count;
}

void
file_parser::obtain_count(vector<string> *init_file_lines, struct init_info *init_info_container)
{
	/*
		gets count of countries, borders, continents
	*/
	init_info_container->country_count = parse_count(0, init_file_lines); // country count
	init_info_container->border_count = parse_count(1, init_file_lines); // border count
	int index = 1 + init_info_container->border_count + 1;
	init_info_container->continent_count = parse_count(index, init_file_lines); // continent count
}


/* parse edge list */
/******************************************/
void
file_parser::obtain_edge_list(vector<string> *init_file_lines, struct init_info *init_info_container)
{
	int index = 2;
	int count = init_info_container->border_count;
	while(count > 0)
	{
		// tokenize
		string line = init_file_lines->at(index); // gets specified line
		vector<string> line_token = tokenize(line); // tokenize line
	    int point1 = std::stoi(line_token.at(0)); // get p1 in edge
	    int point2 = std::stoi(line_token.at(1)); // get p2 in edge
	    // add to edges
	    struct edge tmp;
	    tmp.point1 = point1; tmp.point2 = point2;
	    init_info_container->edge_list.push_back(tmp);
	    // update index, counter
	    index++;
	    count--;
	}
}

/* parse continent list */
/******************************************/
void
file_parser::obtain_continent_list(vector<string> *init_file_lines, struct init_info *init_info_container)
{
	int index = 1 + init_info_container->border_count + 2;
	int count = init_info_container->continent_count;
	//cout << count << endl;
	while(count > 0)
	{
		// create new continent entry
		struct continent tmp;

		// tokenize line
		string line = init_file_lines->at(index); // gets specified line
		vector<string> line_token = tokenize(line); // split by spaces

		// get reward
		int reward = stoi(line_token.at(0));
		tmp.reward = reward;

		// get country list
		vector<string>::iterator ptr;
		for (ptr = line_token.begin()+1; ptr < line_token.end(); ptr++) 
		{
			// use try catch in case if there are words following the line
			try {
				int country_id = stoi(*ptr);
				tmp.country_list.push_back(country_id);
				//cout << country_id << endl;
			} catch (...) {
				break;
			}
		}

		// add continent to list
		init_info_container->continent_list.push_back(tmp);
		// update index, counter
		index++;
		count--;
	}
}


/* interface methods */
/******************************************/
void
file_parser::parse_file(vector<string> *init_file_lines, struct init_info *init_info_container)
{	
	// 01. get count of countries, borders, continents
	obtain_count(init_file_lines, init_info_container);

	// 02. obtain edge list
	obtain_edge_list(init_file_lines, init_info_container);

	// 03. get continent data
	obtain_continent_list(init_file_lines, init_info_container);

}
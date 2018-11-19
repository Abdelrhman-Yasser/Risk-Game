#include "file_parser.h"
#define LSH_TOK_DELIM " \t\r\n();" // delimiter used in string tokenization

/* constructor */
/******************************************/
file_parser::file_parser(char *init_file_dir)
{
	// read data from file
	this->init_file_lines = vector<string>();
	io_handler::read_file(init_file_dir, &init_file_lines);

	// get counts (country, border, continent)
	this->country_count = parse_count(0); // country count
	this->border_count = parse_count(1); // border count
	int index = 1 + this->border_count + 1;
	this->continent_count = parse_count(index); // continent count
}

/* parse attribute counts */
/******************************************/
int
file_parser::parse_count(int line_number)
{
	/*
		gets count of countries, borders, and continents
		simple specify attributes and line in which count is specified
	*/
	string line = this->init_file_lines.at(line_number); // gets specified line
	vector<string> line_token = tokenize(line); // split by delimiter
    int count = std::stoi(line_token.at(1)); // get desired count
	return count;
}

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

/* some getters */
/******************************************/
int
file_parser::get_country_count()
{
	return this->country_count;
}

int
file_parser::get_border_count()
{
	return this->border_count;
}

int
file_parser::get_continent_count()
{
	return this->continent_count;
}


/* parse edge list */
/******************************************/
void
file_parser::obtain_border_list(vector<struct border> *border_list)
{
	int index = 2;
	int count = this->border_count;
	while(count > 0)
	{
		// tokenize
		string line = this->init_file_lines.at(index); // gets specified line
		vector<string> line_token = tokenize(line); // tokenize line
	    int country1 = std::stoi(line_token.at(0)); // get p1 in edge
	    int country2 = std::stoi(line_token.at(1)); // get p2 in edge
	    // add to edges
	    struct border tmp;
	    tmp.country1 = country1; tmp.country2 = country2;
	    border_list->push_back(tmp);
	    // update index, counter
	    index++;
	    count--;
	}
}

/* parse continent list */
/******************************************/
void
file_parser::obtain_continent_list(vector<struct continent> *continent_list)
{
	int index = 1 + this->border_count + 2;
	int count = this->continent_count;
	//cout << count << endl;
	while(count > 0)
	{
		// create new continent entry
		struct continent tmp;

		// tokenize line
		string line = this->init_file_lines.at(index); // gets specified line
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
				//cout << "success" << endl;
				int country_id = stoi(*ptr);
				tmp.country_list.push_back(country_id);
				//cout << country_id << endl;
			} catch (...) {
				break;
			}
		}

		// add continent to list
		continent_list->push_back(tmp);
		// update index, counter
		index++;
		count--;
	}
}

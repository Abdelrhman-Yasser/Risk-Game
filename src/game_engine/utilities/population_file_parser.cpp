#include "population_file_parser.h"
#define LSH_TOK_DELIM " \t\r\n();" // delimiter used in string tokenization

/* constructor */
/******************************************/
population_file_parser::population_file_parser(char *pop_init_file_dir)
{
	// read data from file
	this->buffered_file = vector<string>();
	io_handler::read_file(pop_init_file_dir, &buffered_file);

}

/* tokenization function */
/******************************************/
void
population_file_parser::tokenize(string target_line, vector<string> *tokens)
{
	// abide by the interface
	char line[target_line.length()];
	strcpy(line, target_line.c_str());

	// actual tokenize
    char *token;
    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL)
    {
      tokens->push_back(string(token));
      token = strtok(NULL, LSH_TOK_DELIM);
    }

}

/* parse attribute counts */
/******************************************/
void
population_file_parser::populate_countries(vector<struct country> *country_list)
{
	// we assume countries are listed in-order in the file
	vector<string>::iterator ptr;
	for (ptr = buffered_file.begin()+1; ptr < buffered_file.end(); ptr++) // skip first line
	{
		// (country  |  owner  | troops)
		// 01. read buffered file line by line
		string line = *ptr;
		//cout << line << endl;
		vector<string> line_token;
		tokenize(line, &line_token); // tokenize line
		// 02. for some line/country --> get info
		int country_id = std::stoi(line_token.at(0));
		int owner_id = std::stoi(line_token.at(1));
		int troops_count = std::stoi(line_token.at(2));
		// 03. store information
		struct country tmp;
		tmp.id = country_id;
		tmp.owner_id = (gameplay_id)owner_id; // P1 = 1, P2 = 2, NONE = 0
		tmp.troops_count = troops_count;
		country_list->push_back(tmp); // index of country = id - 1
		
	}
}


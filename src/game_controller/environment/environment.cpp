#include "environment.h"

/* init game environment */
/******************************************/
/* constructor */
environment::environment(char *map_init_file_dir, char *pop_init_file_dir)
{
	// game map
	init_environment(map_init_file_dir, pop_init_file_dir);
	// game status
	this->game_status = status::ONGOING;
	this->winner = gameplay_id::NONE;
}

/* destructor */
environment::environment()
{
	// nothing
}

/* destructor */
environment::~environment()
{
	// TODO
}

/* init game environment */
/******************************************/
void
environment::init_environment(char *map_init_file_dir, char *pop_init_file_dir)
{
	// create countries
	map_file_parser map_parser(map_init_file_dir);
	population_file_parser pop_parser(pop_init_file_dir);

	// create and populate countries
	pop_parser.populate_countries(&country_list);

	// create borders
	map_parser.obtain_border_list(&(this->border_list));

	// create continents and associate countries with continents
	map_parser.obtain_continent_list(&(this->continent_list));

	// associate country with continent
	int continent_id = 1;
	vector<struct continent>::iterator ptr1;
	for (ptr1 = continent_list.begin(); ptr1 < continent_list.end(); ptr1++) 
	{
		// for some continent id
		vector<int>::iterator ptr2;
		for (ptr2 = ptr1->country_list.begin(); ptr2 < ptr1->country_list.end(); ptr2++) 
		{
			country_list.at(*ptr2 - 1).continent_id = continent_id;
		}
		continent_id +=1;
	}

}

void
environment::init_ownership(char *ownership_init_file_dir)
{

}

/* getter methods */
/******************************************/
status
environment::get_game_status()
{
	return this->game_status;
}

gameplay_id
environment::get_winner()
{
	return this->winner;
}

vector<struct country> 
*environment::get_country_list()
{
	return &country_list;
}

vector<struct border> 
*environment::get_border_list()
{
	return &border_list;
}

vector<struct continent> 
*environment::get_continent_list()
{
	return &continent_list;
}



/* utility methods */
/******************************************/
int
environment::border_exists(int country1_id, int country2_id)
{
	vector<struct border>::iterator ptr;
	for (ptr = border_list.begin(); ptr < border_list.end(); ptr++) 
	{
		if((ptr->country1 == country1_id) && (ptr->country2 == country2_id))
		{return 1;}

		if((ptr->country1 == country2_id) && (ptr->country2 == country1_id))
		{return 1;}

	}
	return 0;
}

int
environment::is_owner(gameplay_id test_player, int country_id)
{
	return country_list.at(country_id - 1).owner_id == test_player;
}


int
environment::is_continent_new_owner(gameplay_id test_player, int continent_id)
{
	// if player already owns continent
	if(continent_list.at(continent_id - 1).owner_id == test_player){return 0;}

	// check ownership of all countries
	vector<int>::iterator ptr;
	for (ptr = continent_list.at(continent_id - 1).country_list.begin(); ptr < continent_list.at(continent_id - 1).country_list.end(); ptr++) 
	{
		// if any of the countries does not belong to test player --> return 0
		if(country_list.at(*ptr - 1).owner_id != test_player){return 0;}
	}
	
	return 1;
}

gameplay_id
environment::game_ended(gameplay_id test_player)
{
	vector<struct country>::iterator ptr;
	for (ptr = country_list.begin(); ptr < country_list.end(); ptr++) 
	{
		if(ptr->owner_id != test_player){return NONE;}
	}
	return test_player; // this player won!
}

/* interface methods */
/******************************************/
int
environment::deploy_reserve_troops(gameplay_id owner_id, int target_country_id, int reserve_count)
{
	// 01. check player turn
	// --> already checked at 'game_controller' side P1 then P2 forever
	// 02. check no tampering with reserve count
	// --> already checked when passing 'reserve_count' in calling function as received from parameter
	// 03. check no ownership tampering
	// --> already checked when player passed gameplay_id their own 'this->player_id'
	// 04. check player owns target country
	if(is_owner(owner_id, target_country_id) == 0){return 0;} // throws exception
	country_list.at(target_country_id - 1).troops_count += reserve_count;
	return 1;
}

/* interface methods */
/******************************************/
int
environment::march_troops(gameplay_id owner_id, int from_country_id, int to_country_id, int troops_count)
{
	// 01. check player turn
	// --> already checked at 'game_controller' side P1 then P2 forever
	// 02. check no ownership tampering
	// --> already checked when player passed gameplay_id their own 'this->player_id'
	// 03. check player owns 'FROM' country
	if(is_owner(owner_id, from_country_id) == 0){return 0;} // throws exception
	// 04. check player owns 'TO' country
	if(is_owner(owner_id, to_country_id) == 0){return 0;} // throws exception
	// 05. check enough troops in 'FROM' country to march
	if((country_list.at(from_country_id - 1).troops_count - troops_count) < 1){return 0;} // throws exception
	// 06. check border exists between two countries
	if(border_exists(from_country_id, to_country_id) == 0){return 0;} // throws exception

	// apply march
	country_list.at(from_country_id - 1).troops_count -= troops_count;
	country_list.at(to_country_id - 1).troops_count += troops_count;
	return 1;
}

/* interface methods */
/******************************************/
int
environment::invade(gameplay_id owner_id, int from_country_id, int to_country_id)
{
	// 01. check player turn
	// --> already checked at 'game_controller' side P1 then P2 forever
	// 02. check there's a border
	if(border_exists(from_country_id, to_country_id) == 0){return 0;} // throws exception
	// 03. check no ownership tampering
	// --> already checked when player passed gameplay_id their own 'this->player_id'
	// 04. check invader owns 'from_country'
	if(is_owner(owner_id, from_country_id) == 0){return 0;} // throws exception

	/* 01. apply move */
	// update troops count and ownership
	int i = country_list.at(from_country_id - 1).troops_count;
	int j = country_list.at(to_country_id - 1).troops_count;
	if((i - j) > 1) // successfull invasion
	{
		cout << "successful invasion" << endl;
		cout << "from country ID : " << from_country_id << endl;
		cout << "to country ID : " << to_country_id << endl;
		// reduce troops - killed in battle
		country_list.at(to_country_id - 1).troops_count = 0;
		country_list.at(from_country_id - 1).troops_count -= j;

		// march 1 division of troops to invaded country
		country_list.at(from_country_id - 1).troops_count -= 1;
		country_list.at(to_country_id - 1).troops_count += 1;
		
		// update ownership
		country_list.at(to_country_id - 1).owner_id = country_list.at(from_country_id - 1).owner_id;

		/* 02. check continent ownership for reward */
		int reward = INVASION_REWARD;
		int continent_id = country_list.at(to_country_id - 1).continent_id;
		if(is_continent_new_owner(owner_id, continent_id) == 1)
		{
			// updated continent ownership
			continent_list.at(continent_id - 1).owner_id = owner_id;
			// update given reward
			reward = continent_list.at(continent_id - 1).reward;
		}

		/* 03. update game status */
		if(game_ended(owner_id) == owner_id)
		{
			game_status = status::ENDED;
			winner = owner_id;
		}
		//game_status = ;
		return reward;

	}else{
		// unsucessfull invasion
		return 0; // no reward
	}

}
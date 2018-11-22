#include "game_set_visualizer.h"


/* utilities */
/******************************************/
string
game_set_visualizer::enum_agent_type_to_string(agent_type p_type)
{
	if(p_type == 0){return string("HUMAN");}
	if(p_type == 1){return string("PASSIVE");}
	if(p_type == 2){return string("AGGRESSIVE");}
}

string
game_set_visualizer::enum_gameplay_id_to_string(gameplay_id player_id)
{
	if(player_id == 0){return string("NONE");}
	if(player_id == 1){return string("P1");}
	if(player_id == 2){return string("P2");}
}

string
game_set_visualizer::enum_action_to_string(action a_type)
{
	if(a_type == 0){return string("deploy reserve troops");}
	if(a_type == 1){return string("march troops");}
	if(a_type == 2){return string("attempt invasion");}
}

/* visualize environment */
/******************************************/
void
game_set_visualizer::display_country_info(struct country *c)
{
	cout << "(id : " << c->id << ")\t";
	cout << "(troops count : " << c->troops_count << ")\t";
	cout << "(owner : " << enum_gameplay_id_to_string(c->owner_id) << ")" << endl;
}

void
game_set_visualizer::display_banner(string title)
{
	cout << "**************************************************************************************" << endl;
	cout << "**************************************************************************************" << endl;
	cout << "\t\t\t\t    " << title << endl;
	cout << "**************************************************************************************" << endl;
	cout << "**************************************************************************************" << endl;
	cout << endl;
}


/* visualize environment */
/******************************************/
void
game_set_visualizer::display_continents(environment *game_set)
{
	display_banner(string("CONTINENTS"));

	vector<struct continent>::iterator ptr3;
	for (ptr3 = game_set->get_continent_list()->begin(); ptr3 < game_set->get_continent_list()->end(); ptr3++) 
	{
		cout << "\t****************************************************************" << endl;
		cout << "\tcontinent : " << "(reward = " << ptr3->reward << ")";
		cout << "\t(owner = " << enum_gameplay_id_to_string(ptr3->owner_id) << ")" << endl;
		cout << "\t****************************************************************" << endl;
		vector<int>::iterator ptr4;
		for (ptr4 = ptr3->country_list.begin(); ptr4 < ptr3->country_list.end(); ptr4++) 
		{
			cout << "\tcountry : ";
			display_country_info(&game_set->get_country_list()->at(*ptr4 - 1));
		}
	}

	cout << endl;
	cout << "**************************************************************************************" << endl;
	cout << "**************************************************************************************" << endl;
	cout << endl;
}

void
game_set_visualizer::display_player_perspective(gameplay_id player_id, environment *game_set)
{
	// display player banner
	string title = "PLAYER " + to_string(player_id);
	display_banner(title);

	// display countries owned by player
	vector<struct country>::iterator ptr1;
	for (ptr1 = game_set->get_country_list()->begin(); ptr1 < game_set->get_country_list()->end(); ptr1++) 
	{
		if(ptr1->owner_id != player_id) // country NOT belong to player
		{
			continue;
		}
		// display country info
		cout << "\t*******************************************************************" << endl;
		cout << "\tOWNED : ";
		display_country_info(&(*ptr1));
		cout << "\t*******************************************************************" << endl;
		
		// display bordering countries - ENEMIES
		cout << "\tBordering Enemies :" << endl;
		cout << "\t*******************" << endl;

		vector<struct border>::iterator ptr2;
		for (ptr2 = game_set->get_border_list()->begin(); ptr2 < game_set->get_border_list()->end(); ptr2++) 
		{
			// country on 1st side of border
			if(ptr1->id == ptr2->country1)
			{
				if(game_set->get_country_list()->at(ptr2->country2 - 1).owner_id == player_id){continue;} // not an enemy
				cout << "\tENEMY : ";
				display_country_info(&game_set->get_country_list()->at(ptr2->country2 - 1));
				continue;
			}
			// country on 2nd side of border
			if(ptr1->id == ptr2->country2)
			{
				if(game_set->get_country_list()->at(ptr2->country1 - 1).owner_id == player_id){continue;} // not an enemy
				cout << "\tENEMY : ";
				display_country_info(&game_set->get_country_list()->at(ptr2->country1 - 1));
				continue;
			}
		}

		// display bordering countries - NEIGHBORS MINE
		cout << endl;
		cout << "\tBordering NEIGHBORS :" << endl;
		cout << "\t*********************" << endl;
		for (ptr2 = game_set->get_border_list()->begin(); ptr2 < game_set->get_border_list()->end(); ptr2++) 
		{
			// country on 1st side of border
			if(ptr1->id == ptr2->country1)
			{
				if(game_set->get_country_list()->at(ptr2->country2 - 1).owner_id != player_id){continue;} // not an enemy
				cout << "\tMYCNT : ";
				display_country_info(&game_set->get_country_list()->at(ptr2->country2 - 1));
				continue;
			}
			// country on 2nd side of border
			if(ptr1->id == ptr2->country2)
			{
				if(game_set->get_country_list()->at(ptr2->country1 - 1).owner_id != player_id){continue;} // not an enemy
				cout << "\tMYCNT : ";
				display_country_info(&game_set->get_country_list()->at(ptr2->country1 - 1));
				continue;
			}
		}

		cout << endl;
	}
}


/* visualize environment */
/******************************************/
void
game_set_visualizer::announce_player_turn(gameplay_id player_turn, agent_type p_type, int reserve_troops_count)
{
	//string a_type;
	//if()
	cout << endl;
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	cout << "\t\tplayer turn : " << enum_gameplay_id_to_string(player_turn) << endl;
	cout << "\t     (agent type : " << enum_agent_type_to_string(p_type) << ")" << endl;
	cout << "\t      (reserve troops = " << reserve_troops_count << ")" << endl;
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
}


/* visualize environment */
/******************************************/
void
game_set_visualizer::display_game_board(environment *game_set, gameplay_id player_turn, agent_type p_type, int reserve_troops_count, action a_type)
{
	// clear display
	system("clear");

	// 01. display continent info
	display_continents(game_set);

	// 02. display player perspective
	display_player_perspective(gameplay_id::P1, game_set);
	display_player_perspective(gameplay_id::P2, game_set);

	// 03. display player turn
	announce_player_turn(player_turn, p_type, reserve_troops_count);

	// 04. display current action
	cout << "\t<< " << enum_action_to_string(a_type) << " >>" << endl;
	if(p_type != agent_type::HUMAN)
	{
		sleep(WAIT_TIME); // sleep in order to see agent action
	}
}

/* visualize environment */
/******************************************/
void
game_set_visualizer::display_winner_banner(gameplay_id winner_id)
{
	// clear display
	system("clear");
	
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	cout << "\tGAME WINNER : " << enum_gameplay_id_to_string(winner_id) << endl;
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
}
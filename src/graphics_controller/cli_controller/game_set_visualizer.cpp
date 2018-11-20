#include "game_set_visualizer.h"

/* visualize environment */
/******************************************/
void
game_set_visualizer::display_country_info(struct country *c)
{
	cout << "(id : " << c->id << ")\t";
	cout << "(owner : " << c->o_id << ")\t";
	cout << "(troops count : " << c->troops_count << ")" << endl;
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
		cout << "\tcontinent : " << "(reward = " << ptr3->reward << ")" << endl;
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

}

void
game_set_visualizer::display_player_perspective(owner_id player_id, environment *game_set)
{
	// display player banner
	string title = "PLAYER " + to_string(player_id + 1);
	display_banner(title);

	// display countries owned by player
	vector<struct country>::iterator ptr1;
	for (ptr1 = game_set->get_country_list()->begin(); ptr1 < game_set->get_country_list()->end(); ptr1++) 
	{
		if(ptr1->o_id != player_id) // country NOT belong to player
		{
			continue;
		}
		// display country info
		cout << "\t*******************************************************************" << endl;
		cout << "\tOWNED COUNTRY : ";
		display_country_info(&(*ptr1));
		cout << "\t*******************************************************************" << endl;

		// display bordering countries
		vector<struct border>::iterator ptr2;
		for (ptr2 = game_set->get_border_list()->begin(); ptr2 < game_set->get_border_list()->end(); ptr2++) 
		{
			// country on 1st side of border
			if(ptr1->id == ptr2->country1)
			{
				if(game_set->get_country_list()->at(ptr2->country2 - 1).o_id == player_id){continue;} // not an enemy
				cout << "\tENEMY : ";
				display_country_info(&game_set->get_country_list()->at(ptr2->country2 - 1));
				continue;
			}
			// country on 2nd side of border
			if(ptr1->id == ptr2->country2)
			{
				if(game_set->get_country_list()->at(ptr2->country1 - 1).o_id == player_id){continue;} // not an enemy
				cout << "\tENEMY : ";
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
game_set_visualizer::display_game_board(environment *game_set)
{
	// 01. display player perspective
	display_player_perspective(owner_id::P1, game_set);
	display_player_perspective(owner_id::P2, game_set);

	// 02. display continent info
	display_continents(game_set);
}



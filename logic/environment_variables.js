/* gameplay variables */
/*****************************************/
var variables_player_turn = "P1";
var variables_game_status = "OnGoing";
var variables_game_winner = "none";

var variables_country_list = [];
var variables_border_list = [];
var variables_continent_list = [];

var variables_delay = 200;
var variables_human_delay_period = 10; // milli seconds
var variables_agent_delay_period = 500; // milli seconds

var variables_server_port = 9000;

var variables_curr_player;

var variables_player_info = {
	
	"p1": {
		"type": "test",
		"reserve": 2,
		"view_id_reserve_troops": "#gameplay_page_control_panel_p1_reserve"
	},

	"p2": {
		"type": "test",
		"reserve": 2,
		"view_id_reserve_troops": "#gameplay_page_control_panel_p2_reserve"
	}
};

/* canvas variables */
/*****************************************/
var variables_canvas_nodes;
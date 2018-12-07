/* gameplay variables */
/*****************************************/
var variables_player_turn = "p1";
var variables_game_status = "OnGoing";
var variables_game_winner = "none";

var variables_country_list = [];
var variables_border_list = [];
var variables_continent_list = [];

var variables_delay = 200;
var variables_human_delay_period = 10; // milli seconds
var variables_agent_delay_period = 200; // milli seconds

var variables_server_port = 8000;

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

var variables_canvas_nodes;

/* utility methods */
/*****************************************/
function variables_reset()
{
	variables_player_turn = "p1";
	variables_game_status = "OnGoing";
	variables_game_winner = "none";

	variables_country_list = [];
	variables_border_list = [];
	variables_continent_list = [];

	variables_curr_player = 0;

	variables_player_info = {

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

	variables_canvas_nodes = 0;
}
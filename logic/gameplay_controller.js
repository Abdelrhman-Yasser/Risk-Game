/*****************************************/
/* AJAX controller */
/*****************************************/
function send_POST_request(req_url, send_data)
{
	var data_url = "http://127.0.0.1:9000/" + req_url;

	return JSON.parse(
    	$.ajax({
	        type: "POST",
	        url: data_url,
	        data: send_data,
	        async: false,
	    }).responseText
	);
}

function send_GET_request(req_url)
{
	var data_url = "http://127.0.0.1:9000/" + req_url;

    return JSON.parse(
    	$.ajax({
	        type: "GET",
	        url: data_url,
	        async: false,
	    }).responseText
	);
}

/*****************************************/
/* utilities */
/*****************************************/
function apply_next_in_chain(next_function)
{
	// delay before march
	setTimeout(function(){
	    next_function();
	}, variables_delay);
}

/*****************************************/
/* handle deployment */
/*****************************************/
function gameplay_controller_handle_human_deployment()
{
	// 01. get data move from user
	var to_country = $("#gameplay_page_control_panel_to_country_id").val();
	// 02. send request to apply to server
	var send_data = {
		"target" : to_country,
		"count" : variables_curr_player["reserve"]
	};
	var response = send_POST_request("deploy_human", send_data);
	// 03. apply move - or prompt error
	if(response["success"] == 1)
	{
		// no error
		// apply move on graph --------->> TODO
		// update reserve troops
		variables_player_info[variables_player_turn.toLowerCase()]["reserve"] = 0;
		// update view
		$(variables_curr_player["view_id_reserve_troops"]).text("0");
		// apply next in chain
		apply_next_in_chain(gameplay_controller_handle_marching);
		return;
	}
	// else an error occured
	window.alert("could not apply move!");
}

function gameplay_controller_handle_agent_deployment()
{
	// 01. get deploy move from server
	var response = send_GET_request("deploy_pc");
	var to_country = response["target"];
	var count = response["count"];
	// 02. apply change on graph
	// apply move on graph --------->> TODO
	// 03. update player reserve troops
	variables_player_info[variables_player_turn.toLowerCase()]["reserve"] = 0;
	// update view
	$(variables_curr_player["view_id_reserve_troops"]).text("0");
	// apply next in chain
	apply_next_in_chain(gameplay_controller_handle_marching);
	return;
}

/*****************************************/
/* handle marching */
/*****************************************/

function gameplay_controller_handle_human_skip_march()
{
	apply_next_in_chain(gameplay_controller_handle_invasion);
}

function gameplay_controller_handle_human_marching()
{
	// 01. get data move from user
	var from_country = $("#gameplay_page_control_panel_from_country_id").val();
	var to_country = $("#gameplay_page_control_panel_to_country_id").val();
	var count = $("#gameplay_page_control_panel_troops_count_val").val();
	// 02. send request to apply to server
	var send_data = {
		"from" : from_country,
		"to" : to_country,
		"count": count
	};
	var response = send_POST_request("march_human", send_data);
	// 03. apply move - or prompt error
	if(response["success"] == 1)
	{
		// no error
		// apply move on graph --------->> TODO
		// apply next in chain
		apply_next_in_chain(gameplay_controller_handle_invasion);
		return;
	}
	// else an error occured
	window.alert("could not apply move!");
}

function gameplay_controller_handle_agent_marching()
{
	// 01. get march move from server
	var response = send_GET_request("march_pc");
	if(response["change"] == 0)
	{
		// no change happened
		// apply next in chain
		apply_next_in_chain(gameplay_controller_handle_invasion);
		return;
	}
	var from_country = response["from"];
	var to_country = response["to"];
	var count = response["count"];
	// 02. apply move on graph
	// apply move on graph --------->> TODO
	// apply next in chain
	apply_next_in_chain(gameplay_controller_handle_invasion);
	return;
}

/*****************************************/
/* handle invasion */
/*****************************************/
function gameplay_controller_handle_human_skip_invasion()
{
	gameplay_controller_update_player_turn();
}

function gameplay_controller_handle_human_invasion()
{
	// 01. get data move from user
	var from_country = $("#gameplay_page_control_panel_from_country_id").val();
	var to_country = $("#gameplay_page_control_panel_to_country_id").val();
	// 02. send request to apply to server
	var send_data = {
		"from" : from_country,
		"to" : to_country
	};
	var response = send_POST_request("invade_human", send_data);
	// 03. apply move - or prompt error
	if(response["success"] == 1)
	{
		// no error
		// apply move on graph --------->> TODO
		// 04. update game status
		variables_game_status = response["game_status"];
		variables_game_winner = response["winner"];
		var reward = response["reward"];
		variables_player_info[variables_player_turn.toLowerCase()]["reserve"] = reward;
		// update view
		$(variables_curr_player["view_id_reserve_troops"]).text(reward);
		// apply next in chain
		gameplay_controller_update_player_turn();
		return;
	}
	// else an error occured
	window.alert("could not apply move!");
}

function gameplay_controller_handle_agent_invasion()
{
	// 01. get invade move from server
	var response = send_GET_request("invade_pc");
	if(response["change"] == 0)
	{
		// no change happened
		// apply next in chain
		gameplay_controller_update_player_turn();
		return;
	}
	var from_country = response["from"];
	var to_country = response["to"];
	// 02. apply move on graph
	// apply move on graph --------->> TODO
	// 03. update game status
	variables_game_status = response["game_status"];
	variables_game_winner = response["winner"];
	var reward = response["reward"];
	variables_player_info[variables_player_turn.toLowerCase()]["reserve"] = reward;
	// update view
	$(variables_curr_player["view_id_reserve_troops"]).text(reward);
	// apply next in chain
	gameplay_controller_update_player_turn();
	return;
}

/*****************************************/
/* identify current player */
/*****************************************/
function gameplay_controller_update_curr_player()
{
	if(variables_player_turn.toLowerCase() == "p1")
	{
		variables_curr_player = variables_player_info["p1"];
	}
	else{
		variables_curr_player = variables_player_info["p2"];
	}
	// apply next in chain
	variables_delay = 500;
	if(variables_curr_player["type"].toLowerCase() == "human")
	{
		variables_delay = 10;
	}
	apply_next_in_chain(gameplay_controller_handle_deployment);
}

function gameplay_controller_update_player_turn()
{
	if(variables_player_turn.toLowerCase() == "p1")
	{
		variables_player_turn = "p2";
	}else{
		variables_player_turn = "p1";	
	}

	// update view
	$("#gameplay_page_control_panel_player_turn").text(variables_player_turn);
	
	// check game status
	if(variables_game_status.toLowerCase() == "ongoing")
	{
		gameplay_controller_update_curr_player();
	}else
	{
		// game ends
		$("#gameplay_page_winner_modal_winner_id").text(variables_game_winner);
		$("#gameplay_page_winner_modal").show();
	}
}

/*****************************************/
/* strategy functions */
/*****************************************/
function gameplay_controller_handle_deployment()
{
	if(variables_curr_player["reserve"] == 0)
	{
		apply_next_in_chain(gameplay_controller_handle_marching);
		return;
	}

	if(variables_curr_player["type"].toLowerCase() == "human")
	{
		gameplay_page_display_human_deploy_controls();
		// wait on user to click button
		// which will call gameplay_controller_handle_human_deployment();
	}
	else
	{
		$("#gameplay_page_control_panel_human_controls").hide();
		gameplay_controller_handle_agent_deployment();
	}
	
}

function gameplay_controller_handle_marching()
{
	if(variables_curr_player["type"].toLowerCase() == "human")
	{
		gameplay_page_display_human_march_controls();
		// wait on user to click button
		// which will call gameplay_controller_handle_human_marching();
	}
	else
	{
		$("#gameplay_page_control_panel_human_controls").hide();
		gameplay_controller_handle_agent_marching();
	}
	
}

function gameplay_controller_handle_invasion()
{
	if(variables_curr_player["type"].toLowerCase() == "human")
	{
		gameplay_page_display_human_invade_controls();
		// wait on user to click button
		// which will call gameplay_controller_handle_human_invasion();	
	}
	else
	{
		$("#gameplay_page_control_panel_human_controls").hide();
		gameplay_controller_handle_agent_invasion();
	}
	
}

/*****************************************/
/* gameplay controller */
/*****************************************/
function gameplay_controller_start_game()
{
	gameplay_controller_update_curr_player();
}




















/*function gameplay_controller_start_game()
{
	display_human_march_controls();
	while(variables_game_status.toLowerCase() == "ongoing")
	{
		// identify player currently playing
		gameplay_controller_update_curr_player();

		// 01. deploy reserve troops
		gameplay_controller_handle_deployment();

		// 02. march neiboring troops
		gameplay_controller_handle_marching();

		// 03. attempt invasion
		gameplay_controller_handle_invasion();

		// change turns
		gameplay_controller_update_player_turn();

	}

	// game ends
	$("#gameplay_page_winner_modal_winner_id").text(variables_game_winner);
	$("#gameplay_page_winner_modal").show();

}*/


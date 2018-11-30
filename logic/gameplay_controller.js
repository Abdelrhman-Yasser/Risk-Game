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
/* control human input view */
/*****************************************/
function display_human_deploy_controls()
{
	$("#gameplay_page_control_panel_human_controls").show();
	$("#gameplay_page_control_panel_from_country_input").hide(); // from
	$("#gameplay_page_control_panel_to_country_input").show(); // to
	$("#gameplay_page_control_panel_troops_count_input").hide(); // count
	$("#gameplay_page_control_panel_human_apply_btn").show(); // apply
	$("#gameplay_page_control_panel_human_skip_btn").hide(); // skip
}

function display_human_march_controls()
{
	$("#gameplay_page_control_panel_human_controls").show();
	$("#gameplay_page_control_panel_from_country_input").show(); // from
	$("#gameplay_page_control_panel_to_country_input").show(); // to
	$("#gameplay_page_control_panel_troops_count_input").show(); // count
	$("#gameplay_page_control_panel_human_apply_btn").show(); // apply
	$("#gameplay_page_control_panel_human_skip_btn").show(); // skip
}

function display_human_invade_controls()
{
	$("#gameplay_page_control_panel_human_controls").show();
	$("#gameplay_page_control_panel_from_country_input").show(); // from
	$("#gameplay_page_control_panel_to_country_input").show(); // to
	$("#gameplay_page_control_panel_troops_count_input").hide(); // count
	$("#gameplay_page_control_panel_human_apply_btn").show(); // apply
	$("#gameplay_page_control_panel_human_skip_btn").show(); // skip
}

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
/* strategy functions */
/*****************************************/
function gameplay_controller_handle_deployment()
{
	if(variables_curr_player["reserve"] != 0)
	{
		// computer agent
		if(variables_curr_player["type"].toLowerCase() != "human")
		{
			// 01. get deploy move from server
			var response = send_GET_request("deploy_pc");
			console.log(response);
			//window.alert(response);
			//console.log(response);
			var to_country = response["target"];
			var count = response["count"];
			// 02. apply change on graph
			// apply move on graph --------->> TODO
			// 03. update player reserve troops
			variables_player_info[variables_curr_player["type"].toLowerCase()]["reserve"] = 0;
			// apply next in chain
			apply_next_in_chain(gameplay_controller_handle_marching);
			return;
		}

		// human player
		display_human_deploy_controls();
		while(1)
		{
			// 01. get data move from user
			var to_country = prompt("deploy to");
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
				// apply next in chain
				apply_next_in_chain(gameplay_controller_handle_marching);
				return;
			}
			// else an error occured
			window.alert("could not apply move!");
		}
		
	}
	apply_next_in_chain(gameplay_controller_handle_marching);
}

function gameplay_controller_handle_marching()
{
	// computer player
	if(variables_curr_player["type"].toLowerCase() != "human")
	{
		// 01. get march move from server
		var response = send_GET_request("march_pc");
		console.log(response);
		//window.alert(response);
		//console.log(response);
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

	// human player
	display_human_march_controls();
	while(1)
	{
		// 00. skip flag
		var skip_flag = prompt("march 1/0?");
		if(skip_flag == 0) // skip no marching
		{
			// apply next in chain
			apply_next_in_chain(gameplay_controller_handle_invasion);
			return;
		}
		// 01. get data move from user
		var from_country = prompt("march from");
		var to_country = prompt("march to");
		var count = prompt("troops count");
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
}

function gameplay_controller_handle_invasion()
{
	// computer player
	if(variables_curr_player["type"].toLowerCase() != "human")
	{
		// 01. get invade move from server
		var response = send_GET_request("invade_pc");
		console.log(response);
		//window.alert(response);
		//console.log(response);
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
		// apply next in chain
		gameplay_controller_update_player_turn();
		return;
	}
	// human player
	display_human_invade_controls();
	while(1)
	{
		// 00. skip flag
		var skip_flag = prompt("invade 1/0?");
		if(skip_flag == 0)
		{
			// apply next in chain
			gameplay_controller_update_player_turn();
			return;
		} // skip NO invade
		// 01. get data move from user
		var from_country = prompt("march from");
		var to_country = prompt("march to");
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
			// apply next in chain
			gameplay_controller_update_player_turn();
			return;
		}
		// else an error occured
		window.alert("could not apply move!");
	}
}

/*****************************************/
/* gameplay controller */
/*****************************************/
function apply_next_in_chain(next_function)
{
	// delay before march
	setTimeout(function(){
		console.log("success");
	    next_function();
	}, variables_delay);
}

function gameplay_controller_start_game()
{
	window.alert("success");
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


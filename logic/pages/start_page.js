/* initialize layouts */
/****************************************/
function start_page_init_layout()
{
    $('#start_page_background_container').height($(window).height());
    $('#start_page_background_container').width($(window).width());

    $(window).resize(function(){
        $('#start_page_background_container').height($(window).height());
    	$('#start_page_background_container').width($(window).width());
    });
}
/* add event listeners */
/****************************************/
function start_page_init_event_listeners()
{
	$('#start_page_new_game_btn').click(function(e){

		// 01. obtain selected player types
		var p1_type = $("#start_page_p1_type").val(); //console.log(p1_type);
		var p2_type = $("#start_page_p2_type").val(); //console.log(p2_type);

		// update game controller players
		variables_player1 = p1_type.toUpperCase();
		variables_player2 = p2_type.toUpperCase();

		// 02. send POSt request with player types
		// and obtain environment setup from server
		var send_data = {
			p1_type : p1_type,
			p2_type : p2_type
		};
		var target_url = "http://127.0.0.1:9000/new_game";
		$.post(target_url, send_data, function(data, status){
			// obtain environment setup
	    	environment = JSON.parse(data);
	    	
	    	// update model
	    	variables_country_list = environment["country_list"]; // console.log(country_list);
	    	variables_border_list = environment["border_list"]; // console.log(border_list);
	    	variables_continent_list = environment["continent_list"]; // console.log(continent_list);

	    	// 03. redirect to new game
			app_controller_load_gameplay_page();
		});


	});

}
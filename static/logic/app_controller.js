/* initialize game router */
/*****************************************/
$(document).ready(function(){

    // front-end lib (http://visjs.org/network_examples.html)

    app_controller_load_start_page();
    
});

/* route to start page */
/*****************************************/
function app_controller_load_start_page()
{
    $("body").empty();
    $("body").load("./components/start_page/start_page.html", function(){
        $("#start_page_modal_container").load("./components/start_page/start_modal.html", function(){
            start_page_init_layout();
            start_page_init_event_listeners();
        });
    });
}

/* route to gameplay page */
/*****************************************/
function app_controller_load_gameplay_page()
{
    $("body").empty();
    $("body").load("./components/gameplay_page/gameplay_page.html", function(){
        $("#gameplay_page_control_panel_container").load("./components/gameplay_page/control_panel.html", function(){
            $("#gameplay_page_canvas_container").load("./components/gameplay_page/game_canvas.html", function(){
                // 01. init environment
                gameplay_page_init_layout();
                gameplay_page_init_event_listeners();
                gamepaly_page_init_control_panel();
                gameplay_page_init_graph();

                // 02. start new game
                
                setTimeout(function(){
                    gameplay_controller_start_game();
                }, variables_delay);
                
                
            });
        });
        
        $("#gameplay_page_winner_modal_container").load("./components/gameplay_page/winner_modal.html");
    });
}








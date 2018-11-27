$(document).ready(function(){

    //load_start_page();
    load_gameplay_page();
    
});


function load_start_page()
{
    $("body").empty();
    $("body").load("./components/start_page/start_page.html", function(){
        $("#start_modal_container").load("./components/start_page/start_modal.html", function(){
            start_page_init_event_listeners();
        });

    });
}

function load_gameplay_page()
{
    $("body").empty();
    $("body").load("./components/gameplay_page/gameplay_page.html", function(){
        $("#control_panel_container").load("./components/gameplay_page/control_panel.html");
        $("#gameplay_canvas_container").load("./components/gameplay_page/game_canvas.html", function(){
            gameplay_page_init_canvas_layout();
            gameplay_page_init_event_listeners();
            gameplay_page_init_graph();
        });
    });
}








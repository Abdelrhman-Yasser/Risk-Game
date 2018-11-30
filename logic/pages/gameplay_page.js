/* init layouts */
/*****************************************/
function gameplay_page_init_layout()
{
    gameplay_page_init_canvas_background();
    gameplay_page_init_canvas_layout();
}

function gameplay_page_init_canvas_background()
{
    var left_margin = 250;
    $('#gameplay_page_canvas_background').height($(window).height());
    $('#gameplay_page_canvas_background').width($(window).width() - left_margin);

    $(window).resize(function(){
        $('#gameplay_page_canvas_background').height($(window).height());
        $('#gameplay_page_canvas_background').width($(window).width() - left_margin);
    });
}
function gameplay_page_init_canvas_layout()
{
    var new_height = $(window).height();
    var new_width = $(window).width() - 250;
    $('#gameplay_page_canvas').width(new_width);
    $('#gameplay_page_canvas').height(new_height);

    $(window).resize(function(){
        var new_height = $(window).height();
        var new_width = $(window).width() - 250;
        $('#gameplay_page_canvas').width(new_width);
        $('#gameplay_page_canvas').height(new_height);
    });
}

/* init event listeners */
/*****************************************/
function gameplay_page_init_event_listeners()
{
    $("#gameplay_page_control_panel_human_apply_btn").click(function(e){
        variables_country_list[0]["continent"] = 2;
        gameplay_page_init_graph();
    });
}

/* init variables - control panel */
/*****************************************/
function gamepaly_page_init_control_panel()
{
    $("#gameplay_page_control_panel_p1_type").text(variables_player_info["p1"]["type"]);
    $("#gameplay_page_control_panel_p2_type").text(variables_player_info["p2"]["type"]);

    $("#gameplay_page_control_panel_player_turn").text(variables_player_turn);
    $("#gameplay_page_control_panel_game_status").text(variables_game_status);

    $("#gameplay_page_control_panel_p1_reserve").text(variables_player_info["p1"]["reserve"]);
    $("#gameplay_page_control_panel_p2_reserve").text(variables_player_info["p2"]["reserve"]);
}


/* init variables - graph */
/*****************************************/
function gameplay_canvas_init_node_list()
{
    var node_set = [];

    for (var index in variables_country_list)
    {
        var country = variables_country_list[index];
        var tmp = {
            id: country["id"],
            label: country["owner"],
            group: country["continent"],
            //troops: country["troops_count"]
        };
        node_set.push(tmp);
    }

    return node_set;

}

function gameplay_canvas_init_border_list()
{
    var border_set = [];

    for (var index in variables_border_list)
    {
        var border = variables_border_list[index];
        var tmp = {
            from: border["country1"],
            to: border["country2"]
        };
        border_set.push(tmp);
    }

    return border_set;
}

function gameplay_page_init_graph()
{
    // 01. obtain nodes and edges of environment

    var nodes = gameplay_canvas_init_node_list();

    var edges = gameplay_canvas_init_border_list();

    // using vis.js
    var color = 'gray';
    var len = undefined;

    // create a network
    var container = document.getElementById('gameplay_page_canvas');
    var data = {
        nodes: nodes,
        edges: edges
    };
    var options = {
        nodes: {
            shape: 'circle',
            size: 40,
            font: {
                size: 20,
            },
            borderWidth: 2
        },
        edges: {
            width: 2
        },
        physics: {
            enabled: false
        },
        manipulation:{
            enabled: true,
            editNode: function(nodeData,callback) {
                nodeData.label = 'hello world';
                callback(nodeData);
            }
        }
    };
    network = new vis.Network(container, data, options);
}

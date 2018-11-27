/* init layouts */
/*****************************************/
function gameplay_page_init_canvas_layout()
{
    var new_height = $(window).height() - 2;
    var new_width = $(window).width() - 250 - 10;
    $('#gameplay_canvas').width(new_width);
    $('#gameplay_canvas').height(new_height);

    $(window).resize(function(){
        var new_height = $(window).height() - 2;
        var new_width = $(window).width() - 250 - 10;
        $('#gameplay_canvas').width(new_width);
        $('#gameplay_canvas').height(new_height);
    });
}

/* init event listeners */
/*****************************************/
function gameplay_page_init_event_listeners()
{

}


/* interface methods */
/*****************************************/
function gameplay_page_init_graph()
{
    var color = 'gray';
    var len = undefined;

    var nodes = [
        {id: 1, label: "1", group: 1},
        {id: 2, label: "2", group: 1},
        {id: 3, label: "3", group: 2},
        {id: 4, label: "4", group: 2}

    ];

    var edges = [
        {from: 1, to: 2},
        {from: 2, to: 3},
        {from: 3, to: 4},
        {from: 1, to: 3}
    ]

    // create a network
    var container = document.getElementById('gameplay_canvas');
    var data = {
        nodes: nodes,
        edges: edges
    };
    var options = {
        nodes: {
            shape: 'dot',
            size: 20,
            font: {
                size: 32,
            },
            borderWidth: 2
        },
        edges: {
            width: 2
        }
    };
    network = new vis.Network(container, data, options);
}



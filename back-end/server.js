/* IMPORT REQUIRED MODULEs */
/*********************************************/
var express = require('express');
var app = express();

var path    = require("path"); // module for path reading
var bodyParser = require('body-parser');

// Create application/x-www-form-urlencoded parser
var urlencodedParser = bodyParser.urlencoded({ extended: false });

/* CREATE WEB SERVER */
/*********************************************/
var server = app.listen(9000, function () {
   var host = server.address().address;
   var port = server.address().port;
   console.log("Example app listening at http://%s:%s", host, port);
});

/* allow access from other domains */
/*********************************************/
app.use(function (req, res, next) {

    // Website you wish to allow to connect
    res.setHeader('Access-Control-Allow-Origin', 'http://localhost:8000');

    // Request methods you wish to allow
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    // Request headers you wish to allow
    res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');

    // Set to true if you need the website to include cookies in the requests sent
    // to the API (e.g. in case you use sessions)
    res.setHeader('Access-Control-Allow-Credentials', true);

    // Pass to next layer of middleware
    next();
});

/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
/* global variables */
/*********************************************/
const fs = require('fs');
let rawdata = fs.readFileSync('environment_init.json');  
let environment = JSON.parse(rawdata); 
//console.log(environment)

//var sleep = require('system-sleep');
//sleep(200);


/* REQUEST-ROUTING TABLE */
/*********************************************/
app.post('/new_game', urlencodedParser, function (req, res) {
		
		// 01. get player types
		var p1_type = req.body.p1_type;
		var p2_type = req.body.p1_type;

    console.log("new_game");
    console.log("p1_type : " + p1_type);
    console.log("p2_type : " + p2_type);
    console.log("****************************************");

		// 02. init new game with player types

		// 03. send environment config to front-end
		//console.log(environment)		
		res.end(JSON.stringify(environment));
});

/* HUMAN player requests */
/*********************************************/
app.post('/deploy_human', urlencodedParser, function (req, res) {
    
    // 01. get player types
    var target = req.body.target;
    var count = req.body.count;

    console.log("human deploy");
    console.log("target : " + target);
    console.log("count : "+ count);
    console.log("****************************************");

    // 02. init new game with player types
    var response = {
      "success": 1,
      "msg": "none"
    };

    

    // 03. send environment config to front-end  
    res.end(JSON.stringify(response));
});

app.post('/march_human', urlencodedParser, function (req, res) {
    
    // 01. get player types
    var from_country = req.body.from; 
    var to_country = req.body.to;
    var count = req.body.count;

    console.log("human march");
    console.log("from : " + from_country);
    console.log("to : "+ to_country);
    console.log("count : "+ count);
    console.log("****************************************");

    // 02. init new game with player types
    var response = {
      "success": 1,
      "msg": "none"
    };

    // 03. send environment config to front-end  
    res.end(JSON.stringify(response));
});

app.post('/invade_human', urlencodedParser, function (req, res) {
    
    // 01. get player types
    var from_country = req.body.from;
    var to_country = req.body.to;
    var residual_troops = req.body.residual_troops;

    console.log("human invade");
    console.log("from : " + from_country);
    console.log("to : "+ to_country)
    console.log("to : "+ residual_troops);
    console.log("****************************************");

    // 02. init new game with player types
    var response = {
      "success": 1,
      "msg": "none",
      "game_status": "ongoing",
      "winner": "none",
      "reward": 8
    };

    // 03. send environment config to front-end  
    res.end(JSON.stringify(response));
});

/* AGENT player requests */
/*********************************************/
app.get('/deploy_pc', function (req, res) {

    // 02. form response
    var response = {
      "change": 1,
      "target": 3,
      "count": 5
    };

    console.log("agent deploy");
    console.log(response);
    console.log("****************************************");

    // 03. send environment config to front-end  
    res.end(JSON.stringify(response));
});

app.get('/march_pc', function (req, res) {

    console.log("marching");
    // 02. form response
    var response = {
      "change": 1,
      "from": 3,
      "to": 4,
      "count": 5
    };

    console.log("agent march");
    console.log(response);
    console.log("****************************************");

    // 03. send environment config to front-end  
    res.end(JSON.stringify(response));
});

app.get('/invade_pc', function (req, res) {

    // 02. form response
    var response = {
      "change": 1,
      "from": 3,
      "to": 2,
      "residual_troops": 5,
      "game_status": "ongoing",
      "winner": "none",
      "reward": 5
    };

    console.log("agent invade");
    console.log(response);
    console.log("****************************************");

    // 03. send environment config to front-end  
    res.end(JSON.stringify(response));
});
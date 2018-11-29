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


/* REQUEST-ROUTING TABLE */
/*********************************************/
app.post('/new_game', urlencodedParser, function (req, res) {
		
		// 01. get player types
		var p1_type = req.body.p1_type; // console.log(p1_type);
		var p2_type = req.body.p1_type; // console.log(p2_type);

		// 02. init new game with player types

		// 03. send environment config to front-end
		//console.log(environment)		
		res.end(JSON.stringify(environment));
});
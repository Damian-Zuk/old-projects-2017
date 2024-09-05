var express = require('express');
var app = express();
var server = require('http').Server(app);
var IP = 'localhost';
var PORT = 80;
var TICK = 60;
var DEBUG_MODE = true;

app.use('/', express.static( __dirname + '/client' ));
server.listen(PORT, 'localhost', () =>{
	console.log("Server started on " + IP + ":" + PORT);
});
var socketList = [];
var playersList = [];

var io = require('socket.io')(server, {});
io.sockets.on('connection', (socket) =>{
	socket.id = socketList.length;
	socketList.push(socket);
	console.log("Socket conneted: " + socket.id);
	socket.on('login', (data) => {
		playersList[socket.id] = new Player(socket.id, 2000, 2000, "DEBUG_"+socket.id);
		console.log("Player " + playersList[socket.id].nick + " logged into game.");
		for(var i in socketList){
			if(socket.id != socketList[i].id) socketList[i].emit('chatMsg', "<div style=\"color: yellow\">"+playersList[socket.id].nick+" joined to the game.</div>");
		}
		var welcomePack = {
			id: socket.id,
			nick: playersList[socket.id].nick
		};
		socket.emit('map', grid);
		socket.emit('welcome', welcomePack);
		socket.emit('chatMsg', "<div style=\"color: rgb(223, 210, 33)\">Welcome to the server! Type /help for chat commands.</div>");
		socket.on('keyState', (state) => {
			playersList[socket.id].keyState = state;
			playersList[socket.id].update();
		});
		socket.on('debugCommand', (data) => {
			if(DEBUG_MODE){
				var res = eval(data);
				socket.emit('debugResponse', res);
			}
		});
		socket.on('sendChatMsg', (data) => {
			for(var i in socketList){
				socketList[i].emit('chatMsg', "<div>"+playersList[socket.id].nick+": <span class=\"msgContent\">"+data+"</span></div>");
			}
		});
		socket.on('sendPrivChatMsg', (data) => {
			var reciver = data[0];
			var pm = data[1];
			var pack = {
				sender: playersList[socket.id].nick,
				message: "<span class=\"msgContent\">"+pm+"</span>"
			}
			for(var i in playersList){// TODO: zoptymalizowac szukanie
				if(playersList[i].nick == reciver){
					socketList[i].emit('privChatMsg', pack);
				}
			}
		});
	});
	socket.on('disconnect', () => {
		console.log("Socket disconnected: " + socket.id);
		for(var i in socketList){
			socketList[i].emit('chatMsg', "<div style=\"color: yellow\">"+playersList[socket.id].nick+" left the game</div>");
		}
		delete socketList[socket.id];
		delete playersList[socket.id];
	});
});

function m2dArray(col, row){
	var a = new Array(col);
	for (var i = 0; i < a.length; i++){
		a[i] = new Array(row);
	}
	return a;
}

var Player = function(id, x, y, nick){
	this.x = x;
	this.y = y;
	this.id = id;
	this.speed = 200;
	this.nick = nick;
	this.keyState = [];
	this.update = function(){
		if(this.keyState[65] == true){
			this.x -= Math.round(this.speed/TICK);
		}
		if(this.keyState[68] == true){
			this.x += Math.round(this.speed/TICK);
		}
		if(this.keyState[87] == true){
			this.y -= Math.round(this.speed/TICK);
		}
		if(this.keyState[83] == true){
			this.y += Math.round(this.speed/TICK);
		}
	};
};
var Chunk = function(x, y, type){
	this.x = x;
	this.y = y;
	this.type = type;

};
var mapW = 40;
var mapH = 40;
var grid = m2dArray(mapW, mapH);
var Setup = function(){
	for(var i = 0; i < mapW; i++){
		for(var j = 0; j < mapH; j++){
			grid[i][j] = new Chunk(i*100, j*100, 'grass');
		}
	}
	Update();
}

var Update = function(){
	var serverLoop = setInterval(function(){
		var pack = [];
		for(var i in playersList){
			playersList[i].update();
			pack.push({
				id:playersList[i].id,
				x:playersList[i].x,
				y:playersList[i].y,
				nick:playersList[i].nick
			});
		}
		for(var i in socketList){
				socketList[i].emit('playersInfo', pack);
		}
	}, 1000/TICK);
}
Setup();

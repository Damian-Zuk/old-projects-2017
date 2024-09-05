var FRAME_RATE = 60;
var playersList = [];
var nick;
var playerImage = new Image();
var grass = new Image();
var grid = null;
var myId = null;
var cameraOffsetX = canvas.width/2;
var cameraOffsetY = canvas.height/2 + 100;
var Player = function(id, nick, x, y){
	this.nick = nick;
	this.id = id;
	this.x = x;
	this.y = y;
	this.size = 150;
};
var login = function(n){
	socket.emit('login', n);
}
var clearCanvas = function(){
	ctx.fillStyle = "black";
	ctx.fillRect(0, 0, canvas.width, canvas.height);
}
var drawMap = function(grd){
	var StartX = Math.floor((playersList[myId].x-cameraOffsetX)/100);
	var StartY = Math.floor((playersList[myId].y-cameraOffsetY)/100);
	var EndX = Math.floor((playersList[myId].x-cameraOffsetX+canvas.width)/100);
	var EndY = Math.floor((playersList[myId].y-cameraOffsetY+canvas.height)/100);
	for(var i = StartX; i <= EndX; i++){
		for(var j = StartY; j <= EndY; j++){
			ctx.drawImage(grass, 0, 0, 256, 256, grid[i][j].x-playersList[myId].x+cameraOffsetX, grid[i][j].y-playersList[myId].y+cameraOffsetY, 100, 100);
		}
	}
}
var Setup = function(arg){
	nick = "debug"+Math.random();
	login(nick);
	playerImage.src = "img/player.png";
	grass.src = "img/grass.png";
	ctx.font = '18px Viga';
	ctx.textAlign = 'center';
	socket.on('playersInfo', function(info){
		playersList.splice(0, playersList.length);
		for(var i in info){
			playersList[info[i].id] = new Player(info[i].id, info[i].nick, info[i].x, info[i].y);
		}
	});
	socket.on('map', function(data){
		grid = data;
	});
	socket.on('welcome', function(data){
		myId = data.id;
		nick = data.nick;
	});
	Update();
};

var Update = function(){
	var gameLoop = setInterval(function(){
		clearCanvas();
		if(playersList[myId] != undefined){
			drawMap(grid);
			ctx.fillStyle = "white";
			for(var i in playersList) {
				if(myId === playersList[i].id){
					ctx.fillText("DEBUG_" + playersList[i].id, cameraOffsetX, cameraOffsetY-playersList[i].size);
					ctx.drawImage(playerImage, 0, 0, 256, 256, cameraOffsetX-playersList[i].size/2, cameraOffsetY-playersList[i].size, playersList[i].size, playersList[i].size);
				}
				else{
					ctx.fillText("DEBUG_" + playersList[i].id, playersList[i].x-playersList[myId].x+cameraOffsetX, (playersList[i].y-playersList[i].size)-playersList[myId].y+cameraOffsetY);
					ctx.drawImage(playerImage, 0, 0, 256, 256, (playersList[i].x-playersList[i].size/2)-playersList[myId].x+cameraOffsetX, (playersList[i].y-playersList[i].size)-playersList[myId].y+cameraOffsetY, playersList[i].size, playersList[i].size);
				}
			}
		}
	}, 1000/FRAME_RATE);
}
window.onload = Setup();

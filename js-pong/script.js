var centerX = canvas.width/2;
var centerY = canvas.height/2;
var score = 0;

function Round(n, k)
{
    var factor = Math.pow(10, k);
    return Math.round(n*factor)/factor;
}

function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

var Ball = function(){
	this.X = canvas.width/2;
	this.Y = centerY/2;
	this.angle = 45;
	this.ballSpeed = 12;
	this.speedX = this.ballSpeed*Math.sin(0.4*Math.PI);
	this.speedY = this.ballSpeed*Math.sin(0.4*Math.PI);
	this.radius = 12;



	this.Draw = function(){
		ctx.beginPath();
		ctx.fillStyle = '#E3E3E3';
		ctx.arc(this.X, this.Y, this.radius, 0, 2 *Math.PI, false);
		ctx.fill();
		ctx.closePath();		
	}
	this.testCollisionRR = function(x1, y1, w1, h1, x2, y2, w2, h2){
        return x1 <= x2+w2
                && x2 <= x1+w1
                && y1 <= y2 + h2
                && y2 <= y1 + h1;
	}

	this.CheckCollisions = function(paddleX, paddleY, paddleW, paddleH){
		if((this.Y <= (this.radius+this.ballSpeed))){
			this.speedY = -this.speedY;
		}
		if((this.X >= canvas.width-(this.radius) || this.X <= this.radius+this.ballSpeed)){
			this.speedX = -this.speedX;
		}
		/*if(this.X > paddleX && this.X < paddleX+paddleW && this.Y > paddleY-(this.radius+this.ballSpeed) && this.Y < paddleY+paddleH){*/
		if(this.testCollisionRR(this.X, this.Y, this.radius, this.radius, paddleX, paddleY, paddleW, paddleH)){
			var pop = (this.X - paddleX) / (paddleW+this.radius);
			var ang = 0.5 * Math.PI * (pop*2 - 1);
			this.speedX = this.ballSpeed*Math.sin(ang);
			this.speedY = -1 * this.ballSpeed*Math.cos(ang);
		}
		if(this.X > canvas.width-this.radius) this.X = canvas.width-this.radius-this.ballSpeed;
		else if(this.X < this.radius) this.X = this.radius + this.ballSpeed;
		if(this.Y < this.radius) this.Y = this.radius + this.ballSpeed;
		else if((this.Y > paddleY) && (this.X > paddleX && this.X < paddleX + paddleW) && this.Y > paddleY-(this.radius+this.ballSpeed) && this.Y < paddleY+paddleH)
		 this.Y = paddleY - this.radius;
	}

	this.Update = function(paddleX, paddleY, paddleW, paddleH){
		this.CheckCollisions(paddleX, paddleY, paddleW, paddleH);
		this.Draw();
		this.X += this.speedX;
		this.Y += this.speedY;	
	}
}

var DrawLine = function(){
	ctx.fillStyle = "#606060";
	var odcinki = 21; // Tylko nieparzyste
	var szerokosc = 600 / odcinki;
	var wysokosc = 20;

	for(odstep = 0; odstep < 600; odstep += szerokosc*2)
		ctx.fillRect(odstep, canvas.height/2 - wysokosc/2, szerokosc, wysokosc);
}

var keyState = {};    
window.addEventListener('keydown',function(e){
    keyState[e.keyCode || e.which] = true;
},true);    
window.addEventListener('keyup',function(e){
    keyState[e.keyCode || e.which] = false;
},true);


var Paddle = function(X, Y, type){
	this.height = 20;
	this.width = 150;
	this.type = type;
	this.paddleSpeed = 60;
	this.X = canvas.width/2-this.width/2;
	this.Y = Y;

	this.Move = function(e){
		if(type === "PLAYER")
		{
			if(keyState[37] && this.X > 5) this.X -= 5;
			else if(keyState[39] && (this.X+this.width) < canvas.width-5) this.X += 5;
		}
	}

	this.Draw = function(){
		ctx.fillStyle = "#DBDBDB";
		ctx.fillRect(this.X, this.Y, this.width, this.height);
	}
	this.Update = function(){
		this.Move();
		this.Draw();
	}
}



var Update = function(){
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	ctx.fillStyle = "#181818";
	ctx.fillRect(0, 0, canvas.width, canvas.height);
	DrawLine();
	ball.Update(playerPaddle.X, playerPaddle.Y, playerPaddle.width, playerPaddle.height);
	playerPaddle.Update();
	//enemyPaddle.Update();
}
var ball = new Ball();
var playerPaddle = new Paddle(20, 900, "PLAYER");
var enemyPaddle = new Paddle(canvas.width/2-75, 200, "ENEMY");
var gameLoop = setInterval(Update, 1000/60);




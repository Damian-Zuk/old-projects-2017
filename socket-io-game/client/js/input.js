//left 65
//right 68
//up 87
//down 83
var keyState = [];

window.addEventListener("keydown", function(e){
	if($("#chatMsg").is(':focus') === false){
		console.log(e.keyCode);
		if((e.keyCode == 65 || e.keyCode == 68 || e.keyCode == 87 || e.keyCode == 83) && (keyState[e.keyCode] == false  || keyState[e.keyCode] == undefined)){
			keyState[e.keyCode] = true;
			socket.emit('keyState', keyState);
		}
		if(e.keyCode == 13 && (keyState[13] == false || keyState[13] == undefined)){
			toggleChat(true);

		}
		keyState[e.keyCode] = true;
	}else if(e.keyCode == 27){
		toggleChat(false);
	}
}, false);
window.addEventListener("keyup", function(e){
	if($("#chatMsg").is(':focus') === false){
		keyState[e.keyCode] = false;
		if(e.keyCode == 65 || e.keyCode == 68 || e.keyCode == 87 || e.keyCode == 83) socket.emit('keyState', keyState);
	}else if(e.keyCode == 13) keyState[e.keyCode] = false;

}, false);

var mouseBState = [];
window.addEventListener("mouseup", function(e){
	mouseBState[e.button] = false;
}, false);
window.addEventListener("mousedown", function(e){
	mouseBState[e.button] = true;
}, false);

var mouseX = 0;
var mouseY = 0;
window.addEventListener("mousemove", function(e){
	var rect = canvas.getBoundingClientRect();
	mouseX = Math.round((e.clientX-rect.left)/(rect.right-rect.left)*canvas.width);
	mouseY = Math.round((e.clientY-rect.top)/(rect.bottom-rect.top)*canvas.height);
}, false);

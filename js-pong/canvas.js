var canvas = document.getElementById("main");
var ctx = canvas.getContext("2d");

var cTop = document.getElementById("top-bar");
var ctxTop = cTop.getContext("2d");



ctx.fillStyle = "#181818";
ctx.fillRect(0, 0, canvas.width, canvas.height);

ctxTop.fillStyle = "#080808";
ctxTop.fillRect(0, 0, cTop.width, cTop.height);

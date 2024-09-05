$("#chatMsg").val("");
var chatContainer = document.getElementById('chatContainer');
var chatMsg = document.getElementById('chatMsg');
var lastMsgs = document.getElementById('lastMsgs');
var pressToChat = document.getElementById('pressToChat');
var chatMsgForm = document.getElementById('chatMsgForm');
var chatOpen = false;
var clearDelay = null;
var lm = [];
var global = [];
var privChats = [];
var currentChat = global;
var currentWindow = "global";
var addToLastMessages = function(data){
	if(!chatOpen){
		lm.push(data);
		if(lm.length > 6){
			lastMsgs.innerHTML = "";
			for(var i = lm.length-6; i < lm.length; i++){
				lastMsgs.innerHTML += lm[i];
			}
		}else{
			lastMsgs.innerHTML = "";
			for(var i in lm){
				lastMsgs.innerHTML += lm[i];
			}
		}
		clearTimeout(clearDelay);
		clearDelay = setTimeout(function(){
			lastMsgs.innerHTML = "";
			lm.splice(0, lm.length);
		}, 4000);
	}
};
socket.on('chatMsg', function(data){
	global.push(data);
	updateChat(currentChat);
	addToLastMessages(data);
});

socket.on('privChatMsg', function(data){
  if(!checkChatWindow(data.sender)){
    createChatWindow(data.sender);
    privChats[data.sender] = [];
    global.push("<div style=\"color:yellow\">"+data.sender+" sent you private message.<div>");
		addToLastMessages("<div style=\"color:yellow\">"+data.sender+" sent you private message.<div>");
  }
  privChats[data.sender].push(data.sender+": "+data.message);
	if(currentWindow != data.sender){
		startBlinking(data.sender);
	}
	updateChat();
});
var blinking = [];
var blInt = [];
var blink = function(){

};
var stopBlinking = function(chat){
	clearInterval(blInt[chat]);
	setTimeout(function(){if(document.getElementById(chat) != null) document.getElementById(chat).className = "cs active"}, 10);
};
var startBlinking = function(chat){
	blInt[chat] = setInterval(function(){
		document.getElementById(chat).className = "cs blink";
		setTimeout(function(){
			document.getElementById(chat).className = "cs";
		}, 500);
	}, 1000);
};

var toggleChat = function(what){
	if(what == false){
		chatMsg.blur();
		$("#chatContainer").css("display", "none");
		$("#pressToChat").css("display", "block");
		$("#lastMsgsContainer").css("display", "block");
		$("#chatMsg").val("");
		chatOpen = false;
	}else{
		$("#chatContainer").css("display", "block");
		$("#pressToChat").css("display", "none");
		$("#lastMsgsContainer").css("display", "none");
		lastMsgs.innerHTML = "";
		lm.splice(0, lm.length);
		chatOpen = true;
		chatMsg.focus();
	}
};

var justSent = false;
var updateChat = function(){
	var chat = document.getElementById("chat");
	var scroll = false;
	if(!justSent){
		if(chat.scrollTop+$(".msgs").height() == chat.scrollHeight) scroll = true;
	}else{
		scroll = true;
	}
	chat.innerHTML = "";
	for(var i in currentChat){
		chat.innerHTML += "<div class=\"msg\">"+currentChat[i]+"</div>";
	}
	if(scroll) chat.scrollTop = chat.scrollHeight;
	justSent = false;
};

var activeCs = function(name){
	setTimeout(function(){
		stopBlinking(name);
		if(name != "global") currentChat = privChats[name];
		else currentChat = global;
		var cs = document.getElementById('chatSelect');
		for(var i in cs.children){
			if(cs.children[i].className != "exitButton"){
				if(cs.children[i].id == name){
					cs.children[i].className = "cs active";
				}else{
					cs.children[i].className = "cs";
				}
			}
		}
		currentWindow = name;
		updateChat();
	}, 10);
};

var closeChatWindow = function(name){
	document.getElementById(name).remove();
	var temp = currentWindow;
	if(currentChat == privChats[name]) setTimeout(function(){activeCs("global")}, 20);
	else setTimeout(function(){activeCs(temp)}, 20);
};

var checkChatWindow = function(chatName){
	var cs = document.getElementById('chatSelect').children;
	for(var i in cs){
		if(cs[i].id == chatName) return true;
	}
	return false;
};

var createChatWindow = function(name){
  var cs = document.getElementById('chatSelect');
  cs.innerHTML += "<div class=\"cs\" id=\""+name+"\" onclick=\"activeCs('"+name+"')\">"+name+"<div class=\"exitButton\" onclick=\"closeChatWindow('"+name+"')\" style=\"display: inline-block; width: 20px; height: 20px; margin-left: 5px; vertical-align: middle\"></div></div>";
};

var checkChatArray = function(name){
	if(privChats[name] == undefined){
		privChats[name] = [];
		privChats[name].push("<span style=\"color: yellow\">You started private conversation with "+name+".<span>");
		currentChat = privChats[name];
	}
};

chatMsgForm.onsubmit = function(e){
	e.preventDefault();
	justSent = true;
	var message = $("#chatMsg").val();
	var pm = []; //
	if(currentWindow == "global"){
		if(message.substr(0,3) == "/w "){
			var spt = message.split(" ");
			pm[0] = spt[1];
			for(var i in spt){
				if(i == 2){
					pm[1] = spt[i];
				}else if(i > 2){
					pm[1] += " "+spt[i];
				}
			}
			if(pm[1] != undefined && pm[1] != ""){
				socket.emit('sendPrivChatMsg', pm);
				if(privChats[pm[0]] == undefined){
					checkChatArray(pm[0]);
					privChats[pm[0]].push(nick+": <span class=\"msgContent\">"+pm[1]+"</span>");
				}
			}
			if(!checkChatWindow(pm[0])){
				createChatWindow(pm[0]);
				activeCs(pm[0]);
			}
		}else if(message.substr(0,6) == "/help"){
			global.push("<span style=\"color: yellow\">Available global chat commands:</span>");
			global.push("&nbsp;&nbsp;&nbsp;<span style=\"color: yellow\"> /help - view avaliable commands </span>");
			global.push("&nbsp;&nbsp;&nbsp;<span style=\"color: yellow\"> /w [nick] [optional:message] - open private chat</span>");
			updateChat();
		}else{
			if($("#chatMsg").val() != "") socket.emit('sendChatMsg', message);
		}
	}else{
		if(message != undefined && message != ""){
			var pack = [currentWindow, message];
			socket.emit('sendPrivChatMsg', pack);
			checkChatArray(currentWindow);
			privChats[currentWindow].push(nick+": <span class=\"msgContent\">"+message+"</span>");
		}
	}
	updateChat();
	$("#chatMsg").val("");
};

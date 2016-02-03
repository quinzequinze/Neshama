var usbmux = require('usbmux');
var net = require('net');
var pingDelay = 1000;
var activeSocket;
var CRLF = "\r\n";

var usbDeamon = false;

var flag = {
    usb: false,
    relay: false,
    tunnel: false,
    pd: false
};

if(usbDeamon){
var listener = new usbmux.createListener().on('error', function(err) {}).on('attached', function(udid) {
    console.log("usb : on");
    flag.usb = true;
}).on('detached', function(udid) {
    console.log("usb : off");
    flag.usb = false;
});

function relay() {
    usbmux.Relay(20000, 5000).on('error', function(err) {
        console.log("relay : off");
        flag.relay = false;
    }).on('ready', function(udid) {
        console.log("relay : on");
        flag.relay = true;
    }).on('data', function(data) {
        console.log(data.toString());
    })
}



function tunnel() {
    usbmux.getTunnel(20000, 100).then(function(tunnel) {
        console.log("tunnel : on");
        flag.tunnel = true;
        activeSocket = tunnel;
        activeSocket.write("this is the relay" + CRLF);
        console.log(activeSocket.connected);
        tunnel.on('data', function(data) {
            console.log(data.toString());
              io.emit("msg",data.toString());
            //pdSocket.write(data.toString());
        }).on('close', function(data) {
            flag.tunnel = false;
        });;
    }).catch(function(err) {
        //console.log("tunnel : off");
        flag.tunnel = false;
    })
}
}
function ping() {
	
	/*if(!flag.pd){
		pdConnect();
	}*/
    if(usbDeamon){
    if (!flag.tunnel) {
        tunnel();
    }
    if (!flag.relay) {
        relay();
    }
}
    if (flag.tunnel == true && flag.relay == true && flag.usb == true) {
        //clearInterval(pinger);
    } else {
        console.log("ping");
    }
}
var pinger = setInterval(ping, pingDelay);

///////////////////////////////

var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var express = require('express');
var fs = require('fs');

var videoListArray;

app.use(express.static(__dirname));
app.use(express.static(__dirname + '/video'));
app.use(express.static(__dirname + '/css'));
app.use(express.static(__dirname + '/img'));
app.use(express.static(__dirname + '/audio'));

app.get('/', function(req, res) {
  res.sendfile(__dirname + '/index.html');
  console.log("reload");
    // res.sendfile('idSelec.html');
});

//video array 

http.listen(4000, function() {
  console.log('listening on *:4000' + __dirname);
});

//socket.io events
io.on('connection', function(socket) {
  console.log("Hello player");
  io.emit("msg","welcome");


fs.readFile(__dirname+'/videoList.txt', function(err, data) {
    if(err) throw err;
    var videoListArray = data.toString().split("\n");
      io.emit("videoList", videoListArray);
});

  socket.on('disconnect', function(socket) {
    console.log("bye player");
  });

});


//to do -> blow event 

var fullScreen = false;
var v = document.getElementsByTagName("video")[0];
var sfx = document.getElementById("sfx");
var loop = document.getElementById("loop");
var m = document.getElementById("mask");
var g = document.getElementById("gab");
var s = document.getElementById("gabSquare");
var d = document.getElementById("debug");
var v_Dir = "/video/";
var a_Dir = "/audio/"
var maxValue = 0.5;
var vCount = 0;
var flag = {
    mask: false,
    gab: false,
    gabSquare: false,
    debug: false,
    debugMode: true,
    blow:false
}
var lastEvent = "null";
var lastReading = "null";
var lastVideoName = "null";
var lastVideoIndex = "null";
v.play();
//——————————————
//——————————————
//——————————————  CONTROLS
//——————————————
//——————————————
key('enter', function() {
    if (!fullScreen) {
        enterFullscreen();
    } else {
        exitFullscreen();
    }
});
key('s', function() {
    if (!gabSquare.flag) {
        s.style.display = 'block';
        gabSquare.flag = true;
    } else {
        s.style.display = 'none';
        gabSquare.flag = false;
    }
});
key('g', function() {
    console.log("gab :" + gab.flag);
    if (!gab.flag) {
        g.style.display = 'block';
        gab.flag = true;
    } else {
        g.style.display = 'none';
        gab.flag = false;
    }
});
key('m', function() {
    console.log("mask :" + mask.flag);
    if (!mask.flag) {
        m.style.display = 'block';
        mask.flag = true;
    } else {
        m.style.display = 'none';
        mask.flag = false;
    }
});
key('d', function() {
    console.log("debug :" + flag.debug);
    if (!flag.debug) {
        d.style.display = 'block';
        flag.debug = true;
    } else {
        d.style.display = 'none';
        flag.debug = false;
    }
    debugUp();
});
key('left', function() {
    m.style.left = (parseFloat(getComputedStyle(m).getPropertyValue("left"))) - 10 + "px";
});
key('right', function() {
    m.style.left = (parseFloat(getComputedStyle(m).getPropertyValue("left"))) + 10 + "px";
});
key('up', function() {
    if (vCount < videoListArray.length - 1) {
        vCount++;
    } else {
        vCount = 0;
    }
    v.src = videoListArray[vCount];
});
key('down', function() {
    if (vCount == 0) {
        vCount = videoListArray.length - 1;
    } else {
        vCount--;
    }
    v.src = videoListArray[vCount];
});
//——————————————
//——————————————
//——————————————  FUNCTIONS
//——————————————
//——————————————
function parseMsg(data) {
    data = data.split(" ");
    var header = data[0];
    lastEvent = header;
    switch (header) {
        case "connected":
            console.log("CONNECTED");
            v.src = '';
            loop.src = '';
            sfx.src = '';
            break; 
        case "deconnected":
            console.log("DECONNECTED");
            v.src = '';
            loop.src = '';
            sfx.src = '';
            break;
        case "keepBlowing":
            v.src = v_Dir + 'keepBlowing.mp4';
            loop.src = 'keepBlowing.wav';
            break;
        case "blow":
        //if(flag.blow = false){
            loop.src = '';
            sfx.src = 'blow.wav';
            flag.blow = true;
        //}
            break;
        case "start":
            console.log("START");
            flag.blow = false;
            loop.src = 'warming.wav';
            sfx.src = 'start.wav';

            v.src = v_Dir + 'warming.mp4';
            break;
        case "analysing":
            console.log("ANALYSING");
            v.src = v_Dir + 'analysing.mp4';
            loop.src = 'analysingLoop.wav';
            sfx.src = 'analysingSfx.wav';
            break;
        case "reading":
            if (flag.debugMode) {
                data[1] = document.getElementsByTagName('input')[0].value;
            }
            console.log("READING");
            console.log(data[1]);
            lastReading = data[1];
            if (data[1] >= maxValue) {
                data[1] = maxValue-0.1;
            }
            getFace(data[1]);
            loop.src = 'readingLoop.wav';
            sfx.src = 'readingSfx.wav';
            break;
        default:
    }
    debugUp();
}

function getFace(reading) {
    var videoIndex = Math.round((videoListArray.length / maxValue) * reading);
    v.src = videoListArray[videoIndex];
    console.log(videoIndex + " " + videoListArray[videoIndex]);
    lastVideoIndex = videoIndex;
    lastVideoName = videoListArray[videoIndex];
    debugUp();
}
init = true;
key('t', function() {
    face(1);
});

function debugUp() {
    d.innerHTML = "<p>lastEvent: " + lastEvent + "</p><p>lastReading: " + lastReading + "</p><p>lastVideoName: " + lastVideoName + "</p><p>lastVideoIndex: " + lastVideoIndex + "</p>";
}
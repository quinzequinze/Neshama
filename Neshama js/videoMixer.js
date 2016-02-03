var instal = instal || {};
var fullScreen = false;
var v = document.getElementsByTagName("video")[0];
var m = document.getElementById("mask");
var g = document.getElementById("gab");
var s = document.getElementById("gabSquare");
var a = document.getElementsByTagName("audio")[0];

var v_Dir = "/video/"
var maxValue = 2;
var flag = {
    mask: false,
    gab: false,
    gabSquare: false
}
var countTop = null;
var firstBlow = true;

v.play();
//Debug ethylo steps
key('shift+S', function() {
    parseMsg("start");
});
key('shift+W', function() {
    parseMsg("warming 00");
});
key('shift+B', function() {
    parseMsg("blow");
});
key('shift+K', function() {
    parseMsg("keepBlowing");
});
key('shift+A', function() {
    parseMsg("analysing");
});
key('shift+R', function() {
    parseMsg("reading 0.0");
});


//CONTROLS
key('enter', function() {
    if (!fullScreen) {
        enterFullscreen();
    } else {
        exitFullscreen();
    }
});
key('space', function() {
    v.src = 'b.mp4';
});

key('s', function() {
    if (!gab.flag) {
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


key('a', function() {
    v.src = 'a.mp4';
});
key('left', function() {
    m.style.left = (parseFloat(getComputedStyle(m).getPropertyValue("left"))) - 10 + "px";
});
key('right', function() {
    m.style.left = (parseFloat(getComputedStyle(m).getPropertyValue("left"))) + 10 + "px";
});
key('d', function() {
    console.log(v.duration);
});


for (var i = 1; i < 9; i++) {
    key(i.toString(), function() {
        v.src = 'robin' + i + '.mp4';
    });
}

//PARSING
function parseMsg(data) {
    data = data.split(" ");
    var header = data[0];
    switch (header) {
        case "connected":
            console.log("CONNECTED");
            v.src = '';
            break;
        case "deconnected":
            console.log("DECONNECTED");
            v.src = '';
            break;
        case "start":
            console.log("START");
            countTop = null;
            v.src = '';
            a.src = "start.wav";
            a.play();
            break;
        case "warming":
            console.log("WARMING");
            if (countTop == null) {
                countTop = data[1];
                v.src = v_Dir + 'warming.mp4';
                a.src = "warming.wav";
                a.play();
                a.loop = true;
                firstBlow = true;
            }
            // v.currentTime = data[1]*50/countTop;
            break;
        case "blow":
            if (firstBlow) {
                a.loop = false;
                a.src = "blow.wav";
                a.play();
                firstBlow = false;
            };
            console.log("BLOW");
            v.src = v_Dir + 'blow.mp4';
            break;
        case "keepBlowing":
            //Only one event, set loop
            console.log("KEEPBLOWING");
            v.src = '';
            a.src = "keepBlowing.wav";
            a.play();
            a.loop = true;
            break;
        
        case "analysing": 
            console.log("ENDBLOW + ANALYSING");
            a.loop = false;
            a.src = "endBlow.wav";
            a.play();
            a.addEventListener('ended', playAnalysingSound);
            v.src = v_Dir + 'analysing.mp4';

            function playAnalysingSound(e) {
                a.loop = true;
                a.src = "analysing.wav";
                a.play();
                a.removeEventListener('ended', playAnalysingSound);
            };
            break;

        case "reading":
            console.log("READING + VIDEO LOOP");
            //v.src = 'value.mov';
            getFace(data[1]);
            a.loop = false;
            a.src = "reading.wav";
            a.play();
            break;
        default:
    }
}

function getFace(reading) {
    var videoIndex = Math.round((videoListArray.length / maxValue) * reading);
    v.src = videoListArray[videoIndex];
    console.log(videoIndex + " " + videoListArray[videoIndex]);
}
init = true;
key('t', function() {
    face(1);
});
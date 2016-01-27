document.cancelFullScreen = document.webkitCancelFullScreen || document.mozCancelFullScreen;
var elem = document.documentElement;

function onFullScreenEnter() {
    fullScreen = true;
    elem.onwebkitfullscreenchange = onFullScreenExit;
    elem.onmozfullscreenchange = onFullScreenExit;
};
// Called whenever the rowser exits fullscreen.
function onFullScreenExit() {
    fullScreen = false;
};

function enterFullscreen() {
    console.log("enterFullscreen()");
    elem.onwebkitfullscreenchange = onFullScreenEnter;
    elem.onmozfullscreenchange = onFullScreenEnter;
    if (elem.webkitRequestFullScreen) {
        elem.webkitRequestFullScreen(Element.ALLOW_KEYBOARD_INPUT);
    } else {
        elem.mozRequestFullScreen();
    }
}

function exitFullscreen() {
    console.log("exitFullscreen()");
    document.cancelFullScreen();
}
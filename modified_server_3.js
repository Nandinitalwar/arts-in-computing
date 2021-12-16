const evtSource = new EventSource("http://0.0.0.0:8889", { } );

var audioCtx;
var modulatorFreq;
var modulationIndex;


evtSource.onmessage = function(event) {
  const parsed_data = JSON.parse(event.data)
  val_x = parsed_data.x
  val_y = parsed_data.y
  val_z = parsed_data.z
  const g = 9.81;
  var pitch = (Math.asin(Math.abs(parsed_data.x)/g))*(180/Math.PI);
  console.log("pitch in degrees: " + pitch); 
  //in the pitch, y values are constant
  console.log("X : " + parsed_data.x);
  console.log("Y :" + parsed_data.y);
  console.log("Z :" +parsed_data.z);
  var roll = (Math.atan(Math.abs(parsed_data.y)/Math.abs(parsed_data.z)))*(180/Math.PI);
  //in the roll, x values are constant
  console.log("roll in degrees: " + roll);
  //loadSound("santa_tell_me.mp3", "kick");
  //it is not possible to calculate the yaw 
  modulatorFreq.frequency.value = 100;
  modulatorFreq.frequency.value = val_x;

}
function initFM() {
    // create web audio api context
    audioCtx = new (window.AudioContext || window.webkitAudioContext)
    /** was trying to play without click
    audioCtx.play()
    console.log(audioCtx.state) **/
    // create Oscillator node
    var carrier = audioCtx.createOscillator();
    modulatorFreq = audioCtx.createOscillator();
    //The GainNode interface represents a change in volume
    modulationIndex = audioCtx.createGain();
    modulationIndex.gain.value = 100;
    modulatorFreq.frequency.value = 100;

    //connecting oscillator to gain
    modulatorFreq.connect(modulationIndex);
    //connecting gain to frequency of oscillator
    modulationIndex.connect(carrier.frequency)
    //connecting oscillator to destination of audioCtx
    carrier.connect(audioCtx.destination);
    
    carrier.start();
    modulatorFreq.start();
    while (true) {
        //what values should updateFreq and updateIndex ideally move between?
        //problem: could not find the origin
        if (pitch > 30) {
        updateFreq(val_x);
        updateIndex(val_z);
        //updateFreq(roll)
        //updateIndex(pitch);
        }
    
        if (pitch < 30) {
            //updateIndex(roll)
            //updateFreq(pitch)
            updateFreq(val_z);
            updateIndex(val_y);
        }

        if (roll < 30){
            updateFreq(val_x);
            updateIndex(val_y);
        }
    }
}

/**
 * trying to play a song from the internet by making 
 * an XMLHttpRequest using WebAudio 
*/

function loadSound(url, sourceName) {
    // Load buffer asynchronously
    var request = new XMLHttpRequest();
    request.open("GET", url, true);
    request.responseType = "arraybuffer";
    console.log("I RAN!");
    request.onload = function() {
        // Asynchronously decode the audio file data
        context.decodeAudioData(
            request.response,
            function(buffer) {
                if (!buffer) {
                    console.log('error decoding file data: ' + url);
                    return;
                }
                    window[sourceName] = buffer;
            }
        );
    }

    request.onerror = function() {
        console.log('error loading file data: ' + url);
    }

    request.send();
}


//changing how much the frequency changes
function updateFreq(val) {
    modulatorFreq.frequency.value = val;
};
//changing how much the amplitude of the frequency changes
function updateIndex(val) {
    modulationIndex.gain.value = val;
};



//attach a click listener to a play button
/*
document.querySelector('tonejsbutton')?.addEventListener('click', async () => {
	await Tone.start()
	console.log('audio is ready')
})*/


const playButton = document.querySelector('button');
playButton.addEventListener('click', function() {

    if(!audioCtx) {
        initFM();
        return;
	}

    if (audioCtx.state === 'suspended') {
        audioCtx.resume();
    }

    if (audioCtx.state === 'running') {
        audioCtx.suspend();
    }

}, false);

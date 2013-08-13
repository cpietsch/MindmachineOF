#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
	ofBackground(0);
	ofSetLogLevel(OF_LOG_VERBOSE);
    
    // SERIAL
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    serial.setup(0, 9600); //open the first device

    int bufferSize		= 512;
	sampleRate 			= 44100;
	phaseL 				= 0;
	phaseAdderL 			= 0.0f;
	phaseAdderTargetL 	= 0.0;
	phaseR 				= 0;
	phaseAdderR 			= 0.0f;
	phaseAdderTargetR 	= 0.0;
	volume				= initVolume;
	bNoise 				= false;
	
	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);
    
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    
    freqs = "batd";
    manual = 0;
    blinkMode = 0;
    freq=14.4;
    
    gui.setup("panel");
    gui.add(centralTone.set( "base", 200, 10, 400 ));
    gui.add(playButton.setup("play"));
    gui.add(stopButton.setup("stop"));
    gui.add(trackNumber.set( "trackNumber", 1, 1, 5 ));
    gui.add(loadButton.setup("load"));


    playButton.addListener(this,&testApp::playButtonPressed);
    stopButton.addListener(this,&testApp::stopButtonPressed);
    loadButton.addListener(this,&testApp::loadButtonPressed);


    gui.loadFromFile("settings.xml");

}

void testApp::playButtonPressed(){
    start();
    track.playItem(0);
}
void testApp::stopButtonPressed(){
    stop();
    track.stop();
}
void testApp::loadButtonPressed(){
    track.readXML("track"+ofToString(trackNumber)+".xml");
}

void testApp::setLED(float freq, int alt){
    ofLog(OF_LOG_NOTICE, ofToString(freqs)+ " " + ofToString(alt));
    int millis = 1000.0/(freq*2);
    string message = ofToString(millis)+','+ofToString(alt)+'\n';
    unsigned char* chars = (unsigned char*) message.c_str(); 
    int length = message.length();
    
    serial.writeBytes(chars, length);
}

//--------------------------------------------------------------
void testApp::update(){
    track.update();
    
    if(fadeOut){
		if(volume<=0){
			fadeOut=false;
			volume=0;
			play=false;
			ofSetFrameRate(60);
		} else {
			volume-=0.001;
		}
	}
	
	if(fadeIn){
		if(volume>=initVolume){
			fadeIn=false;
			volume=initVolume;
		} else {
			volume+=0.01;
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    ofFill();
    ofColor(255,255,255,60);
    ofRect(0, 0, (ofGetWidth()/track.track.size())*track.currentItem, 40);
    gui.draw();
}


void testApp::startSequenz(){
	cout << "start track" << endl;
	play = true;
	fadeIn=true;
    
}
void testApp::start(){
	cout << "start" << endl;
	play = true;
	fadeIn=true;
	fadeOut=false;
	frameChanged=true;
}
void testApp::stop(){
	cout << "start" << endl;
	fadeOut=true;
	fadeIn=false;
}

//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
	
	if(play){
		// sin (n) seems to have trouble when n is very large, so we
		// keep phase in the range of 0-TWO_PI like this:
		while (phaseL > TWO_PI){
			phaseL -= TWO_PI;
		}
		
		while (phaseR > TWO_PI){
			phaseR -= TWO_PI;
		}
		
		if ( bNoise == true){
			// ---------------------- noise --------------
			for (int i = 0; i < bufferSize; i++){
				lAudio[i] = output[i*nChannels    ] = ofRandom(0, 1) * volume;
				rAudio[i] = output[i*nChannels + 1] = ofRandom(0, 1) * volume;
			}
		} else {
			targetFrequencyL = (int)centralTone-(float)binauralBeat/2;
			phaseAdderTargetL = (targetFrequencyL / (float) sampleRate) * TWO_PI;
			
			targetFrequencyR = (int)centralTone+(float)binauralBeat/2;
			phaseAdderTargetR = (targetFrequencyR / (float) sampleRate) * TWO_PI;
			
			//phaseAdderL = 0.95f * phaseAdderL + 0.05f * phaseAdderTargetL;
			//phaseAdderR = 0.95f * phaseAdderR + 0.05f * phaseAdderTargetR;
			
			//smooth factor aus
			phaseAdderL = phaseAdderTargetL;
			phaseAdderR = phaseAdderTargetR;
			
			for (int i = 0; i < bufferSize; i++){
				phaseL += phaseAdderL;
				phaseR += phaseAdderR;
				
				float sampleL = sin(phaseL);
				float sampleR = sin(phaseR);
				
				lAudio[i] = output[i*nChannels    ] = sampleL * volume;
				rAudio[i] = output[i*nChannels + 1] = sampleR * volume;
			}
		}
	}
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	freq=track.getFreq(msg.message);
    blinkMode=track.getAlt(msg.message);
    
	if(freq!=0){
		binauralBeat=freq;
        setLED(freq, blinkMode);
		frameChanged=true;
        
	} else {
		fadeOut=true;
        setLED(freq, 3);
	}
	
	cout << "playing: " +msg.message +"@" + ofToString(track.currentItem,0) + " ("+ofToString(track.track.size()-1,0)+")" << endl;
	
	cout << "play freq: " + ofToString(freq) << endl;
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if(key =='p'){
        start();
        track.playItem(0);
    } else if( key == 's') {
        track.stop();
    } else if( key == 'a') {
        start();
    }
}
void testApp::exit(){
	setLED(100, 3);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	if(key==0){
        
    }
}

void testApp::mouseScroll(int device, int axis, int value){
    centralTone+=value;
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    /*
    cout << button << endl;
    if (button==0) {
       manual++;
    }
    if (button==2){
        manual--;
    }
    if(button==1){
        if(blinkMode==0) blinkMode=1;
        else blinkMode=0;
        
    }
    
    if (manual>freqs.length()-1) {
        manual=freqs.length()-1;
    }
    if(manual<=0){
        manual=0;
    }
    
    ofMessage msg(ofToString(freqs[manual]));
    ofSendMessage(msg);
     */
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}



//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}


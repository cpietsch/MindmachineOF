#include "testApp.h"



bool fadeOut=false;
bool fadeIn=false;
bool play=false;

float initVolume=0.35f;

ofxFenster* guiWin;
guiApp guiApp;

ofImage img1;

float rotation;

//--------------------------------------------------------------
void testApp::setup()
{		
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	// SOUND --------------------------------------------------------
	// 2 output channels,
	// 0 input channels
	// 22050 samples per second
	// 512 samples per buffer
	// 4 num buffers (latency)
	
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
	
	//soundStream.listDevices();
	
	//if you want to set the device id to be different than the default
	//soundStream.setDeviceID(1); 	//note some devices are input only and some are output only 
	
	soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
	
	//--------------------------------------------------------------
	//track.speed=10;
	frameChanged=false;
	
	img1.loadImage("image.png");
	rotation=0;
	
	// WINDOWS ---------
	guiApp.setup(this);
	guiWin=ofxFensterManager::get()->createFenster(500, 10,600, 600, OF_WINDOW);
	guiWin->addListener(&guiApp);
	/*
	 ofxDisplayList displays = ofxDisplayManager::get()->getDisplays();
	 ofxDisplay* disp = displays[0];
	 if(displays.size() > 1)
	 disp = displays[1];
	 ofxFensterManager::get()->setActiveDisplay(disp);
	 */
}


//--------------------------------------------------------------
void testApp::update(){

	track.update();
	guiApp.oscBrainmachineGui.update();
	
	if (frameChanged) {
		ofSetFrameRate((float)guiApp.binauralBeat*2);
		frameChanged=false;
	}
	
	if(fadeOut){
		if(volume<=0){
			fadeOut=false;
			volume=0;
			play=false;
			ofSetFrameRate(60);
		} else {
			volume-=0.01;
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
void testApp::drawNet(float size){
	float xFac=ofGetWidth()/size;
	float yFac=ofGetHeight()/size;
	
	ofSetColor(guiApp.a,guiApp.a,guiApp.a,5);
	
	for (int x=0; x<size; x++) {
		ofLine(x*xFac, 0, x*xFac, ofGetHeight());
		ofLine(0, x*yFac, ofGetWidth(), x*yFac);
	}
}	
//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0, 0, 0);
	ofPushStyle();
	ofEnableAlphaBlending();
	
	float factor = guiApp.binauralBeat / 10;

	
	if(!fadeOut && play){
		ofFill();
		ofColor(255,255,255,60);
		ofRect(0, 0, (ofGetWidth()/track.track.size())*track.currentItem, 40);
		
		ofSetColor(0, 0, 0);
		ofDrawBitmapString("PROGRESS", 10, 15);
		
		//ofDrawBitmapString(label, textPadding, 0);

		
		int mod = ofGetFrameNum();
		
		if (mod%2) {
			
			//ofSetColor(guiApp.r,guiApp.g*(1-factor),guiApp.b*factor*factor,guiApp.a);
//			ofRect(0, 100, ofGetWidth() , ofGetHeight());
//			

			ofSetColor(255, 255, 255);

			ofPushMatrix();
			ofTranslate(ofGetWidth()/2, ofGetWidth()/2, 0);
			rotation+=guiApp.binauralBeat;
			ofRotateZ(rotation);
			ofScale(2, 2, 0);
			img1.draw(ofGetWidth()/-2, ofGetWidth()/-2);
			
			
			ofPopMatrix();
			
		} else {
			ofSetColor(0,0,0);
			ofRect(0, 100, ofGetWidth() , ofGetHeight());	
			//drawNet(40-guiApp.binauralBeat);
		}
			
	}
	
	ofDisableAlphaBlending();
	ofPopStyle();
	
	
	
	guiApp.leftRight = "L(" + ofToString(targetFrequencyL, 2) + "hz) R(" + ofToString(targetFrequencyR, 2) + "hz)";
	guiApp.frameRate = "FPS: "+ofToString(ofGetFrameRate(), 4);
	
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
void testApp::keyPressed  (int key){
	if (key == '-' || key == '_' ){
		volume -= 0.05;
		volume = MAX(volume, 0);
	} else if (key == '+' || key == '=' ){
		volume += 0.05;
		volume = MIN(volume, 1);
	}
	
	if( key == 's' ){
		soundStream.start();
	}
	
	if( key == 'e' ){
		soundStream.stop();
	}
	if( key == ' ' ){
	 	frameChanged=true;
	}
	if( key == ',' ){
		//(float)guiApp.binauralBeat=(float)guiApp.binauralBeat-0.3;
		frameChanged=true;
	}
	if( key == '.' ){
		//(float)guiApp.binauralBeat=(float)guiApp.binauralBeat+0.3;
		frameChanged=true;
	}
	if(key=='f'){
		ofxFensterManager::get()->getPrimaryWindow()->toggleFullscreen();
	}
	
	cout << "key pressed: " << key << endl;
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	bNoise = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
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
			targetFrequencyL = (int)guiApp.centralTone-(float)guiApp.binauralBeat/2;
			phaseAdderTargetL = (targetFrequencyL / (float) sampleRate) * TWO_PI;
			
			targetFrequencyR = (int)guiApp.centralTone+(float)guiApp.binauralBeat/2;
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
	float freq=track.translateFreq(msg.message);
	if(freq!=0){
		guiApp.binauralBeat=freq;
		frameChanged=true;
	} else {
		fadeOut=true;
	}
	
	guiApp.currentItem = "playing: " +msg.message +"@" + ofToString(track.currentItem,0) + " ("+ofToString(track.track.size()-1,0)+")";
	
	cout << "play freq: " + ofToString(freq) << endl;
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}

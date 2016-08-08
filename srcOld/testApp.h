#pragma once
//https://github.com/LaughterOnWater/Arduino-Brain-Machine/blob/master/Arduino_Brain_Machine/Arduino_Brain_Machine.pde

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxGui.h"
#include "trackManager.h"
#include "ofxOsc.h"
#include "oscGui.h"


// listen on port 12345



class testApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void audioOut(float * input, int bufferSize, int nChannels);
	
	void startSequenz();
	void start();
	void stop();
	void drawNet(float size);
	
	
	ofSoundStream soundStream;
	
	float 	pan;
	int		sampleRate;
	bool 	bNoise;
	float 	volume;
	
	vector <float> lAudio;
	vector <float> rAudio;
	
	//------------------- for the simple sine wave synthesis
	float 	targetFrequencyL;
	float 	phaseL;
	float 	phaseAdderL;
	float 	phaseAdderTargetL;
	
	float 	targetFrequencyR;
	float 	phaseR;
	float 	phaseAdderR;
	float 	phaseAdderTargetR;
	
	bool frameChanged;
	
	trackManager track;
	
};


#include "guiApp.h"



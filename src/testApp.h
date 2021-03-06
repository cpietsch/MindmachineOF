#pragma once

#include "ofMain.h"
#include "trackManager.h"
#include "ofxManyMouse.h"
#include "ofxGui.h"

class ofStringLoggerChannel {
public:
    ofStringLoggerChannel::ofStringLoggerChannel(){
        
    }
};



class testApp : public ofBaseApp , public ofxManyMouse{
	
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
    void mouseScroll(int device, int axis, int value);
    void setLED(float freq, int alt);
    void audioOut(float * input, int bufferSize, int nChannels);
    void startSequenz();
	void start();
	void stop();
    void playButtonPressed();
    void stopButtonPressed();
    void loadButtonPressed();


    
    void exit();
    
    ofSoundStream soundStream;

		ofSerial	serial;
    
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
    float initVolume=0.35f;
    bool fadeOut=false;
    bool fadeIn=false;
    bool play=false;
    
    float binauralBeat;
    string freqs;
    int manual;
    int blinkMode;
    float freq;
    
    ofParameter<int> centralTone,trackNumber;
    ofxButton playButton,stopButton,loadButton;

    ofxPanel gui;
    

};


/*
 *  oscGui.h
 *  ofxFensterExample
 *
 *  Created by ich beobachte dich on 07.07.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
#include "ofUtils.h"

#define PORT 7000
#define NUM_MSG_STRINGS 200


class oscGui  {
	public:
	oscGui(){
		currentPos=0;
	};
	void setup(int _x, int _y, int _width, int _height){
		x=_x;
		y=_y;
		width=_width;
		height=_height;
		
		for (int i=0; i< NUM_MSG_STRINGS; i++) {
			braindata[currentPos] = ofVec2f(0,0);
		}
	};
	
	void draw(){
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(x, y, 0);
		ofSetColor(255,255,255,100);
		ofNoFill();
		ofRect(0, 0, width, height);
		
				
		for (float i=1; i < NUM_MSG_STRINGS; i++) {
			float xpos = (width / NUM_MSG_STRINGS) *i;
			float xposOld = (width / NUM_MSG_STRINGS) *(i-1);

			float attention = (height / 100) * braindata[(int) i].x;
			float attentionOld = (height / 100) * braindata[(int) i-1].x;
			float relax = (height / 100) * braindata[(int) i].y;
			float relaxOld = (height / 100) * braindata[(int) i-1].y;
			
			ofFill();
			ofSetColor(0,0,255,200);
			//ofRect(xpos, height-attention, 4, 4);
			ofLine(xposOld, height-attentionOld, xpos, height-attention);
			
			ofSetColor(0,255,0,200);
			ofFill();
			//ofRect(xpos, height-attention, 4, 4);
			ofLine(xposOld, height-relaxOld, xpos, height-relax);
			
			
		}
		
		
		ofPopMatrix();
		ofPopStyle();
	};
	
	void update(){
		while(receiver.hasWaitingMessages()){
			// get the next message
			ofxOscMessage m;
			receiver.getNextMessage(&m);
			
			// check for mouse moved message
			if(m.getAddress() == "/brain"){
				// both the arguments are int32's
//				cout << "attention:" << m.getArgAsDouble(0)
//				<< "- meditation:" << m.getArgAsDouble(1)
//				<< endl;
				
				//braindata[currentPos] = ofVec2f((float)m.getArgAsDouble(0),(float)m.getArgAsDouble(1));
				//currentPos = (currentPos + 1) % NUM_MSG_STRINGS;
			}
		}
		
		// testing
		
		braindata[currentPos] = ofVec2f(ofRandom(100.0f),ofRandom(100.0f));
		currentPos = (currentPos + 1) % NUM_MSG_STRINGS;
		//cout << currentPos << endl;
	};
	
	void mouseDragged(int x, int y, int button){
		
	}
	
	
	int x,y;
	int beta,aplha,theta,gamma,delta;
	//int numData=100;
	ofVec2f braindata[NUM_MSG_STRINGS];
	ofxOscReceiver receiver;
	int currentPos;
	int width,height;

};
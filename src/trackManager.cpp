/*
 *  trackManager.cpp
 *  ofxFensterExample
 *
 *  Created by ich beobachte dich on 07.07.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "trackManager.h"
#include "ofEvents.h"

trackManager::trackManager(){
	//generateMeditation();
	readXML();
	
	speed=1;
	bTimerReached=true;
}
void trackManager::stop(){
	bTimerReached=true;
	ofMessage msg(ofToString(0));
	ofSendMessage(msg);
}
void trackManager::playItem(int index){
	//cout << "play track" << index << endl;
	currentItem=index;
	bTimerReached = false;
    startTime = ofGetElapsedTimeMillis();  // get the start time
    endTime = track[index].time*1000/speed; // in milliseconds;
	
	ofMessage msg(ofToString(track[currentItem].frequency));
	ofSendMessage(msg);
}
void trackManager::update(){
	float timer = ofGetElapsedTimeMillis() - startTime;
    
    if(timer >= endTime && !bTimerReached) {
        bTimerReached = true; 
		
		currentItem++;
		if(currentItem<track.size()){
			playItem(currentItem);
		}		
    }
}

float trackManager::translateFreq(string name){
	float output=0;
	name=ofToLower(name);
	char freq=name[0];
	
	if(freq=='b') {
		output=14.4;
	} 
	else if(freq=='a') {
		output=11.1;
	} 
	else if(freq=='t') {
		output=6;
	} 
	else if (freq=='d') {
		output=2.2;
	}
	else if (freq=='g') {
		output=40.4;
	}
	
	return output;	
}

void trackManager::readXML(){
	ofxXmlSettings XML;
	XML.loadFile("track.xml");
	int numTracks = XML.getNumTags("Track:Phase");
	
	if(numTracks > 0){
		
		XML.pushTag("Track", numTracks-1);
		
		int numTrackItems = XML.getNumTags("Phase");
		
		if(numTrackItems > 0){
			
			for(int i = 0; i < numTrackItems; i++){
				string frequence = XML.getValue("Phase:Frequence", "b", i);
				int duration = XML.getValue("Phase:Duration", 0, i);
				
				char freq = frequence[0];
				
				cout << "added " << frequence << " : " << duration << endl; 
				track.push_back (trackItem ( freq, duration ));
			}
		}
		
		XML.popTag();
	}
		
}

void trackManager::generateMeditation(){
	
	track.push_back (trackItem ( 'b', 400000 ));
	//track.push_back (trackItem ( 'a', 100000 ));
//	track.push_back (trackItem ( 'b', 200000 ));
//	track.push_back (trackItem ( 'a', 150000 ));
//	track.push_back (trackItem ( 'b', 150000 ));
	//track.push_back (trackItem ( 'a', 200000 ));
	//track.push_back (trackItem ( 'b', 100000 ));
	track.push_back (trackItem ( 'a', 300000 ));
	track.push_back (trackItem ( 'b', 50000 ));
	track.push_back (trackItem ( 'a', 600000 ));
	track.push_back (trackItem ( 't', 100000 ));
	track.push_back (trackItem ( 'A', 300000 ));
	track.push_back (trackItem ( 't', 200000 ));
	track.push_back (trackItem ( 'a', 200000 ));
	track.push_back (trackItem ( 't', 300000 ));
	track.push_back (trackItem ( 'A', 150000 ));
	track.push_back (trackItem ( 't', 600000 ));
	track.push_back (trackItem ( 'a', 100000 ));
	track.push_back (trackItem ( 'b', 100000 ));
	track.push_back (trackItem ( 'a', 50000 ));
	track.push_back (trackItem ( 'T', 550000 ));
	track.push_back (trackItem ( 'd', 100000 ));
	track.push_back (trackItem ( 't', 450000 ));
	track.push_back (trackItem ( 'd', 50000 ));
	track.push_back (trackItem ( 'T', 350000 ));
	track.push_back (trackItem ( 'd', 100000 ));
	track.push_back (trackItem ( 't', 250000 ));
//	track.push_back (trackItem ( 'd', 150000 ));
//	track.push_back (trackItem ( 'g', 10000 ));
//	track.push_back (trackItem ( 'T', 50000 ));
//	track.push_back (trackItem ( 'g', 10000 ));
//	track.push_back (trackItem ( 'd', 300000 ));
//	track.push_back (trackItem ( 'g', 50000 ));
//	track.push_back (trackItem ( 'd', 600000 ));
//	track.push_back (trackItem ( 'g', 100000 ));
//	track.push_back (trackItem ( 'D', 300000 ));
//	track.push_back (trackItem ( 'g', 50000 ));
//	track.push_back (trackItem ( 'd', 150000 ));
//	track.push_back (trackItem ( 'g', 10000 ));
//	track.push_back (trackItem ( 't', 100000 ));
//	track.push_back (trackItem ( 'D', 100000 ));
//	track.push_back (trackItem ( 't', 200000 ));
//	track.push_back (trackItem ( 'a', 10000 ));
//	track.push_back (trackItem ( 'd', 100000 ));
//	track.push_back (trackItem ( 't', 300000 ));
	//track.push_back (trackItem ( 'a', 50000 ));
//	track.push_back (trackItem ( 'B', 10000 ));
//	track.push_back (trackItem ( 'a', 100000 ));
//	track.push_back (trackItem ( 't', 220000 ));
//	track.push_back (trackItem ( 'A', 150000 ));
//	track.push_back (trackItem ( 'b', 10000 ));
//	track.push_back (trackItem ( 'a', 300000 ));
//	track.push_back (trackItem ( 'b', 50000 ));
//	track.push_back (trackItem ( 'a', 200000 ));
//	track.push_back (trackItem ( 'B', 120000 ));
//	track.push_back (trackItem ( 'a', 150000 ));
//	track.push_back (trackItem ( 'b', 200000 ));
//	track.push_back (trackItem ( 'a', 100000 ));
//	track.push_back (trackItem ( 'b', 250000 ));
//	track.push_back (trackItem ( 'A', 50000 ));
//	track.push_back (trackItem ( 'b', 600000 ));
	track.push_back (trackItem ( '0', 0 ));
	
	cout << "generated meditation track with "+ofToString(track.size(), 2)+" items" << endl;
	
}

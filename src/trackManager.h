/*
 *  trackManager.h
 *  emptyExample
 *
 *  Created by ich beobachte dich on 07.07.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "trackItem.h"
#include "ofUtils.h"
#include "ofxXmlSettings.h"

class trackManager {
public:
	vector<trackItem> track;
	trackManager ();
	void generateMeditation ();
	void generateFreq ();
	void playItem(int);
	void update();
	void stop();
	void readXML();
	float translateFreq(string);
	
	float startTime; // store when we start time timer
	float endTime; // when do want to stop the timer
	bool  bTimerReached; // used as a trigger when we hit the timer
	int currentItem;
	int speed;
	
	
	
};

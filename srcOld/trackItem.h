#pragma once
/*
 *  track.h
 *  emptyExample
 *
 *  Created by ich beobachte dich on 07.07.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

class trackItem {
public:
	char frequency;
	int time;
	trackItem (char _frequency, int _time){
		frequency = _frequency;
		time = _time;
	}
};



class guiApp: public ofxFensterListener {
public:
	guiApp() {
	}
	void setup(testApp* _mainApp){
		
		mainApp = _mainApp;
		
		panelBrainmachine.setup("Brainmachine"); // most of the time you don't need a name
		panelBrainmachine.add(centralTone.setup( "CentralTone", 200, 100, 500 ));
		panelBrainmachine.add(binauralBeat.setup( "Binaural Beat", 10.0f, 0, 50 ));
		panelBrainmachine.add(frameRate.setup("FrameRate", ""));
		panelBrainmachine.add(leftRight.setup("LeftRight", ""));
		panelBrainmachine.add(runButton.setup("Go"));
		panelBrainmachine.add(quitButton.setup("Stop"));
		panelBrainmachine.add(r.setup( "R", 200, 0, 255 ));
		panelBrainmachine.add(g.setup( "G", 200, 0, 255 ));
		panelBrainmachine.add(b.setup( "B", 200, 0, 255 ));
		panelBrainmachine.add(a.setup( "A", 200, 0, 255 ));
		
		panelTrack.setup("Track","settings.xml",10,panelBrainmachine.getHeight()+50); 
		panelTrack.add(playButton.setup("Play Track"));
		panelTrack.add(stopButton.setup("Stop Track"));
		panelTrack.add(currentItem.setup("Current Track", ""));
		
		
		playButton.addListener(this,&guiApp::playButtonPressed);
		stopButton.addListener(this,&guiApp::stopButtonPressed);
		
		runButton.addListener(this,&guiApp::startButtonPressed);
		quitButton.addListener(this,&guiApp::quitButtonPressed);
		
		oscBrainmachineGui.setup(10,300,500,200);
		
		//binauralBeat.addListener(ofEvents.mouseReleased, this, &guiApp::changeFrameRate);


	}
	void exit(){
		playButton.removeListener(this,&guiApp::playButtonPressed);
		stopButton.removeListener(this,&guiApp::stopButtonPressed);
		
		//@todo: eventlistener einfügen
	}
	void playButtonPressed(bool & pressed){
		if(pressed) {
			mainApp->start();
			mainApp->track.playItem(0);
		}
	}
	void stopButtonPressed(bool & pressed){
		if(pressed) mainApp->track.stop();
	}
	void startButtonPressed(bool & pressed){
		if(pressed) mainApp->start();
	}
	void quitButtonPressed(bool & pressed){
		if(pressed) mainApp->stop();
	}
	void changeFrameRate(int & rate){
		
	}
	void draw() {
		panelBrainmachine.draw();
		panelTrack.draw();
		oscBrainmachineGui.draw();
		
		//ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("www.brainstatesharing.com", 10, 550);
		
	}
	void keyReleased(int key, ofxFenster* window) {
		if(key==' ')
			//ofxFensterManager::get()->deleteFenster(window);
			mainApp->frameChanged=true;
		if(key == 'm'){ //this is to test set and get window position
			ofPoint winPos = window->getWindowPosition();
			window->setWindowPosition(winPos.x + 10, winPos.y);
		}
	}
	
	//--------------------------------------------------------------
	void mouseMoved(int x, int y ){
		
	}
	
	//--------------------------------------------------------------
	void mouseDragged(int x, int y, int button){
		oscBrainmachineGui.mouseDragged(x,y,button);
	}
	
	//--------------------------------------------------------------
	void mousePressed(int x, int y, int button){
		
	}
	
	
	//--------------------------------------------------------------
	void mouseReleased(int x, int y, int button){
		cout << x << " " << y << endl;
	}
	
	
	ofxPanel panelBrainmachine, panelTrack, panelOsc;
	ofxFloatSlider binauralBeat;
	ofxIntSlider centralTone;
	ofxIntSlider r,g,b,a;

	ofxButton playButton, stopButton;
	ofxButton runButton,quitButton;
	ofxToggle filled;
	ofxLabel currentItem,frameRate,leftRight;
	
	testApp* mainApp;
	oscGui oscBrainmachineGui;
	
	
};
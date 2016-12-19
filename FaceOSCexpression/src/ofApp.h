#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "FaceOsc.h"
#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp, public FaceOsc {
public:
	void loadSettings();
	
	void setup();
	void update();
	void draw();
	//void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
	ExpressionClassifier classifier;
	
	/*
	void setVideoSource(bool useCamera);

	bool bUseCamera, bPaused;

	int camWidth, camHeight;
	int movieWidth, movieHeight;
	int sourceWidth, sourceHeight;

	ofVideoPlayer movie;
	ofBaseVideoDraws *videoSource;
    
	ofMatrix4x4 rotationMatrix;
	
	bool bDrawMesh;
    
    ofxPanel gui;
    bool bGuiVisible;*/
};

#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	
	tracker.setup();
	tracker.setRescale(.5);
	//loadSettings();
	/*
	ofXml xml;
	xml.setTo("osc");
	host = xml.getValue("host", "localhost");
	port = xml.getValue("port", 8338);*/
	osc.setup("localhost", 8338);
	
	classifier.load("expressions");
}

void ofApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		if(tracker.update(toCv(cam))) {
			unsigned int i = classifier.classify(tracker);
			string exp = classifier.getDescription(i);
			sendFaceOsc(tracker,exp);
			/*cout << exp;
			fflush(stdout);*/
		}		
	}
}

void ofApp::draw() {
	ofSetColor(255);
	cam.draw(0, 0);
	tracker.draw();
	
	int w = 100, h = 12;
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(5, 10);
	int n = classifier.size();
	int primary = classifier.getPrimaryExpression();
  for(int i = 0; i < n; i++){
		ofSetColor(i == primary ? ofColor::red : ofColor::black);
		ofDrawRectangle(0, 0, w * classifier.getProbability(i) + .5, h);
		ofSetColor(255);
		ofDrawBitmapString(classifier.getDescription(i), 5, 9);
		ofTranslate(0, h + 5);
  }
	ofPopMatrix();
	ofPopStyle();
	
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	ofDrawBitmapStringHighlight(
		string() +
		"r - reset\n" +
		"e - add expression\n" +
		"a - add sample\n" +
		"s - save expressions\n"
		"l - load expressions",
		14, ofGetHeight() - 7 * 12);
}
/*
void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
		classifier.reset();
	}
	if(key == 'e') {
		classifier.addExpression();
	}
	if(key == 'a') {
		classifier.addSample(tracker);
	}
	if(key == 's') {
		classifier.save("expressions");
	}
	if(key == 'l') {
		classifier.load("expressions");
	}
}*/
/*
void ofApp::loadSettings() {
    bGuiVisible = true;
    gui.setup();
    gui.setName("FaceOSC");
    gui.setPosition(0, 0);
    gui.add(bIncludePose.set("pose", true));
    gui.add(bIncludeGestures.set("gesture", true));
    gui.add(bIncludeAllVertices.set("raw", false));
    gui.add(bNormalizeRaw.set("normalize raw", false));
    
    // load settings file
	ofXml xml;
	if(!xml.load(ofToDataPath("settings.xml"))) {
		return;
	}
	
	// expects following tags to be wrapped by a main "faceosc" tag
	
	bool bUseCamera = true;

	xml.setTo("source");
	if(xml.exists("useCamera")) {
		bUseCamera = xml.getValue("useCamera", false);
	}
	xml.setToParent();

	xml.setTo("camera");
	if(xml.exists("device")) {
		cam.setDeviceID(xml.getValue("device", 0));
	}
	if(xml.exists("framerate")) {
		cam.setDesiredFrameRate(xml.getValue("framerate", 30));
	}
	camWidth = xml.getValue("width", 640);
	camHeight = xml.getValue("height", 480);
	cam.initGrabber(camWidth, camHeight);
	xml.setToParent();

	xml.setTo("movie");
	if(xml.exists("filename")) {
		string filename = ofToDataPath((string)xml.getValue("filename", ""));
		if(filename != "") {
			if(!movie.load(filename)) {
				ofLog(OF_LOG_ERROR, "Could not load movie \"%s\", reverting to camera input", filename.c_str());
				bUseCamera = true;
			}
			movie.play();
		}
	}
	else {
		ofLog(OF_LOG_ERROR, "Movie filename tag not set in settings, reverting to camera input");
		bUseCamera = true;
	}
	if(xml.exists("volume")) {
		float movieVolume = ofClamp(xml.getValue("volume", 1.0), 0, 1.0);
		movie.setVolume(movieVolume);
	}
	if(xml.exists("speed")) {
		float movieSpeed = ofClamp(xml.getValue("speed", 1.0), -16, 16);
		movie.setSpeed(movieSpeed);
	}
	bPaused = false;
	movieWidth = movie.getWidth();
	movieHeight = movie.getHeight();
	xml.setToParent();

	if(bUseCamera) {
		ofSetWindowShape(camWidth, camHeight);
		setVideoSource(true);
	}
	else {
		ofSetWindowShape(movieWidth, movieHeight);
		setVideoSource(false);
	}

	xml.setTo("face");
	if(xml.exists("rescale")) {
		tracker.setRescale(xml.getValue("rescale", 1.0));
	}
	if(xml.exists("iterations")) {
		tracker.setIterations(xml.getValue("iterations", 5));
	}
	if(xml.exists("clamp")) {
		tracker.setClamp(xml.getValue("clamp", 3.0));
	}
	if(xml.exists("tolerance")) {
		tracker.setTolerance(xml.getValue("tolerance", 0.01));
	}
	if(xml.exists("attempts")) {
		tracker.setAttempts(xml.getValue("attempts", 1));
	}
	bDrawMesh = true;
	if(xml.exists("drawMesh")) {
		bDrawMesh = (bool) xml.getValue("drawMesh", 1);
	}
	tracker.setup();
	xml.setToParent();

	xml.setTo("osc");
	host = xml.getValue("host", "localhost");
	port = xml.getValue("port", 8338);
	osc.setup(host, port);
	xml.setToParent();
	
	xml.clear();
}
*/

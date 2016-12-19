#include "FaceOsc.h"
#include <string> 

void FaceOsc::sendFaceOsc(ofxFaceTracker& tracker, string expression) {
    clearBundle();
    
    if(tracker.getFound())
    {
        addMessage("/found", 1);
		std::size_t found;
		found=expression.find("eyebrows");
		if (found!=std::string::npos)
        {
			        cout << expression;
			fflush(stdout);
            addMessage("/raisedeyebrows", true);
        }

        if (expression == "smile") 
        {
            addMessage("/smile",true);
        }
        if(expression == "neutral")
        {
			addMessage("/neutral", true);
		}

    } 
    else 
    {
        addMessage("/found", 0);
    }
    
    sendBundle();
}

void FaceOsc::clearBundle() {
	bundle.clear();
}

void FaceOsc::addMessage(string address, ofVec3f data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addFloatArg(data.x);
	msg.addFloatArg(data.y);
	msg.addFloatArg(data.z);
	bundle.addMessage(msg);
}

void FaceOsc::addMessage(string address, ofVec2f data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addFloatArg(data.x);
	msg.addFloatArg(data.y);
	bundle.addMessage(msg);
}

void FaceOsc::addMessage(string address, float data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addFloatArg(data);
	bundle.addMessage(msg);
}

void FaceOsc::addMessage(string address, int data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addIntArg(data);
	bundle.addMessage(msg);
}

void FaceOsc::sendBundle() {
	osc.sendBundle(bundle);
}

#include "ofApp.h"
#include "math.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Empfänger");
	//ofSetFrameRate(60); // run at 60 fps

	// listen on the given port
	ofLog() << "listening for osc messages on port " << PORT;
	receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){

	// check for waiting messages
	while(receiver.hasWaitingMessages()){

		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
		ofLog() << m.getAddress();

		// check for mouse moved message
		if(m.getAddress() == "/daumen"){

			// both the arguments are floats
			mouseXfD = m.getArgAsFloat(1);
			mouseYfD = m.getArgAsFloat(2);
			ofLog() << mouseXfD << " " << mouseYfD;
		}
		if(m.getAddress() == "/zeigefinger"){

			// both the arguments are floats
			mouseXfZ = m.getArgAsFloat(1);
			mouseYfZ = m.getArgAsFloat(2);
			ofLog() << mouseXfZ << " " << mouseYfZ;
		}
	}

	checkDistance();
}


bool ofApp::checkDistance() {
	float distance = sqrt((mouseXfZ - mouseXfD)*(mouseXfZ - mouseXfD) + (mouseYfZ - mouseYfD)*(mouseYfZ - mouseYfD));
	ofLog() << "Distance: " << distance;

	if (distance <= 30 && distance != 0){
		check = true;
		ofLog() << check;
		return check;
	}
	
	if (distance >= 40){
		check = false;
		ofLog() << check;
		return check;
	}

	else{
		ofLog() << check;
		return check;
	}
}




//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

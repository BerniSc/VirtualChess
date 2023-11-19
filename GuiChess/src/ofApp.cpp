#include "ofApp.h"

#define CHESS_BOARD_LENGTH 8
#define CHESS_BOARD_PLATE_DIMESION 64
#define CHESS_BOARD_PLATE_RADIUS 10
#define CHESS_BOARD_PLATE_DIMESION 64
#define CHESS_BOARD_PLATE_GAP 5
#define CHESS_BOARD_FOCUS_POINT_RADIUS 5
#define CHESS_LABEL_CORRECTION 3
#define CHESS_LABEL_FIRST_NUMBER_COLUMN_CORRECTION 5

//--------------------------------------------------------------
void ofApp::setup(){
	image.load("logo.png");
	font.load("arial.ttf", 10);
	// Removed "stream" parameter to ensure compatibility with Linux System
	chessWorkout.load("chess_workout.mp3");
	chessWorkout.setVolume(0.6);
	chessWorkout.setLoop(true);
	chessWorkout.play();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	//Chess Board
	ofTranslate(32, 32);

	ofSetColor(240);
	for (int i = 0; i < CHESS_BOARD_LENGTH; i++) {
		for (int j = 0; j < CHESS_BOARD_LENGTH; j++) {
			ofDrawRectRounded(
				i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * i,
				j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * j,
				CHESS_BOARD_PLATE_DIMESION,
				CHESS_BOARD_PLATE_DIMESION,
				CHESS_BOARD_PLATE_RADIUS);
		};
	};

	ofSetColor(41, 254, 47, 60);
	ofDrawRectRounded(
		0,
		0,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_RADIUS
	);
	ofSetColor(255, 67, 40, 60);
	ofDrawRectRounded(
		64 + 5,
		64 + 5,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_RADIUS
	);
	ofSetColor(255, 153, 40, 100);
	ofDrawRectRounded(
		128 + 10,
		128 + 10,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_RADIUS
	);

	ofSetColor(240);
	string chessAlphabet[8] = { "A", "B", "C", "D", "E", "F", "G", "H" };
	string chessNumbers[8] = { "1", "2", "3", "4", "5", "6", "7", "8" };
	for (int i = 0; i < CHESS_BOARD_LENGTH; i++) {
		font.drawString(chessAlphabet[i], i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_DIMESION / 2 + i * CHESS_BOARD_PLATE_GAP - CHESS_LABEL_CORRECTION,
			-CHESS_BOARD_PLATE_GAP);
	}

	for (int i = 0; i < CHESS_BOARD_LENGTH; i++) {
		font.drawString(chessAlphabet[i], i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_DIMESION / 2 + i * CHESS_BOARD_PLATE_GAP - CHESS_LABEL_CORRECTION,
			CHESS_BOARD_LENGTH * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_LENGTH * CHESS_BOARD_PLATE_GAP + CHESS_BOARD_PLATE_GAP + CHESS_LABEL_CORRECTION);
	}

	for (int j = 0; j < CHESS_BOARD_LENGTH; j++) {
		font.drawString(chessNumbers[j], -CHESS_BOARD_PLATE_GAP - CHESS_LABEL_FIRST_NUMBER_COLUMN_CORRECTION,
			j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_DIMESION / 2 + j * CHESS_BOARD_PLATE_GAP + CHESS_LABEL_CORRECTION);
	}

	for (int j = 0; j < CHESS_BOARD_LENGTH; j++) {
		font.drawString(chessNumbers[j], CHESS_BOARD_LENGTH * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_LENGTH * CHESS_BOARD_PLATE_GAP - CHESS_BOARD_PLATE_GAP + CHESS_LABEL_CORRECTION,
			j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_DIMESION / 2 + j * CHESS_BOARD_PLATE_GAP + CHESS_LABEL_CORRECTION);
	}

	ofSetColor(263, 47, 0);
	for (int i = 0; i < CHESS_BOARD_LENGTH; i++) {
		for (int j = 0; j < CHESS_BOARD_LENGTH; j++) {
			ofDrawCircle(
				i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * i + CHESS_BOARD_PLATE_DIMESION / 2,
				j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * j + CHESS_BOARD_PLATE_DIMESION / 2,
				CHESS_BOARD_FOCUS_POINT_RADIUS);
		};
	};



	//Image
	/*
	ofSetColor(200);
	image.draw(ofGetWidth() / 2 - image.getWidth() / 2, ofGetHeight() / 2 - image.getHeight() / 2 + 80);
	image.resize(250, 250);

	//Text
	ofSetColor(62, 255, 40);
	font.drawString("BernSoft AG\n  presents:", ofGetWidth() / 2 - 110, ofGetHeight() / 2 - 120);
	*/
	//Color
	/*
	ofSetColor(138, 255, 130, 60);
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 32);

	ofSetBackgroundColor(100, 160, 200);
	*/


	//OF-Translate
	/*
	ofTranslate(0, 0);
	ofDrawCircle(64, 64, 32);

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofDrawCircle(0, 0, 32);
	*/

	//3D-Shapes
	/*
	ofNoFill();

	ofDrawBox(64, 256, 0, 64, 64, 64);

	ofDrawCone(160, 256, 0, 32, 128);

	ofDrawCylinder(256, 256, 32, 128);

	ofDrawIcoSphere(352, 256, 0, 32);

	ofDrawPlane(448, 256, 64, 64);

	ofDrawSphere(544, 256, 32);
	*/


	//2D-Shapes 
	/*
	ofNoFill();

	ofDrawRectangle(64, 64, 64, 64);

	ofDrawCircle(192, 96, 32);

	ofDrawLine(256, 64, 320, 128);

	ofDrawTriangle(352, 128, 384, 64, 416, 128);

	ofDrawEllipse(512, 96, 128, 64);

	ofFill();

	ofDrawRectRounded(608, 64, 64, 64, 9);

	ofNoFill();

	ofDrawBezier(704, 64, 736, 128, 768, 160, 800, 64);*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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

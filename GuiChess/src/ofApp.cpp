#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	image.load("logo.png");
	font.load("arial.ttf", 10);
	// Removed "stream" parameter to ensure compatibility with Linux System
	//chessWorkout.load("chess_workout.mp3");
	//chessWorkout.setVolume(0.6);
	//chessWorkout.setLoop(true);
	//chessWorkout.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	this->windowHeight = ofGetHeight();
	this->windowWidth = ofGetWidth();

	//std::cout << windowHeight << "		" << windowWidth << std::endl;

	//std::cout << scalingFactorTile << "		" << std::endl;
	//std::cout << "Chess Square Dimension: " << chessSquareDimension << std::endl;

	// Scale acording to the SMAAAALLLLER Side of the Window, as it is more important to get the Image to fit
	int min = std::min(windowHeight, windowWidth);

	// Calculate the ScalingFactor
	this->scalingFactorTile = float(min) / float(minimalWindowSize);

	// Cap the Value so no State smaller than the Default State is possible
	this->scalingFactorTile = scalingFactorTile <= 1.0 ? 1.0 : scalingFactorTile;

	this->CHESS_BOARD_PLATE_DIMESION = this->start_CHESS_BOARD_PLATE_DIMESION * this->scalingFactorTile;
	this->CHESS_BOARD_PLATE_GAP = this->start_CHESS_BOARD_PLATE_GAP * this->scalingFactorTile;
	this->CHESS_BOARD_FOCUS_POINT_RADIUS = this->start_CHESS_BOARD_FOCUS_POINT_RADIUS * this->scalingFactorTile;

	chessSquareDimension = CHESS_BOARD_PLATE_DIMESION * CHESS_BOARD_LENGTH + CHESS_BOARD_PLATE_GAP * 7;
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//Displaying th GUI of the Chess Game

	//Setting spacer frame
	ofTranslate(32, 32);

	//Draw ChessBoard
	drawChessBoardTiles();

	//Draw overlay for possibilities to move
	drawHelpfulOverlay();

	//Draw coordinates labeling
	drawCoordinatesLabeling();

	//Draw red doits 
	drawRedDoits();

	//Draw current indicator
	drawIndicator();

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
void ofApp::drawChessBoardTiles() {
	//Function for drawing the ChessBoard(-Overlay)
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
}

//--------------------------------------------------------------
void ofApp::drawHelpfulOverlay() {

	//Coordiantes (x,y) (left upper corner => (0,0))
	int k1[2] = { 0,0 };
	int k2[2] = { 1,1 };
	int k3[2] = { 2,4 };
	//Function for drawing the ChessBoard(-Overlay)
	
	//Overlay for possibilities to move
	ofSetColor(41, 254, 47, 60);
	ofDrawRectRounded(
		k1[0] * CHESS_BOARD_PLATE_DIMESION + k1[0] * CHESS_BOARD_PLATE_GAP,
		k1[1] * CHESS_BOARD_PLATE_DIMESION + k1[1] * CHESS_BOARD_PLATE_GAP,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_RADIUS
	);

	//Overlay for moves that are blocked
	ofSetColor(255, 67, 40, 60);
	ofDrawRectRounded(
		k2[0] * CHESS_BOARD_PLATE_DIMESION + k2[0] * CHESS_BOARD_PLATE_GAP,
		k2[1] * CHESS_BOARD_PLATE_DIMESION + k2[1] * CHESS_BOARD_PLATE_GAP,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_RADIUS
	);

	//Overlay for possibilities to capture a figure
	ofSetColor(255, 153, 40, 100);
	ofDrawRectRounded(
		k3[0] * CHESS_BOARD_PLATE_DIMESION + k3[0] * CHESS_BOARD_PLATE_GAP,
		k3[1] * CHESS_BOARD_PLATE_DIMESION + k3[1] * CHESS_BOARD_PLATE_GAP,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_RADIUS
	);
}

//--------------------------------------------------------------
void ofApp::drawCoordinatesLabeling() {

	// Drawing Labeling for Chess Coordinates

	// alphabet mirrored
	ofSetColor(240);
	for (int i = 0; i < CHESS_BOARD_LENGTH; i++) {
		// Draw Text mirrored
		ofPushMatrix();
		ofScale(1, -1);  // Mirror in the horizontal direction
		font.drawString(chessAlphabet[i], i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_DIMESION / 2 + i * CHESS_BOARD_PLATE_GAP - CHESS_LABEL_CORRECTION,
			+ 3 * CHESS_BOARD_PLATE_GAP);
		ofPopMatrix();
	}

	// alphabet
	for (int i = 0; i < CHESS_BOARD_LENGTH; i++) {
		font.drawString(chessAlphabet[i], i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_DIMESION / 2 + i * CHESS_BOARD_PLATE_GAP - CHESS_LABEL_CORRECTION,
			CHESS_BOARD_LENGTH * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_LENGTH * CHESS_BOARD_PLATE_GAP + CHESS_BOARD_PLATE_GAP + CHESS_LABEL_CORRECTION);
	}

	// text
	for (int j = 0; j < CHESS_BOARD_LENGTH; j++) {
		font.drawString(chessNumbers[7 - j], -CHESS_BOARD_PLATE_GAP - CHESS_LABEL_FIRST_NUMBER_COLUMN_CORRECTION,
			j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_DIMESION / 2 + j * CHESS_BOARD_PLATE_GAP + CHESS_LABEL_CORRECTION);
	}

	// text mirrored
	for (int j = 0; j < CHESS_BOARD_LENGTH; j++) {
		// Draw Text mirrored
		ofPushMatrix();
		ofScale(1, -1);  // Mirror in the horizontal direction
		font.drawString(chessNumbers[j], CHESS_BOARD_LENGTH * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_LENGTH * CHESS_BOARD_PLATE_GAP - CHESS_BOARD_PLATE_GAP + CHESS_LABEL_CORRECTION,
			j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_DIMESION / 2 + j * CHESS_BOARD_PLATE_GAP + CHESS_LABEL_CORRECTION - 8.5 * CHESS_BOARD_PLATE_DIMESION);
		ofPopMatrix();
	}
	
}

//--------------------------------------------------------------
void ofApp::drawRedDoits() {

	// Drawing red doits for calibration
	ofSetColor(263, 47, 0);

	ofDrawCircle(
		0,
		0,
		CHESS_BOARD_FOCUS_POINT_RADIUS);
	ofDrawCircle(
		CHESS_BOARD_PLATE_DIMESION * CHESS_BOARD_LENGTH + CHESS_BOARD_PLATE_GAP * 7,
		0,
		CHESS_BOARD_FOCUS_POINT_RADIUS);
	ofDrawCircle(
		0,
		CHESS_BOARD_PLATE_DIMESION * CHESS_BOARD_LENGTH + CHESS_BOARD_PLATE_GAP * 7,
		CHESS_BOARD_FOCUS_POINT_RADIUS);
}

//--------------------------------------------------------------
void ofApp::drawIndicator() {

	if (indicatorPressed) {      //Input from Camara-Detection

		ofSetColor(105, 3, 107);

		calculateIndicatorFixCoordinates();

		ofDrawCircle(
			indicatorCoordinaters[0] * ( CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP ) + CHESS_BOARD_PLATE_DIMESION / 2,
			indicatorCoordinaters[1] * ( CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP ) + CHESS_BOARD_PLATE_DIMESION / 2,
			CHESS_BOARD_FOCUS_POINT_RADIUS);
	}
	else {
		ofSetColor(120, 120, 120);

		calculateIndicatorFlexCoordinates();

		ofDrawCircle(
			indicatorPixels[0],
			indicatorPixels[1],
			CHESS_BOARD_FOCUS_POINT_RADIUS);
	}
}

//--------------------------------------------------------------
void ofApp::calculateIndicatorFixCoordinates(){

	//Conversion from Camera to GUI
	float plateDivision = maxCameraDimension / CHESS_BOARD_LENGTH;

	this->indicatorCoordinaters[0] = floor(xCamera / plateDivision);
	this->indicatorCoordinaters[1] = floor(yCamera / plateDivision);

}

//--------------------------------------------------------------
void ofApp::calculateIndicatorFlexCoordinates() {

	//Conversion from Camera pixels to GUI pixels
	this->indicatorPixels[0] = ( xCamera * chessSquareDimension) / maxCameraDimension;
	this->indicatorPixels[1] = ( yCamera * chessSquareDimension) / maxCameraDimension;

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
	if (w < 616 || h < 616) {
		ofSetWindowShape(616, 616);
	}
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

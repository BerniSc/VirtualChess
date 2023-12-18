#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("VirtualChess");
	image.load("logo.png");

	// Load images for chess figures

	// Black pieces
	rook.load("rook.png");
	knight.load("knight.png");
	bishop.load("bishop.png");
	queen.load("queen.png");
	king.load("king.png");
	pawn.load("pawn.png");

	// White pieces
	ROOK.load("ROOK_W.png");
	KNIGHT.load("KNIGHT_W.png");
	BISHOP.load("BISHOP_W.png");
	QUEEN.load("QUEEN_W.png");
	KING.load("KING_W.png");
	PAWN.load("PAWN_W.png");

	font.load("arial.ttf", 10);
	// Removed "stream" parameter to ensure compatibility with Linux System
	//chessWorkout.load("chess_workout.mp3");
	//chessWorkout.setVolume(0.6);
	//chessWorkout.setLoop(true);
	//chessWorkout.play();

	VCEngine.reset();
	VCEngine.loadFEN("r3k2r/pppppppp/8/8/4q3/8/PPPPPPPP/R3K2R w KQkq - 0 1");
	VCEngine.reset();
	writeBoardInternaly(VCEngine.getCurrentBoard());

	receiver.setup(PORT);
	ofSetFrameRate(60); // run at 60 fps
}

//--------------------------------------------------------------
void ofApp::update(){
	
	// Receiver loop
	while(receiver.hasWaitingMessages()){

		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
		//ofLog() << m.getAddress();

		// check for mouse moved message
		if(m.getAddress() == "/daumen"){

			// both the arguments are floats
			XfThumb = m.getArgAsFloat(1);
			YfThumb = m.getArgAsFloat(2);
			//ofLog() << XfThumb << " " << YfIndex;
		}
		if(m.getAddress() == "/zeigefinger"){

			// both the arguments are floats
			XfIndex = m.getArgAsFloat(1);
			YfIndex= m.getArgAsFloat(2);
			//ofLog() << XfIndex << " " << YfIndex;
		}
	}

	// Camera data process
	checkDistance();
}

//--------------------------------------------------------------
void ofApp::draw(){


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
	
	//Displaying th GUI of the Chess Game

	//Setting spacer frame
	ofTranslate(32, 32);

	//Draw ChessBoard
	drawChessBoardTiles();

	//Draw chess figures
	drawChessFigures();

	//Draw overlay for possibilities to move
	// drawHelpfulOverlay();

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
void ofApp::drawChessFigures() {
	ofSetColor(240);
	//Function for drawing the Chess Figures
	for (int i = 0; i < CHESS_BOARD_LENGTH; i++) {
		for (int j = 0; j < CHESS_BOARD_LENGTH; j++) {

			// Switching between figures
			switch (arrayBoard[i][j]) {
				// black figures
				case 'r':
					rook.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
								j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					rook.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				case 'n':
					knight.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					knight.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				case 'b':
					bishop.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					bishop.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				case 'q':
					queen.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					queen.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				case 'k':
					king.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					king.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				case 'p':
					pawn.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					pawn.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				
				// white figures
				case 'R':
					ROOK.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					ROOK.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				case 'N':
					KNIGHT.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					KNIGHT.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				case 'B':
					BISHOP.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					BISHOP.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				case 'Q':
					QUEEN.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					QUEEN.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				case 'K':
					KING.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					KING.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
				case 'P':
					PAWN.draw(i * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (i + 1),
						j * CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP * (j + 1));
					PAWN.resize(CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP, CHESS_BOARD_PLATE_DIMESION - 2 * CHESS_BOARD_PLATE_GAP);
					break;
			}

		};
	};
}

//--------------------------------------------------------------
void ofApp::drawHelpfulOverlay(int posX, int posY, bool isCapture) {
	//Overlay for possibilities to move
	if(!isCapture)
		ofSetColor(41, 254, 47, 60);
	else
		ofSetColor(255, 67, 40, 60);

	ofDrawRectRounded(
		posX * CHESS_BOARD_PLATE_DIMESION + posX * CHESS_BOARD_PLATE_GAP,
		posY * CHESS_BOARD_PLATE_DIMESION + posY * CHESS_BOARD_PLATE_GAP,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_DIMESION,
		CHESS_BOARD_PLATE_RADIUS
	);

	/*
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
	*/
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

		try {
			engine::ChessTile src(indicatorCoordinaters[0], indicatorCoordinaters[1]);
			std::vector<engine::ChessTile> possibleTiles= VCEngine.getPossibleMoves(src);

			if(possibleTiles.size() != 0) {
				this->pickedSuccesfully = true;
				this->succesfullyPickedTile = src;
				for(auto& tile : possibleTiles) {
					std::pair<int, int> pos = tile.getArrayNr();
					drawHelpfulOverlay(pos.first, pos.second, tile.getIsCaptureMove());
				}
			}
		} catch(std::runtime_error& ex) {
			// A tile has been picked, that does not contain a Figure
		}

		ofDrawCircle(
			indicatorCoordinaters[0] * ( CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP ) + CHESS_BOARD_PLATE_DIMESION / 2,
			indicatorCoordinaters[1] * ( CHESS_BOARD_PLATE_DIMESION + CHESS_BOARD_PLATE_GAP ) + CHESS_BOARD_PLATE_DIMESION / 2,
			CHESS_BOARD_FOCUS_POINT_RADIUS);
	
	}else{
		if(this->pickedSuccesfully) {
			VCEngine.tryMove(this->succesfullyPickedTile, engine::ChessTile(indicatorCoordinaters[0], indicatorCoordinaters[1]));
			this->pickedSuccesfully = false;
			writeBoardInternaly(VCEngine.getCurrentBoard());
		}
	}
		ofSetColor(120, 120, 120);

		calculateIndicatorFlexCoordinates();

		ofDrawCircle(
			indicatorPixels[0],
			indicatorPixels[1],
			CHESS_BOARD_FOCUS_POINT_RADIUS);
	
}

//--------------------------------------------------------------
void ofApp::calculateIndicatorFixCoordinates(){

	//Conversion from Camera to GUI
	float plateDivision = maxCameraDimension / CHESS_BOARD_LENGTH;

	this->indicatorCoordinaters[0] = floor(xIndicator / plateDivision);
	this->indicatorCoordinaters[1] = floor(yIndicator / plateDivision);

}

//--------------------------------------------------------------
void ofApp::calculateIndicatorFlexCoordinates() {

	//Conversion from Camera pixels to GUI pixels
	this->indicatorPixels[0] = ( xIndicator * chessSquareDimension) / maxCameraDimension;
	this->indicatorPixels[1] = ( yIndicator* chessSquareDimension) / maxCameraDimension;

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

//--------------------------------------------------------------
bool ofApp::checkDistance() {
	float distance = sqrt((XfIndex - XfThumb)*(XfIndex - XfThumb) + (YfIndex - YfThumb)*(YfThumb - YfThumb));
	// ofLog() << "Distance: " << distance;

	xIndicator = (XfIndex + XfThumb)/2.;
	yIndicator = (YfIndex + YfThumb)/2.;

	//ofLog() << "xIndicator: " << xIndicator << "  ;  yIndicator: " << yIndicator;

	// 30
	if(distance <= 15 && distance != 0){
		indicatorPressed = true;
		//ofLog() << indicatorPressed;
		return indicatorPressed;
	}
	
	// 40
	if(distance >= 30){
		indicatorPressed = false;
		//ofLog() << indicatorPressed;
		return indicatorPressed;
	} else{
		//ofLog() << indicatorPressed;
		return indicatorPressed;
	}
}

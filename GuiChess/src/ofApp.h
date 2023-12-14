#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include <algorithm>

// listening port
#define PORT 5005

// max number of strings to display
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{
	private:

		//Constants for the chess board
		const int minimalWindowSize = 616;
		const int CHESS_BOARD_LENGTH = 8;
		const int fontWidth = 8;
		const int CHESS_BOARD_PLATE_RADIUS = 10;
		const int CHESS_LABEL_CORRECTION = 3;
		const int CHESS_LABEL_FIRST_NUMBER_COLUMN_CORRECTION = 5;

		//Vaiable dimension for scaling from window size
		int CHESS_BOARD_PLATE_DIMESION = 64;
		const int start_CHESS_BOARD_PLATE_DIMESION = this->CHESS_BOARD_PLATE_DIMESION;

		int CHESS_BOARD_PLATE_GAP = 5;
		const int start_CHESS_BOARD_PLATE_GAP = this->CHESS_BOARD_PLATE_GAP;

		int CHESS_BOARD_FOCUS_POINT_RADIUS = 5;
		const int start_CHESS_BOARD_FOCUS_POINT_RADIUS = this->CHESS_BOARD_FOCUS_POINT_RADIUS;

		// Scaling
		int windowHeight, windowWidth;

		float scalingFactorTile = 1.0f;

		float chessSquareDimension = 1.0f;

		// Chess Figures
		char arrayBoard[8][8] = { {'r', 'p', ' ', ' ', ' ', ' ', 'P', 'R'},
								  {'n', ' ', ' ', 'p', ' ', ' ', 'P', 'N'},
								  {'b', 'p', ' ', ' ', ' ', ' ', 'P', 'B'},
								  {'q', 'p', ' ', ' ', ' ', ' ', 'P', 'Q'},
								  {'k', 'p', ' ', ' ', ' ', ' ', 'P', 'K'},
								  {'b', 'p', ' ', ' ', ' ', 'P', ' ', 'B'},
								  {'n', 'p', ' ', ' ', ' ', ' ', 'P', 'N'},
								  {'r', 'p', ' ', ' ', ' ', ' ', 'P', 'R'} };

		// Input from Camara-Detection
		float maxCameraDimension = 400;
		float xIndicator = 55;
		float yIndicator = 20;
		bool indicatorPressed = false;

		// Varaibles from Osc
		int currentMsgString;
		string msgStrings[NUM_MSG_STRINGS];

		float XfThumb = 0;
		float YfThumb = 0;
		float XfIndex = 0;
		float YfIndex = 0;

		//Test Variables
		int indicatorCoordinaters[2] = { 0,0 };
		float indicatorPixels[2] = { 0.,0. };

		// Chess Label Coordinates
		string chessAlphabet[8] = { "A", "B", "C", "D", "E", "F", "G", "H" };
		string chessNumbers[8] = { "1", "2", "3", "4", "5", "6", "7", "8" };


		// Importing files from bin/data
		ofImage image;
		
		//Images for chess figures

		// black pieces
		ofImage rook;
		ofImage knight;
		ofImage bishop;
		ofImage queen;
		ofImage king;
		ofImage pawn;

		// black pieces
		ofImage ROOK;
		ofImage KNIGHT;
		ofImage BISHOP;
		ofImage QUEEN;
		ofImage KING;
		ofImage PAWN;

		ofTrueTypeFont font;

		ofSoundPlayer chessWorkout;
		

	public:
		void setup();
		void update();
		void draw();

		// Drawing parts of the chess board
		void drawChessBoardTiles();
		void drawChessFigures();
		void drawHelpfulOverlay();
		void drawCoordinatesLabeling();
		void drawRedDoits();
		void drawIndicator();

		// Calculation from camera to gui
		void calculateIndicatorFixCoordinates();
		void calculateIndicatorFlexCoordinates();

		// Process camera input
		bool checkDistance();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxOscReceiver receiver;
};

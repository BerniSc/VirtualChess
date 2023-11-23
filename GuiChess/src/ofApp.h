#pragma once

#include "ofMain.h"

#include <algorithm>

class ofApp : public ofBaseApp{
	private:
		int windowHeight, windowWidth;

		const int minimalWindowSize = 616;

		const int CHESS_BOARD_LENGTH = 8;

		const int fontWidth = 8;

		int CHESS_BOARD_PLATE_DIMESION = 64;
		const int start_CHESS_BOARD_PLATE_DIMESION = this->CHESS_BOARD_PLATE_DIMESION;
		const int CHESS_BOARD_PLATE_RADIUS = 10;
		int CHESS_BOARD_PLATE_GAP = 5;
		const int start_CHESS_BOARD_PLATE_GAP = this->CHESS_BOARD_PLATE_GAP;
		const int CHESS_BOARD_FOCUS_POINT_RADIUS = 5;
		const int CHESS_LABEL_CORRECTION  = 3;
		const int CHESS_LABEL_FIRST_NUMBER_COLUMN_CORRECTION = 5;

		float scalingFactorTile = 1.0f;


		ofImage image;

		ofTrueTypeFont font;

		ofSoundPlayer chessWorkout;
		

	public:
		void setup();
		void update();
		void draw();

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

};

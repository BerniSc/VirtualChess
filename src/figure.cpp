#include "figure.hpp"

#include <iostream>

engine::Figure::~Figure() {

}

std::vector<engine::ChessTile> King::getPossibleMoves(char const board[8][8]) {

}

Pawn::Pawn(engine::ChessTile tile, char figure) {
    this->position = tile;
    this->identifier = figure;
}

std::vector<engine::ChessTile> Pawn::getPossibleMoves(char const board[8][8]) {
    std::vector<engine::ChessTile> moves;
    std::pair<int, int> curPos = this->position.getArrayNr();

    // Determine the direction based on the pawn's color
    int direction = (isupper(board[curPos.first][curPos.second])) ? -1 : 1;

    // Move one square forward if the destination square is empty
    if(curPos.second + direction >= 0 && curPos.second + direction < 8 && 
       board[curPos.first][curPos.second + direction] == 0) {
        
        moves.push_back(engine::ChessTile(curPos.first, curPos.second + direction));
    }

    // Add optional double move if the pawn is in its starting position
    if(((islower(board[curPos.first][curPos.second]) && curPos.second == 1) || (isupper(board[curPos.first][curPos.second]) && curPos.second == 6)) &&
       board[curPos.first][curPos.second + direction] == 0) {
        
        moves.push_back(engine::ChessTile(curPos.first, curPos.second + 2 * direction));
    }

    // Add possible captures if the destination squares are not empty and have a piece with complementary direction
    int leftCaptureX = curPos.first - 1;
    int rightCaptureX = curPos.first + 1;

    // Only capture to the left, if there is space to the left and the Tile is occupied and the occuping piece is of complementary colour
    if(leftCaptureX >= 0 && board[leftCaptureX][curPos.second + direction] != 0 &&
        ((isupper(board[curPos.first][curPos.second]) && islower(board[leftCaptureX][curPos.second + direction])) ||
         (islower(board[curPos.first][curPos.second]) && isupper(board[leftCaptureX][curPos.second + direction])))) {
        moves.push_back(engine::ChessTile(leftCaptureX, curPos.second + direction));
    }
    
    // Only capture to the right, if there is space to the right and the Tile is occupied and the occuping piece is of complementary colour
    if(rightCaptureX < 8 && board[rightCaptureX][curPos.second + direction] != 0 &&
        ((isupper(board[curPos.first][curPos.second]) && islower(board[rightCaptureX][curPos.second + direction])) ||
         (islower(board[curPos.first][curPos.second]) && isupper(board[rightCaptureX][curPos.second + direction])))) {
        moves.push_back(engine::ChessTile(rightCaptureX, curPos.second + direction));
    }

    return moves;
}

Rook::Rook(engine::ChessTile tile, char figure) {
    this->position = tile;
    this->identifier = figure;
}

std::vector<engine::ChessTile> Rook::getPossibleMoves(const char board[8][8]) {
    std::vector<engine::ChessTile> moves;
    std::pair<int, int> curPos = position.getArrayNr();

    // Check possible moves to the right
    for(int i = curPos.first + 1; i < 8; i++) {
        if(board[i][curPos.second] == 0)
            moves.push_back(engine::ChessTile(i, curPos.second));
        
        else if((isupper(identifier) && islower(board[i][curPos.second])) ||
                (islower(identifier) && isupper(board[i][curPos.second]))) {
            moves.push_back(engine::ChessTile(i, curPos.second));
            break;
        } else {
            break;
        }
    }

    // Check possible moves to the left
    for(int i = curPos.first - 1; i >= 0; i--) {
        if(board[i][curPos.second] == 0)
            moves.push_back(engine::ChessTile(i, curPos.second));
        else if((isupper(identifier) && islower(board[i][curPos.second])) ||
                (islower(identifier) && isupper(board[i][curPos.second]))) {
            moves.push_back(engine::ChessTile(i, curPos.second));
            break;
        } else {
            break;
        }
    }

    // Check possible moves upwards
    for(int j = curPos.second + 1; j < 8; j++) {
        if(board[curPos.first][j] == 0)
            moves.push_back(engine::ChessTile(curPos.first, j));
        else if((isupper(identifier) && islower(board[curPos.first][j])) ||
                (islower(identifier) && isupper(board[curPos.first][j]))) {
            moves.push_back(engine::ChessTile(curPos.first, j));
            break;
        } else {
            break;
        }
    }

    // Check possible moves downwards
    std::cout << "x: " << curPos.second << "\n";
    for(int j = curPos.second - 1; j >= 0; j--) {
        if(board[curPos.first][j] == 0) {
            moves.push_back(engine::ChessTile(curPos.first, j));
        } else if((isupper(identifier) && islower(board[curPos.first][j])) ||
                  (islower(identifier) && isupper(board[curPos.first][j]))) {
            moves.push_back(engine::ChessTile(curPos.first, j));
            break;
        } else {
            break;
        }
    }

    return moves;
}

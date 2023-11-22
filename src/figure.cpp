#include "figure.hpp"

std::vector<engine::ChessTile> King::getPossibleMoves(char const board[8][8]) {

}
void King::move(){
    
}

std::vector<engine::ChessTile> Pawn::getPossibleMoves(char const board[8][8]) {
    std::vector<engine::ChessTile> moves;
    std::pair<int, int> curPos = this->position.getArrayNr();

    // Determine the direction based on the pawn's color
    int direction = (isupper(board[curPos.first][curPos.second])) ? 1 : -1;

    // Move one square forward if the destination square is empty
    if(curPos.second + direction >= 0 && curPos.second + direction < 8 && 
       board[curPos.first][curPos.second + direction] != 0) {
        
        moves.push_back(engine::ChessTile(curPos.first, curPos.second + direction));
    }

    // Add optional double move if the pawn is in its starting position
    if(((isupper(board[curPos.first][curPos.second]) && curPos.first == 1) || (!isupper(board[curPos.first][curPos.second]) && curPos.second == 6)) &&
       board[curPos.first][curPos.second + direction] != 0) {
        
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

void Pawn::move(){
    
}
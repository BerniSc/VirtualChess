#include "figure.hpp"

#include <iostream>

engine::Figure::~Figure() {

}

std::vector<engine::ChessTile> King::getPossibleMoves(char const board[8][8]) {
    std::vector<engine::ChessTile> moves;
    std::pair<int, int> curPos = position.getArrayNr();

    return moves;
}

/**
 * Pawn Section
*/
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
        moves.push_back(engine::ChessTile(leftCaptureX, curPos.second + direction, true));
    }
    
    // Only capture to the right, if there is space to the right and the Tile is occupied and the occuping piece is of complementary colour
    if(rightCaptureX < 8 && board[rightCaptureX][curPos.second + direction] != 0 &&
        ((isupper(board[curPos.first][curPos.second]) && islower(board[rightCaptureX][curPos.second + direction])) ||
         (islower(board[curPos.first][curPos.second]) && isupper(board[rightCaptureX][curPos.second + direction])))) {
        moves.push_back(engine::ChessTile(rightCaptureX, curPos.second + direction, true));
    }

    return moves;
}

/**
 * Queen Section
*/
Queen::Queen(engine::ChessTile tile, char figure) {
    this->position = tile;
    this->identifier = figure;
}

std::vector<engine::ChessTile> Queen::getPossibleMoves(const char board[8][8]) {
    std::vector<engine::ChessTile> moves;
    std::pair<int, int> curPos = position.getArrayNr();

    // Passing Identifier that does not match the class it is passed to is okay, as it only checks for Upper/Lowercase -> TODO Check anyhow
    Rook referenceMoverRook(this->position, this->identifier);
    Bishop referenceMoverBishop(this->position, this->identifier);

    std::vector<engine::ChessTile> tmp;
    // Get Rook Moves and add them to Queen Vector
    tmp = referenceMoverRook.getPossibleMoves(board);
    moves.insert(moves.end(), tmp.begin(), tmp.end());
    // Get Bishop Moves and add them to Queen Vector
    tmp = referenceMoverBishop.getPossibleMoves(board);
    moves.insert(moves.end(), tmp.begin(), tmp.end());

    return moves;
}

/**
 * Bishop Section
*/
Bishop::Bishop(engine::ChessTile tile, char figure) {
    this->position = tile;
    this->identifier = figure;
}

std::vector<engine::ChessTile> Bishop::getPossibleMoves(const char board[8][8]) {
    std::vector<engine::ChessTile> moves;
    std::pair<int, int> curPos = position.getArrayNr();

    int x, y;

    // Check possible moves to the upper right -> MemSafe as for Loop won't start if out of bounds 
    y = curPos.second + 1;
    for(int x = curPos.first + 1; (x < 8 && y < 8); x++) {
        if(board[x][y] == 0) {
            moves.push_back(engine::ChessTile(x, y));
        } else if((isupper(identifier) && islower(board[x][y])) ||
                  (islower(identifier) && isupper(board[x][y]))) {
            moves.push_back(engine::ChessTile(x, y, true));
            break;
        } else {
            break;
        }
        y++;
    }

    // Check possible moves to the upper left -> MemSafe as for Loop won't start if out of bounds 
    y = curPos.second + 1;
    for(int x = curPos.first - 1; (x >= 0 && y < 8); x--) {
        if(board[x][y] == 0) {
            moves.push_back(engine::ChessTile(x, y));
        } else if((isupper(identifier) && islower(board[x][y])) ||
                  (islower(identifier) && isupper(board[x][y]))) {
            moves.push_back(engine::ChessTile(x, y, true));
            break;
        } else {
            break;
        }
        y++;
    }

    // Check possible moves to the lower right -> MemSafe as for Loop won't start if out of bounds 
    y = curPos.second - 1;
    for(int x = curPos.first + 1; (x < 8 && y >= 0); x++) {
        if(board[x][y] == 0) {
            moves.push_back(engine::ChessTile(x, y));
        } else if((isupper(identifier) && islower(board[x][y])) ||
                  (islower(identifier) && isupper(board[x][y]))) {
            moves.push_back(engine::ChessTile(x, y, true));
            break;
        } else {
            break;
        }
        y--;
    }

    // Check possible moves to the lower left -> MemSafe as for Loop won't start if out of bounds 
    y = curPos.second - 1;
    for(int x = curPos.first - 1; (x >= 0 && y >= 0); x--) {
        if(board[x][y] == 0) {
            moves.push_back(engine::ChessTile(x, y));
        } else if((isupper(identifier) && islower(board[x][y])) ||
                  (islower(identifier) && isupper(board[x][y]))) {
            moves.push_back(engine::ChessTile(x, y, true));
            break;
        } else {
            break;
        }
        y--;
    }

    return moves;
}

/**
 * Knight Section
*/
Knight::Knight(engine::ChessTile tile, char figure) {
    this->position = tile;
    this->identifier = figure;
}

std::vector<engine::ChessTile> Knight::getPossibleMoves(const char board[8][8]) {
    std::vector<engine::ChessTile> moves;
    std::pair<int, int> curPos = position.getArrayNr();

    for(const auto& move : this->knightMoveVectors) {
        int newX = curPos.first + move[0];
        int newY = curPos.second + move[1];
        
        // Check OutOfBounds
        if(newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            if(board[newX][newY] == 0)
                moves.push_back(engine::ChessTile(newX, newY));
            else if((isupper(identifier) && islower(board[newX][newY])) ||
                    (islower(identifier) && isupper(board[newX][newY])))
                moves.push_back(engine::ChessTile(newX, newY, true));
        }
    }

    return moves;
}

/**
 * Rook Section 
*/
Rook::Rook(engine::ChessTile tile, char figure) {
    this->position = tile;
    this->identifier = figure;
}

std::vector<engine::ChessTile> Rook::getPossibleMoves(const char board[8][8]) {
    std::vector<engine::ChessTile> moves;
    std::pair<int, int> curPos = position.getArrayNr();

    // Check possible moves to the right -> MemSafe as for Loop won't start if out of bounds 
    for(int i = curPos.first + 1; i < 8; i++) {
        if(board[i][curPos.second] == 0)
            moves.push_back(engine::ChessTile(i, curPos.second));
        
        else if((isupper(identifier) && islower(board[i][curPos.second])) ||
                (islower(identifier) && isupper(board[i][curPos.second]))) {
            moves.push_back(engine::ChessTile(i, curPos.second, true));
            break;
        } else {
            break;
        }
    }

    // Check possible moves to the left -> MemSafe as for Loop won't start if out of bounds 
    for(int i = curPos.first - 1; i >= 0; i--) {
        if(board[i][curPos.second] == 0)
            moves.push_back(engine::ChessTile(i, curPos.second));
        else if((isupper(identifier) && islower(board[i][curPos.second])) ||
                (islower(identifier) && isupper(board[i][curPos.second]))) {
            moves.push_back(engine::ChessTile(i, curPos.second, true));
            break;
        } else {
            break;
        }
    }

    // Check possible moves upwards -> MemSafe as for Loop won't start if out of bounds 
    for(int j = curPos.second + 1; j < 8; j++) {
        if(board[curPos.first][j] == 0)
            moves.push_back(engine::ChessTile(curPos.first, j));
        else if((isupper(identifier) && islower(board[curPos.first][j])) ||
                (islower(identifier) && isupper(board[curPos.first][j]))) {
            moves.push_back(engine::ChessTile(curPos.first, j, true));
            break;
        } else {
            break;
        }
    }

    // Check possible moves downwards -> MemSafe as for Loop won't start if out of bounds 
    std::cout << "x: " << curPos.second << "\n";
    for(int j = curPos.second - 1; j >= 0; j--) {
        if(board[curPos.first][j] == 0) {
            moves.push_back(engine::ChessTile(curPos.first, j));
        } else if((isupper(identifier) && islower(board[curPos.first][j])) ||
                  (islower(identifier) && isupper(board[curPos.first][j]))) {
            moves.push_back(engine::ChessTile(curPos.first, j, true));
            break;
        } else {
            break;
        }
    }

    return moves;
}

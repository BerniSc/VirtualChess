#include "chessInterface.hpp"
#include "utility.hpp"

#include <vector>
#include <string>
#include <cctype>

char engine::ChessBoard::arrayBoard[8][8];
std::string engine::ChessBoard::currentBoard;

engine::ChessBoard::ChessBoard() {

}

engine::ChessBoard::~ChessBoard() {

}

char (*engine::ChessBoard::string2board(std::string fen))[8] {
    // Initialize the whole array to zero
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            arrayBoard[i][j] = 0;

    // Split the FEN to seperate Board from Game parameters
    std::vector<std::string> seperatedFen = split(fen, " ");

    int col = 0, line = 7;
    
    // Populate board-placeholder according to the Board-FEN
    for(char& symbol : seperatedFen[0]) {
        // Symbol represents Line change
        if(symbol == '/') {
            col = 0;
            line--;
        } else {
            // If Symbol is a Digit skip its value in cols
            if(isdigit(symbol)) {
                col += (int) (symbol - '0') - 1;
            } else {
                // set the pieces
                arrayBoard[line][col] = symbol;
                col++;
            }
        }
    }
    return arrayBoard;
}

std::string engine::ChessBoard::board2string(const char board[8][8]) {
    std::string fen = "";

    // Iterate through each row of the board
    for(int row = 7; row >= 0; row--) {
        int emptyCount = 0;

        // Iterate through each column of the row
        for(int col = 0; col < 8; col++) {
            if(board[row][col] == 0) {
                // Empty square, increment empty count
                emptyCount++;
            } else {
                // Non-empty square
                if(emptyCount > 0) {
                    // Append empty count to FEN string
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }

                // Append piece to FEN string
                fen += board[row][col];
            }
        }

        // Handle the last empty squares in the row
        if(emptyCount > 0)
            fen += std::to_string(emptyCount);

        // Separate rows with '/'
        if(row > 0)
            fen += '/';
    }

    return fen;
}

char (*engine::ChessBoard::getBoardArray() const)[8] {
    return this->arrayBoard;
}

void engine::ChessBoard::reset() {
    // Reset the Board to the Initial String
    this->currentBoard = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
}
#include "chessInterface.hpp"
#include "utility.hpp"

#include <vector>
#include <string>
#include <cctype>

char** engine::ChessBoard::string2board(std::string fen) {
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
                col += (int) (symbol - '0');
            } else {
                // set the pieces
                arrayBoard[line][col] = symbol;
                col++;
            }
        }
    }
}
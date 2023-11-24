#include "chessTester.hpp"

ChessTester::ChessTester(engine::ChessEngine& engine) : engine(engine) {

}

void ChessTester::printBoard(char(* board)[8]) {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            std::cout << (board[col][row] == 0 ? '.' : board[col][row]);
        }
        std::cout << "\n";
    }
}

void ChessTester::printBoard(std::string board) {
    std::cout << "FEN: " << board << std::endl;
    printBoard(engine::ChessBoard::string2board(board));
}

void ChessTester::printBoardWithHighlights(char(* board)[8], const std::vector<engine::ChessTile>& highlights) {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            // Check if the current position is in the vector of highlights
            bool isHighlighted = false;
            bool isCaptureMove = false;
            for(const auto& tile : highlights) {
                std::pair<int, int> pos = tile.getArrayNr();
                if(pos.first == col && pos.second == row) {
                    isHighlighted = true;
                    isCaptureMove = tile.getIsCaptureMove();
                    break;
                }
            }

            // Print in green if highlighted, otherwise print normally
            if(isHighlighted) {
                // Print all CaptureMoves red and Free Moves green
                if(!isCaptureMove)
                    std::cout << "\033[32m" << (board[col][row] == 0 ? '*' :  board[col][row]) << "\033[0m";
                else
                    std::cout << "\033[31m" << (board[col][row] == 0 ? '*' :  board[col][row]) << "\033[0m";
            } else {
                std::cout << (board[col][row] == 0 ? '*' :  board[col][row]);
            }
        }
        std::cout << "\n";
    }
}

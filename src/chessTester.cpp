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

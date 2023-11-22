#include "chessTester.hpp"

ChessTester::ChessTester(engine::ChessEngine& engine) : engine(engine) {

}

void ChessTester::printBoard(char(* board)[8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            std::cout << board[i][j];
        }
        std::cout << "\n";
    }
}

void ChessTester::printBoard(std::string board) {
    std::cout << "FEN: " << board << std::endl;
    printBoard(engine::ChessBoard::string2board(board));
}

void ChessTester::printPos(char const figure) {
    engine::ChessTile tile = this->engine.getPosition(figure);
    std::pair<int, int> tmp = tile.getArrayNr();
    std::cout << tmp.first << "|" << tmp.second << std::endl;
}
#include "chessInterface.hpp"

std::vector<engine::ChessTile> engine::ChessEngine::getPossibleMoves(char const figure) const {
    for(Figure* f : aliveFigures)
        if(f->identifier == figure)
            return f->getPossibleMoves(this->currentBoard.arrayBoard);
}

char** engine::ChessEngine::getCurrentBoard() const {
    return this->currentBoard.getBoardArray();
}
#include "chessInterface.hpp"

std::vector<engine::ChessTile> engine::ChessEngine::getPossibleMoves(char const figure) const {
    for(auto f : aliveFigures)
        if(f.second->identifier == figure)
            return f.second->getPossibleMoves(this->currentBoard.arrayBoard);
}

char (* engine::ChessEngine::getCurrentBoard() const)[8] {
    return this->currentBoard.getBoardArray();
}

engine::ChessTile engine::ChessEngine::getPosition(char const figure) const {
    auto iter = aliveFigures.find(figure);
    Figure* wantedFigure = (iter != aliveFigures.end() ? iter->second : nullptr);

    if(wantedFigure != nullptr)
        return wantedFigure->position;

    // If the figure is not found, return an invalid ChessTile
    return engine::ChessTile(-1, -1);
}

void engine::ChessEngine::reset() {
    currentBoard.reset();
    
}
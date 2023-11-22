#include "chessInterface.hpp"

engine::ChessEngine::ChessEngine() {
    this->moveGen = new MoveGenerator();
}

engine::ChessEngine::~ChessEngine() {
    if(moveGen)
        delete moveGen;
}

std::vector<engine::ChessTile> engine::ChessEngine::getPossibleMoves(engine::ChessTile tile) const {
    return moveGen->getPossibleMoves(this->currentBoard.getBoardArray(), tile);
}

char (* engine::ChessEngine::getCurrentBoard() const)[8] {
    return this->currentBoard.getBoardArray();
}

void engine::ChessEngine::reset() {
    currentBoard.reset();
}


engine::ChessEngine::MoveGenerator::MoveGenerator() {
    std::cout << "Creted MoveGen\n";
}

engine::ChessEngine::MoveGenerator::~MoveGenerator() {
    if(this->referenceMover)
        delete referenceMover;
}

std::vector<engine::ChessTile> engine::ChessEngine::MoveGenerator::getPossibleMoves(char const board[8][8], engine::ChessTile tile) {
    std::vector<engine::ChessTile> allowedMoves;

    std::pair<int, int> pos = tile.getArrayNr(); 
    char figure = board[pos.first][pos.second];

    if(this->referenceMover)
        delete referenceMover;

    // Parse the current Tile content
    switch(toupper(figure)) {
        case constants::ROOK :
            //referenceMover = new Rook();
            break;
        case constants::KNIGHT :
            //referenceMover = new Knight();
            break;
        case constants::BISHOP :
            //referenceMover = new Bishop();
            break;
        case constants::KING :
            //referenceMover = new King();
            break;
        case constants::QUEEN :
            //referenceMover = new Queen();
            break;
        case constants::PAWN :
            referenceMover = new Pawn(tile, figure);
            break;
    }
    
    if(referenceMover)
        allowedMoves = this->referenceMover->getPossibleMoves(board);

    return allowedMoves;
    
}
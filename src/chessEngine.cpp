#include "chessInterface.hpp"

#include <stdexcept>

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

    if(pos.first > 7 || pos.first < 0 || pos.second > 7 || pos.second < 0) {
        std::cout << "Invalid index in getPossible Moves: " << pos.first << "   " << pos.second << std::endl;
        return allowedMoves; 
    }

    std::cout << pos.first << "||" << pos.second << std::endl;

    char figure = board[pos.first][pos.second];

    std::cout << "Checking Figure " << figure << " on x:" << pos.first << "| y:" << pos.second << std::endl;

    if(this->referenceMover)
        delete referenceMover;

    // Parse the current Tile content
    switch(toupper(figure)) {
        case constants::ROOK :
            referenceMover = new Rook(tile, figure);
            break;
        case constants::KNIGHT :
            //throw std::runtime_error("Feature KNIGHT MOVE not supportet");
            referenceMover = new Knight(tile, figure);
            break;
        case constants::BISHOP :
            //throw std::runtime_error("Feature BISHOP MOVE not supportet");
            referenceMover = new Bishop(tile, figure);
            break;
        case constants::KING :
            throw std::runtime_error("Feature KING MOVE not supportet");
            //referenceMover = new King();
            break;
        case constants::QUEEN :
            //throw std::runtime_error("Feature QUEEN MOVE not supportet");
            referenceMover = new Queen(tile, figure);
            break;
        case constants::PAWN :
            referenceMover = new Pawn(tile, figure);
            break;
        default :
            throw std::runtime_error("Please try a Tile containing Something");
    }
    
    if(referenceMover)
        allowedMoves = this->referenceMover->getPossibleMoves(board);

    return allowedMoves;
    
}
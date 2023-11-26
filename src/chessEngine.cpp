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
    std::vector<engine::ChessTile>& allowedMoves = this->lastPossibleMoves;

    this->lastCheckedTile = tile;

    std::pair<int, int> pos = tile.getArrayNr();

    if(pos.first > 7 || pos.first < 0 || pos.second > 7 || pos.second < 0) {
        std::cout << "Invalid index in getPossible Moves: " << pos.first << "   " << pos.second << std::endl;
        return allowedMoves; 
    }

    char figure = board[pos.first][pos.second];

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

    this->lastPossibleMoves = allowedMoves;

    return allowedMoves;
}

bool engine::ChessEngine::tryMove(engine::ChessTile source, engine::ChessTile target) {
    bool retVal = false;

    // If the Source is not also the last checked Tile check the Source and safe its Tiles in MoveGev
    if(source != this->moveGen->lastCheckedTile)
        getPossibleMoves(source);
    
    // If TargetTile is contained in possible Moves do the Move
    if(std::find(this->moveGen->lastPossibleMoves.begin(), this->moveGen->lastPossibleMoves.end(), target) != this->moveGen->lastPossibleMoves.end()) {
        this->move(source, target);
        retVal = true;
    }

    return retVal;
}

void engine::ChessEngine::move(engine::ChessTile source, engine::ChessTile target) {
    this->currentBoard.move(source, target);
}

char engine::ChessEngine::MoveGenerator::checkCheck(char figure, char const board[8][8]) const {
    // TODO -> Store KingPos somewhere and catch non-king queries
    int kingPosX = -1, kingPosY = -1;
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            if(board[x][y] == figure) {
                kingPosX = x;
                kingPosY = y;
                break;
            }
        }
    }

    std::cout << "KingPos: " << kingPosX << "   " << kingPosY << std::endl; 

    engine::ChessTile kingTile(kingPosX, kingPosY);

    Knight referenceKnight(kingTile, (std::isupper(figure) ? 'N' : 'n'));
    Rook referenceRook(kingTile, (std::isupper(figure) ? 'R' : 'r'));
    Bishop referenceBishop(kingTile, (std::isupper(figure) ? 'B' : 'b'));
    Queen referenceQueen(kingTile, (std::isupper(figure) ? 'Q' : 'q'));
    Pawn referencePawn(kingTile, (std::isupper(figure) ? 'P' : 'p'));

    // Get possible moves for each piece
    std::vector<engine::ChessTile> movesKnight = referenceKnight.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesRook = referenceRook.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesBishop = referenceBishop.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesQueen = referenceQueen.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesPawn = referencePawn.getPossibleMoves(board);

    // Check if any of the pieces can capture the king
    for(const auto& move : movesKnight) {
        std::pair<int,int> pos = move.getArrayNr();
        if(move.getIsCaptureMove() && toupper(board[pos.first][pos.second]) == toupper('N'))
            return true;
    }

    std::cout << "N\n";

    for(const auto& move : movesRook) {
        std::pair<int,int> pos = move.getArrayNr();
        if(move.getIsCaptureMove() && toupper(board[pos.first][pos.second]) == toupper('R'))
            return true;
    }

    std::cout << "R\n";

    for(const auto& move : movesBishop) {
        std::pair<int,int> pos = move.getArrayNr();
        if(move.getIsCaptureMove() && toupper(board[pos.first][pos.second]) == toupper('B'))
            return true;
    }

    std::cout << "B\n";

    for(const auto& move : movesQueen) {
        std::pair<int,int> pos = move.getArrayNr();
        if(move.getIsCaptureMove() && toupper(board[pos.first][pos.second]) == toupper('Q')) {
            std::cout << "MEQ: " << pos.first << "  " << pos.second << "\n";
            return true;
        }
    }

    std::cout << "Q\n";

    for(const auto& move : movesPawn) {
        std::pair<int,int> pos = move.getArrayNr();
        if(move.getIsCaptureMove() && toupper(board[pos.first][pos.second]) == toupper('P'))
            return true;
    }

    std::cout << "P\n";

    return false;
}
#include "chessInterface.hpp"

#include <stdexcept>

engine::ChessEngine::ChessEngine() {
    this->moveGen = new MoveGenerator(this);
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


engine::ChessEngine::MoveGenerator::MoveGenerator(engine::ChessEngine* engine) : referenceMover(nullptr), super(engine) {
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

    if(this->referenceMover != nullptr)
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
            //throw std::runtime_error("Feature KING MOVE not supportet");
            referenceMover = new King(tile, figure);
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

    /**
    *   Consider the weird Special moves, that affect more then the Source and the Target Field
    */
    // If the Current Board is castleable and the tried Figure is a King or a Rook add the CastleMoves
    if(super->currentBoard.castleable != "-") {
        std::vector<engine::ChessTile> castleMoves = this->getCastleMoves(figure, board);
        for(engine::ChessTile& move : castleMoves) {
            allowedMoves.push_back(move);
        }
    }

    // If the Last Move was a EnPassantable Move and now an EnPassante is possible then also add the EnPassante Tiles to possible moves
    if(super->currentBoard.enPassante != "-") {
        int x = (super->currentBoard.enPassante[0] - 'a');
        int y = (super->currentBoard.enPassante[1] - '1');
        // Check if EnPassante is possible
        if(true) {
            std::cout << "Added an EnPassante move the the Vector of possible Moves\n";
            ChessTile tile(x, y);
            tile.setIsEnPassante(true);
            allowedMoves.push_back(tile);
        }
    }

    /**
     *  Finally remove the illegal moves from the List 
    */
    // Now remove all the Moves that would result in the own King checked
    allowedMoves.erase(std::remove_if(allowedMoves.begin(), allowedMoves.end(), 
        [&](const engine::ChessTile& obj) {
            return this->checkPseudoMove(tile, obj, board);
        }
    ), allowedMoves.end());

    this->lastPossibleMoves = allowedMoves;

    return allowedMoves;
}

bool engine::ChessEngine::tryMove(engine::ChessTile source, engine::ChessTile target) {
    bool retVal = false;

    // If the Source is not also the last checked Tile check the Source and safe its Tiles in MoveGev
    if(source != this->moveGen->lastCheckedTile)
        getPossibleMoves(source);
    
    // If TargetTile is contained in possible Moves do the Move
    auto iter = std::find(this->moveGen->lastPossibleMoves.begin(), this->moveGen->lastPossibleMoves.end(), target);
    if(iter != this->moveGen->lastPossibleMoves.end()) {
        this->move(source, *iter.base());

        if((*iter.base()).getIsCastleMove()) {
            std::pair<engine::ChessTile, engine::ChessTile> correspondingMove = moveGen->getOpposingCastleMove(target);
            this->move(correspondingMove.first, correspondingMove.second);
        }

        retVal = true;
    }

    return retVal;
}

void engine::ChessEngine::move(engine::ChessTile source, engine::ChessTile target) {
    this->currentBoard.move(source, target);
}

// TODO Add Check (Reference) for King also, maybe not for ChessCheck?, also return the offending Tile?
bool engine::ChessEngine::MoveGenerator::checkUnderSiege(engine::ChessTile tile, char figure, char const board[8][8]) const {
    Knight referenceKnight(tile, (std::isupper(figure) ? 'N' : 'n'));
    Rook referenceRook(tile, (std::isupper(figure) ? 'R' : 'r'));
    Bishop referenceBishop(tile, (std::isupper(figure) ? 'B' : 'b'));
    Queen referenceQueen(tile, (std::isupper(figure) ? 'Q' : 'q'));
    Pawn referencePawn(tile, (std::isupper(figure) ? 'P' : 'p'));

    // Get possible moves for each piece
    std::vector<engine::ChessTile> movesKnight = referenceKnight.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesRook = referenceRook.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesBishop = referenceBishop.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesQueen = referenceQueen.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesPawn = referencePawn.getPossibleMoves(board);

    // Check if any of the pieces can capture the tile under attack -> See if it could capture itsself from the Tile 
    for(const auto& move : movesKnight) {
        std::pair<int,int> pos = move.getArrayNr();
        if(move.getIsCaptureMove() && toupper(board[pos.first][pos.second]) == toupper('N'))
            return true;
    }

    for(const auto& move : movesRook) {
        std::pair<int,int> pos = move.getArrayNr();
        if(move.getIsCaptureMove() && toupper(board[pos.first][pos.second]) == toupper('R'))
            return true;
    }

    for(const auto& move : movesBishop) {
        std::pair<int,int> pos = move.getArrayNr();
        if(move.getIsCaptureMove() && toupper(board[pos.first][pos.second]) == toupper('B'))
            return true;
    }

    for(const auto& move : movesQueen) {
        std::pair<int,int> pos = move.getArrayNr();
        if(move.getIsCaptureMove() && toupper(board[pos.first][pos.second]) == toupper('Q')) {
            return true;
        }
    }

    for(const auto& move : movesPawn) {
        std::pair<int,int> pos = move.getArrayNr();
        if(move.getIsCaptureMove() && toupper(board[pos.first][pos.second]) == toupper('P'))
            return true;
    }

    return false;
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

    engine::ChessTile kingTile(kingPosX, kingPosY);

    bool check = this->checkUnderSiege(kingTile, figure, board);

    if(check) std::cout << "SCHACH...\n";

    return check;
}

// TODO -> Let the GUI allow to distinguish between Rook Move and Rook Castle Move
std::pair<engine::ChessTile, engine::ChessTile> engine::ChessEngine::MoveGenerator::getOpposingCastleMove(const engine::ChessTile& move) const {
    std::pair<int, int> pos = move.getArrayNr();

    // Return the Source of the Opposite move as well as its Target
    std::pair<engine::ChessTile, engine::ChessTile> oppositeMove;

    if(pos.first == 2) {
        // Queenside castling
        oppositeMove.first = engine::ChessTile(0, pos.second, false, true);
        oppositeMove.second = engine::ChessTile(3, pos.second, false, true);
    } else if(pos.first == 3) {
        // Queenside castling (rook move)
        oppositeMove.first = engine::ChessTile(4, pos.second, false, true);
        oppositeMove.second = engine::ChessTile(2, pos.second, false, true);
    } else if(pos.first == 6) {
        // Kingside castling
        oppositeMove.first = engine::ChessTile(7, pos.second, false, true);
        oppositeMove.second = engine::ChessTile(5, pos.second, false, true);
    } else if(pos.first == 5) {
        // Kingside castling (rook move)
        oppositeMove.first = engine::ChessTile(4, pos.second, false, true);
        oppositeMove.second = engine::ChessTile(6, pos.second, false, true);
    }

    return oppositeMove;
}

std::vector<engine::ChessTile> engine::ChessEngine::MoveGenerator::getCastleMoves(char figure, char const board[8][8]) const {
    std::vector<engine::ChessTile> castleMoves;
    engine::ChessTile castleMove;
    int yCoordinate = (isupper(figure) ? 7 : 0);

    // Checks wheter the current Move is a possible Queenside Castle (The calling Figure is either at x=0 (Left Rook) or the King
    bool queensideCastle = (this->lastCheckedTile.getArrayNr().first == 0 | toupper(figure) == 'K');
    // Checks wheter the current Move is a possible Queenside Castle (The calling Figure is either at x=7 (Right Rook) or the King
    bool kingsideCastle = (this->lastCheckedTile.getArrayNr().first == 7 | toupper(figure) == 'K');

    // Add the Castling Move -> Queenside first
    // TODO -> Maybe move away from using lastCheckedTiles
    if(queensideCastle && super->currentBoard.getCastleable().find((isupper(figure) ? 'Q' : 'q')) != std::string::npos) {
        // Check if the squares between the king and the rook are empty
        if(board[1][yCoordinate] == 0 && board[2][yCoordinate] == 0 && board[3][yCoordinate] == 0) {
            bool movementSpacesClear;
            movementSpacesClear = !(this->checkUnderSiege(engine::ChessTile(2, yCoordinate), figure, board));
            movementSpacesClear = movementSpacesClear && !(this->checkUnderSiege(engine::ChessTile(3, yCoordinate), figure, board));
            movementSpacesClear = movementSpacesClear && !(this->checkUnderSiege(engine::ChessTile(4, yCoordinate), figure, board));
            // Check if the King is NOT in Check and the Tiles in between are not under Siege
            if(!(this->checkCheck((isupper(figure) ? 'K' : 'k'), board)) && movementSpacesClear) {
                if(toupper(figure) == 'K') {
                    // The Move for the King -> No Capture but Castle
                    castleMove = engine::ChessTile(2, yCoordinate, false, true);
                } else {
                    // The Move for the Rook -> No Capture but Castle
                    castleMove = engine::ChessTile(3, yCoordinate, false, true);
                }
                castleMoves.push_back(castleMove);
            }
        }
    }

    // Now add the Kingside Castling Move
    if(kingsideCastle && super->currentBoard.getCastleable().find((isupper(figure) ? 'K' : 'k')) != std::string::npos) {
        // Check if the squares between the king and the rook are empty
        if(board[5][yCoordinate] == 0 && board[6][yCoordinate] == 0) {
            bool movementSpacesClear;
            movementSpacesClear = !this->checkUnderSiege(engine::ChessTile(5, yCoordinate), figure, board);
            movementSpacesClear = movementSpacesClear && !this->checkUnderSiege(engine::ChessTile(6, yCoordinate), figure, board);
            // Check if the King is NOT in Check and the Tiles in between are not under Siege
            if(!(this->checkCheck((isupper(figure) ? 'K' : 'k'), board)) && movementSpacesClear) {
                if(toupper(figure) == 'K') {
                    // The Move for the King -> No Capture but Castle
                    castleMove = engine::ChessTile(6, yCoordinate, false, true);
                } else {
                    // The Move for the Rook -> No Capture but Castle
                    castleMove = engine::ChessTile(5, yCoordinate, false, true);
                }
                castleMoves.push_back(castleMove);
            }
        }
    }

    std::cout << "Added " << castleMoves.size() << " Castle Moves\n";
    return castleMoves;
}

bool engine::ChessEngine::MoveGenerator::checkPseudoMove(engine::ChessTile source, engine::ChessTile target, const char board[8][8]) const {
    char tempBoard[8][8];

    // Using nested loops to copy the array
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    std::pair<int,int> sourcePos = source.getArrayNr();
    std::pair<int,int> targetPos = target.getArrayNr();

    char figureSrc = board[sourcePos.first][sourcePos.second];

    tempBoard[sourcePos.first][sourcePos.second] = 0;
    tempBoard[targetPos.first][targetPos.second] = figureSrc;

    bool check = checkCheck((isupper(figureSrc) ? 'K' : 'k'), tempBoard);
    std::cout << "Schachdetektor Pseudo " << (check ? "true" : "false") << "\n";
    return check;
}
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


engine::ChessEngine::MoveGenerator::MoveGenerator(engine::ChessEngine* engine) : super(engine) {
    engine::ChessTile startTile;
    // Knight
    referenceMovers[constants::KNIGHT] = std::unique_ptr<engine::Figure>(new Knight(startTile, constants::KNIGHT));
    referenceMovers[constants::knight] = std::unique_ptr<engine::Figure>(new Knight(startTile, constants::knight));
    // Rook
    referenceMovers[constants::ROOK] = std::unique_ptr<engine::Figure>(new Rook(startTile, constants::ROOK));
    referenceMovers[constants::rook] = std::unique_ptr<engine::Figure>(new Rook(startTile, constants::rook));
    // Bishop
    referenceMovers[constants::BISHOP] = std::unique_ptr<engine::Figure>(new Bishop(startTile, constants::BISHOP));
    referenceMovers[constants::bishop] = std::unique_ptr<engine::Figure>(new Bishop(startTile, constants::bishop));
    // Queen
    referenceMovers[constants::QUEEN] = std::unique_ptr<engine::Figure>(new Queen(startTile, constants::QUEEN));
    referenceMovers[constants::queen] = std::unique_ptr<engine::Figure>(new Queen(startTile, constants::queen));
    // Pawn
    referenceMovers[constants::PAWN] = std::unique_ptr<engine::Figure>(new Pawn(startTile, constants::PAWN));
    referenceMovers[constants::pawn] = std::unique_ptr<engine::Figure>(new Pawn(startTile, constants::pawn));
    // King
    referenceMovers[constants::KING] = std::unique_ptr<engine::Figure>(new King(startTile, constants::KING));
    referenceMovers[constants::king] = std::unique_ptr<engine::Figure>(new King(startTile, constants::king));

    std::cout << "Creted MoveGen\n";
}

engine::ChessEngine::MoveGenerator::~MoveGenerator() {

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

    // Only a figure of the coulour that is set for the Turn can make a move 
    if(!constants::debugMovementColourfree) {        
        if(isupper(figure) && super->currentBoard.turn == 'b' || islower(figure) && super->currentBoard.turn == 'w') {
            std::cout << "Tried to move " << figure << " when it wasnt your Turn\n";
            return std::vector<engine::ChessTile>(0);
        }
    }

    // Parse the current Tile content
    switch(toupper(figure)) {
        case constants::ROOK :
            referenceMover = dereferenceMovers(figure);
            break;
        case constants::KNIGHT :
            //throw std::runtime_error("Feature KNIGHT MOVE not supportet");
            referenceMover = dereferenceMovers(figure);
            break;
        case constants::BISHOP :
            //throw std::runtime_error("Feature BISHOP MOVE not supportet");
            referenceMover = dereferenceMovers(figure);
            break;
        case constants::KING :
            //throw std::runtime_error("Feature KING MOVE not supportet");
            referenceMover = dereferenceMovers(figure);
            break;
        case constants::QUEEN :
            //throw std::runtime_error("Feature QUEEN MOVE not supportet");
            referenceMover = dereferenceMovers(figure);
            break;
        case constants::PAWN :
            referenceMover = dereferenceMovers(figure);
            break;
        default :
            referenceMover = nullptr;
            throw std::runtime_error("Please try a Tile containing Something");
    }
    
    if(referenceMover != nullptr) {
        referenceMover->setPosition(tile);
        allowedMoves = this->referenceMover->getPossibleMoves(board);
    }

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
        // For it to Work current Figure must be a Pawn, be of opposing Colour and right next to the enPassantable Pawn in question
        // Rank for White would be 3 and for Black 4
        if(toupper(figure) == constants::PAWN && pos.second == (isupper(figure) ? 3 : 4) && (x == pos.first - 1 || x == pos.first + 1)) {
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

/***
 * Helper Function to dereference referenceMover in Question
*/
engine::Figure* engine::ChessEngine::MoveGenerator::dereferenceMovers(char const mover) {
    auto referenceMover = this->referenceMovers.find(mover);
        
    return referenceMover->second.get();
}

bool engine::ChessEngine::tryMove(engine::ChessTile source, engine::ChessTile target) {
    bool retVal = false;

    // TODO Needed?
    if(source == target) return retVal;

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

void engine::ChessEngine::move(const engine::ChessTile& source, const engine::ChessTile& target) {
    this->currentBoard.move(source, target);
    this->moveGen->lastPossibleMoves.clear();
}

// TODO Add Check (Reference) for King also, maybe not for ChessCheck?, also return the offending Tile?
bool engine::ChessEngine::MoveGenerator::checkUnderSiege(engine::ChessTile tile, char figure, char const board[8][8]) const {
    // TODO Implement this version relying on the Map that is already created
    // std::string referenceString = (std::isupper(figure) ? "KRBQP" : "krbqp");
    Knight referenceKnight(tile, (std::isupper(figure) ? constants::KNIGHT : constants::knight));
    Rook referenceRook(tile, (std::isupper(figure) ? constants::ROOK : constants::rook));
    Bishop referenceBishop(tile, (std::isupper(figure) ? constants::BISHOP : constants::bishop));
    Queen referenceQueen(tile, (std::isupper(figure) ? constants::QUEEN : constants::queen));
    Pawn referencePawn(tile, (std::isupper(figure) ? constants::PAWN : constants::pawn));

    // Get possible moves for each piece
    std::vector<engine::ChessTile> movesKnight = referenceKnight.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesRook = referenceRook.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesBishop = referenceBishop.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesQueen = referenceQueen.getPossibleMoves(board);
    std::vector<engine::ChessTile> movesPawn = referencePawn.getPossibleMoves(board);

    // Check if any of the pieces can capture the tile under attack -> See if it could capture itsself from the Tile 
    // Colour already considered in getPossibleMoves
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

char engine::ChessEngine::MoveGenerator::checkCheckMate(char figure, char const board[8][8]) const {
    throw(std::runtime_error("Not implemented Yet!"));
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

    // Catch Bug where moving pawn at x0 or x7 gives him castling ability.... Thats not really intended, but kinda cool ^^
    if(toupper(figure) != 'K' || toupper(figure) != 'R')
        return castleMoves;

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

    if(constants::debugCastle) std::cout << "Added " << castleMoves.size() << " Castle Moves\n";
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
    if(constants::debugPseudoChess) std::cout << "Schachdetektor Pseudo " << (check ? "true" : "false") << "\n";
    return check;
}
#include "chessInterface.hpp"
#include "utility.hpp"

#include <vector>
#include <string>
#include <cctype>

char engine::ChessBoard::arrayBoard[8][8];
std::string engine::ChessBoard::currentBoard;

// Used for piecing together FEN
char engine::ChessBoard::turn = 'w';
std::string engine::ChessBoard::castleable = "KQkq";
std::string engine::ChessBoard::enPassante = "-";
int engine::ChessBoard::halfmoves = 0;
int engine::ChessBoard::moveNumber = 1;

engine::ChessBoard::ChessBoard() {
    reset();
}

engine::ChessBoard::~ChessBoard() {

}

char (*engine::ChessBoard::string2board(std::string fen))[8] {
    // Initialize the whole array to zero
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            arrayBoard[i][j] = 0;

    // Split the FEN to seperate Board from Game parameters
    std::vector<std::string> seperatedFen = split(fen, " ");

    int col = 0, line = 0;
    
    // Populate board-placeholder according to the Board-FEN
    for(char& symbol : seperatedFen[0]) {
        // Symbol represents Line change
        if(symbol == '/') {
            col = 0;
            line++;
        } else {
            // If Symbol is a Digit skip its value in cols
            if(isdigit(symbol)) {
                col += (int) (symbol - '0');
            } else {
                // set the pieces
                arrayBoard[col][line] = symbol;
                col++;
            }
        }
    }
    
    return arrayBoard;
}

/**
 * Converts the given Board to a FEN, Also adds the current "Elements" like turn, castleable flag etc to the FEN
*/
std::string engine::ChessBoard::board2string(const char board[8][8]) {
    std::string fen = "";

    // Iterate through each row of the board
    for(int row = 0; row < 8; row++) {
        int emptyCount = 0;

        // Iterate through each column of the row
        for(int col = 0; col < 8; col++) {
            if(board[col][row] == 0) {
                // Empty square, increment empty count
                emptyCount++;
            } else {
                // Non-empty square
                if(emptyCount > 0) {
                    // Append empty count to FEN string
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }

                // Append piece to FEN string
                fen += board[col][row];
            }
        }

        // Handle the last empty squares in the row
        if(emptyCount > 0)
            fen += std::to_string(emptyCount);

        // Separate rows with '/' except last row
        if(row < 7)
            fen += '/';
    }

    // Add the Appendage descibing the current Board to the FEN
    fen += " ";
    fen += turn;
    fen += " ";
    fen += castleable;
    fen += " ";
    fen += enPassante;
    fen += " ";
    fen += std::to_string(halfmoves);
    fen += " ";
    fen += std::to_string(moveNumber);
    
    return fen;
}

char (*engine::ChessBoard::getBoardArray() const)[8] {
    return this->arrayBoard;
}

std::string engine::ChessBoard::getBoardString() const {
    return this->currentBoard;
}

std::string engine::ChessBoard::getCastleable() const {
    return this->castleable;
}

void engine::ChessBoard::writeBoardInternaly(char (* array)[8]) {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            this->arrayBoard[col][row] = array[col][row];
        }
    }
}

void engine::ChessBoard::reset() {
    // Reset the Board to the Initial String
    std::string initialFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; 
    this->currentBoard = initialFEN;
    this->writeBoardInternaly(engine::ChessBoard::string2board(initialFEN));
}

void engine::ChessBoard::move(engine::ChessTile source, engine::ChessTile target) {
    std::pair<int,int> sourcePos = source.getArrayNr();
    std::pair<int,int> targetPos = target.getArrayNr();

    char figureSrc = this->arrayBoard[sourcePos.first][sourcePos.second];

    // Remove the specific Castleable Flag if a move blocks it 
    if(this->castleable.size() != 0) {

        if(toupper(figureSrc) == 'K') {
            this->castleable.erase(remove(castleable.begin(), castleable.end(), (isupper(figureSrc) ? 'K' : 'k')), castleable.end());
            this->castleable.erase(remove(castleable.begin(), castleable.end(), (isupper(figureSrc) ? 'Q' : 'q')), castleable.end());
        }

        if(toupper(figureSrc) == 'R') {
            if(sourcePos.first == 0)
                this->castleable.erase(remove(castleable.begin(), castleable.end(), (isupper(figureSrc) ? 'Q' : 'q')), castleable.end());
            if(sourcePos.first == 7)
                this->castleable.erase(remove(castleable.begin(), castleable.end(), (isupper(figureSrc) ? 'K' : 'k')), castleable.end());
        }
    } else {
        this->castleable = "-";
    }

    // Set En-Passante-Flag if Move is EnPassantable
    if(target.getIsEnPassanteable()) {
        std::pair<char, int> pos = target.getFieldNr();
        char x = tolower(pos.first);
        int y = pos.second + (isupper(figureSrc) ? 1 : -1);
        std::cout << "Added an EnPassante Move on " << x << " | " << y << "\n";
        this->enPassante = x + std::to_string(y);
    } else if(this->enPassante != "-") {
        // Reset it as well if it isnt already reset
        this->enPassante = "-";
    }

    this->arrayBoard[sourcePos.first][sourcePos.second] = 0;
    this->arrayBoard[targetPos.first][targetPos.second] = figureSrc;

    if(target.getIsEnPassante())     {
        // Also remove the passed piece if the Move is an actual En Passante Move TODO -> TEST 
        this->arrayBoard[targetPos.first][targetPos.second + ((targetPos.second == 2) ? 1 : -1)] = 0;
        std::cout << "Removed part " << targetPos.first << " | " << targetPos.second + ((targetPos.second == 2) ? -1 : 1) << "\n";
    }

    this->currentBoard = engine::ChessBoard::board2string(this->arrayBoard);

    this->moveNumber++;

    // Swap the current turn-colour
    this->turn = (this->turn == 'w' ? 'b' : 'w');
    
    // IF THE AI IS DEFINED LET IT DO THE MOVE FOR THE BLACK FIGURES
    #ifdef AI_MOVES_BLACK
        if(this->turn == 'b') {
            MOVE aiMove = ai.getBestMove(this->currentBoard);
            move(aiMove.first, aiMove.second);
        }
    #endif
}

void engine::ChessBoard::loadFEN(std::string fen) {
    // TODO -> Implement full parsing/storing of the FEN, Also in string2Fen and fen2board
    std::vector<std::string> seperatedFen = split(fen, " ");
    this->currentBoard = seperatedFen[0];
    // TODO CHeck for other Params as well -> For now sufficient, as if one extra is passed then probably the others as well
    if(fen.size() > 2) {
        this->turn = seperatedFen[1][0];
        this->castleable = seperatedFen[2];
        this->enPassante = seperatedFen[3];
        this->halfmoves = stol(seperatedFen[4]);
        this->moveNumber = stol(seperatedFen[5]);
    } else {
        this->castleable = "KQkq";
    }

    char(*newBoard)[8] = string2board(currentBoard);
    this->writeBoardInternaly(newBoard);
}
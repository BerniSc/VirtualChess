#include "chessInterface.hpp"
#include "utility.hpp"

#include <vector>
#include <string>
#include <cctype>

char engine::ChessBoard::arrayBoard[8][8];
std::string engine::ChessBoard::currentBoard;
char engine::ChessBoard::turn = 'w';
std::string engine::ChessBoard::castleable = "KQkq";

engine::ChessBoard::ChessBoard() {
    turn = 'w';
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

    fen += " ";
    fen += turn;
    fen += " ";
    

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
    if(this->castleable.size() != 0 && toupper(figureSrc) == 'K') {
        this->castleable.erase(remove(castleable.begin(), castleable.end(), (isupper(figureSrc) ? 'K' : 'k')), castleable.end());
        this->castleable.erase(remove(castleable.begin(), castleable.end(), (isupper(figureSrc) ? 'Q' : 'q')), castleable.end());
    }

    if(this->castleable.size() != 0 && toupper(figureSrc) == 'R') {
        if(sourcePos.first == 0)
            this->castleable.erase(remove(castleable.begin(), castleable.end(), (isupper(figureSrc) ? 'Q' : 'q')), castleable.end());
        if(sourcePos.first == 7)
            this->castleable.erase(remove(castleable.begin(), castleable.end(), (isupper(figureSrc) ? 'K' : 'k')), castleable.end());
    }

    if(!target.getIsCaptureMove()) {
        this->arrayBoard[sourcePos.first][sourcePos.second] = 0;
        this->arrayBoard[targetPos.first][targetPos.second] = figureSrc;
    }

    this->currentBoard = engine::ChessBoard::board2string(this->arrayBoard);
}

void engine::ChessBoard::loadFEN(std::string fen) {
    this->currentBoard = fen;
                
    char(*newBoard)[8] = string2board(currentBoard);
    this->writeBoardInternaly(newBoard);
}

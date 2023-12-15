#ifndef CHESS_INTERFACE_HPP
#define CHESS_INTERFACE_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>

#include <iostream>

#include <algorithm> // For checking if contained in Vector

#include "chessConstants.hpp"
#include "chessTile.hpp"
#include "figure.hpp"

namespace engine {
    // Need ad Least Engine for Friend declaration and Figure
    class ChessBoard;
    class ChessEngine;
    class Figure;

    // Class that contains the actuall internal representation of the board that is beeing played 
    //    -> Provides STATIC conversion functions from internal storage to other notation Form (Char array and FEN-String)
    //    like to the external char[8][8], that can be used much more intuitively
    class ChessBoard {
        private:
            // Static as needed in static Functions
            static std::string currentBoard;
            static char arrayBoard[8][8];
            static char turn;
            
            ChessBoard();                                                  // Private constructor -> Only usable in Friend (ChessEngine)

            // TODO -> Add var that shows wheter the current Board is castleable and a fuction to perform the Casteling
            // https://en.wikipedia.org/wiki/Castling
            static std::string castleable;

            // The current EnPassante Status, '-' means not possible, otherwise char/int notation -> got in move from targetFlag
            static std::string enPassante;

            // The current number of Halfmoves -> Used for weird fifty-Move rule (from 0 - 50)
            static int halfmoves;

            // The current Move-Number. Starts at 1 and then gets incremented every time Black Moves;
            static int moveNumber;

            // Move a Piece from A -> B
            void move(engine::ChessTile source, engine::ChessTile target);

            // Needed to asign char (*)[8] to char[8][8]
            void writeBoardInternaly(char (*)[8]);

            // Reset the Board to its initial State -> Only callable from friend as it changes board uncontrolled
            void reset();
        public:
            // Returns the FEN String representing the Board
            static std::string board2string(const char board[8][8]);
            // Returns an 8x8 Char grid containing the Pieces
            static char(*string2board(const std::string board))[8]; 

            // Get the current Board
            char (*getBoardArray() const)[8];
            std::string getBoardString() const;
            std::string getCastleable() const;

            ~ChessBoard();

            // Load a FEN as the current Board
            void loadFEN(std::string fen);

        friend ChessEngine;
    };

    class ChessEngine {
        private:
            ChessBoard currentBoard;

            // Nested Class to generate the Valid Moves
            struct MoveGenerator {
                private:
                    Figure* referenceMover;
                    std::map<char, std::unique_ptr<engine::Figure>> referenceMovers;
                    engine::ChessEngine* super;

                    // Check if a specific Tile is under Siege, tile for Coordinates, figure for Colour and Board for the Check
                    bool checkUnderSiege(engine::ChessTile tile, char figure, char const board[8][8]) const;

                    engine::Figure* dereferenceMovers(char const mover);
                public:
                    MoveGenerator(ChessEngine* engine);
                    ~MoveGenerator();

                    engine::ChessTile lastCheckedTile;
                    std::vector<engine::ChessTile> lastPossibleMoves;
                    std::vector<engine::ChessTile> possibleCastleMoves;

                    char checkCheck(char figure, char const board[8][8]) const;
                    char checkCheckMate(char figure, char const board[8][8]) const;

                    std::pair<engine::ChessTile, engine::ChessTile> getOpposingCastleMove(const engine::ChessTile& move) const;
                    std::vector<engine::ChessTile> getCastleMoves(char figure, char const board[8][8]) const;

                    // Check a Move by making a Pseudo-Move and check for check
                    bool checkPseudoMove(engine::ChessTile source, engine::ChessTile target, const char board[8][8]) const;

                    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8], engine::ChessTile tile);
            };
            
            MoveGenerator* moveGen;

            // Actually do the Move
            void move(const engine::ChessTile& source, const engine::ChessTile& target);

        public:
            // Reset the Board and all its Pieces -> Restart for new Game
            // Sets the currentBoard using class ChessBoard
            void reset();

            // Returns Vector of possibles moves for a specific Tile in Board
            std::vector<engine::ChessTile> getPossibleMoves(engine::ChessTile tile) const;

            // Trys to move the given Figure to the given Tile, returns success
            bool tryMove(engine::ChessTile source, engine::ChessTile target);

            // Returns the char-array of the current Board
            char (*getCurrentBoard() const)[8];

            // DEBUG ONLY
            inline void loadFEN(std::string string) {
                this->currentBoard.loadFEN(string);
            }

            inline bool checkCheck(const char& king) {
                return this->moveGen->checkCheck(king, this->currentBoard.getBoardArray());
            }

            inline bool checkCheckMate(const char& king) {
                return this->moveGen->checkCheckMate(king, this->currentBoard.getBoardArray());
            }

            ChessEngine();
            ~ChessEngine();
    };
}

#endif
#ifndef CHESS_INTERFACE_HPP
#define CHESS_INTERFACE_HPP

#include <string>
#include <vector>
#include <map>

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

            struct MoveGenerator {
                private:
                    engine::Figure* referenceMover;
                    engine::ChessEngine* super;

                    // Check if a specific Tile is under Siege, tile for Coordinates, figure for Colour and Board for the Check
                    bool checkUnderSiege(engine::ChessTile tile, char figure, char const board[8][8]) const;

                public:
                    MoveGenerator(ChessEngine* engine);
                    ~MoveGenerator();

                    engine::ChessTile lastCheckedTile;
                    std::vector<engine::ChessTile> lastPossibleMoves;

                    char checkCheck(char figure, char const board[8][8]) const;
                    char checkCheckMate() const;

                    std::vector<std::pair<engine::ChessTile, engine::ChessTile>> getCastleMoves(char figure, char const board[8][8]) const;

                    // Check a Move by making a Pseudo-Move and check for check ->
                    bool checkPseudoMove(char figure);

                    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8], engine::ChessTile tile);
            };
            
            MoveGenerator* moveGen;

            // Actually do the Move
            void move(engine::ChessTile source, engine::ChessTile target);

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

            inline bool checkCheck() {
                return this->moveGen->checkCheck('k', this->currentBoard.getBoardArray());
            }

            ChessEngine();
            ~ChessEngine();
    };
}

#endif
#ifndef CHESS_INTERFACE_HPP
#define CHESS_INTERFACE_HPP

#include <string>
#include <vector>
#include <map>

#include <iostream>

#include "chessConstants.hpp"
#include "chessTile.hpp"
#include "figure.hpp"

namespace engine {
    // Need ad Least Engine for Friend declaration and Figure
    class ChessBoard;
    class ChessEngine;
    class Figure;

    // Class that contains the actuall internal representation of the board that is beeing played 
    //    -> Provides only conversion functions from internal storage to other notation Form (Char array and FEN-String)
    //    like to the external char[8][8], that can be used much more intuitively
    class ChessBoard {
        private:
            static std::string currentBoard;
            static char arrayBoard[8][8];                                  // Not actively used to Store Board internaly, but as a static, inScope holder for string2board

            ChessBoard();                                                  // Private constructor -> Only usable in Friend (ChessEngine)

            void reset();

        public:
            // Returns the current FEN String representing the Board
            static std::string board2string(const char board[8][8]);
            // Returns an 8x8 Char grid containing the Pieces
            static char(*string2board(const std::string board))[8]; 

            // Get the current Board
            char (*getBoardArray() const)[8];
            std::string getBoardString() const;

            ~ChessBoard();

            inline void loadFEN(std::string fen) {
                this->currentBoard = fen;
            }


        friend ChessEngine;
    };

    class ChessEngine {
        private:
            ChessBoard currentBoard;

            struct MoveGenerator {
                private:
                    engine::Figure *referenceMover;
                public:
                    MoveGenerator();
                    ~MoveGenerator();

                    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8], engine::ChessTile tile);
            };
            
            MoveGenerator* moveGen;

        public:
            // Reset the Board and all its Pieces -> Restart for new Game
            // Sets the currentBoard using class ChessBoard
            void reset();

            // Returns Vector of possibles moves for a specific Tile in Board
            std::vector<ChessTile> getPossibleMoves(ChessTile tile) const;

            // Trys to move the given Figure to the given Tile, returns success
            bool tryMove(ChessTile source, ChessTile target);

            // Returns the char-array of the current Board
            char (*getCurrentBoard() const)[8];

            // DEBUG ONLY
            inline void loadFEN(std::string string) {
                this->currentBoard.loadFEN(string);
            }

            ChessEngine();
            ~ChessEngine();
    };
}

#endif
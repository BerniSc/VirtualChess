#ifndef CHESS_INTERFACE_HPP
#define CHESS_INTERFACE_HPP

#include <string>
#include <vector>
#include <map>

#include <iostream>

namespace engine {
    // Need ad Least Engine for Friend declaration
    class ChessTile;
    class ChessBoard;
    class ChessEngine;

    // Class only used for "Interfacing" with OF Application -> Through ChessEngine pos is found and returned as Tile
    //      Provides nice usability as it can output the indices as well as the actuall value (Like "A-1")
    class ChessTile {
        private:
            int x, y;
        public:
            inline ChessTile(int x, int y) : x(x), y(y) {

            };
            
            inline ChessTile(char x, int y) : x(toupper(x) - 'A'), y(y) {

            };

            // Usable array-values of the current Tile
            inline std::pair<int, int> getArrayNr() {
                std::pair<int, int> ret;
                ret.first = x;
                ret.second = y;
                return ret;
            }; 

            // i.e. "A3" or Other Chess Coordinates
            std::pair<char, int> getFieldNr() {
                std::pair<char, int> ret;
                ret.first = x + 'A';
                ret.second = y + 1;
                return ret;
            };     

    };

    // Class used to store 
    struct Figure {
        protected:
            std::vector<ChessTile> possibleMoves;

        public:
            // Current Position
            engine::ChessTile position;
            char identifier;

            virtual std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]) = 0;
            virtual void move() = 0;

            virtual ~Figure();
    };

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
            static std::string board2string(const char * const board[8]);
            // Returns an 8x8 Char grid containing the Pieces
            static char(*string2board(const std::string board))[8]; 

            // Get the current Board
            char (*getBoardArray() const)[8];
            std::string getBoardString() const;

            ~ChessBoard();

        friend ChessEngine;
    };

    class ChessEngine {
        private:
            ChessBoard currentBoard;

            // Stores the alive Figures
            std::map<char, Figure*> aliveFigures;
        public:
            // Reset the Board and all its Pieces -> Restart for new Game
            // Sets the currentBoard using class ChessBoard
            void reset();

            // Get Position of requested Figure from Map
            // Programm than can use Data to populate Board and print Position
            ChessTile getPosition(char const figure) const;

            // Returns Vector of possibles moves for a specific Figure
            std::vector<ChessTile> getPossibleMoves(char const figure) const;

            // Trys to move the given Figure to the given Tile, returns success
            bool tryMove(char const figure, ChessTile target);

            // Returns the char-array of the current Board
            char (*getCurrentBoard() const)[8];
    };
}

#endif
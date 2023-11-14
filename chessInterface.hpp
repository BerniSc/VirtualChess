#ifndef CHESS_INTERFACE_HPP
#define CHESS_INTERFACE_HPP

#include <string>
#include <vector>

namespace engine {
    // Need ad Least Engine for Friend declaration
    class ChessTile;
    class ChessBoard;
    class ChessEngine;

    // Class only used for "Interfacing" with OF Application -> Through ChessEngine pos is found and returned as Tile
    //      Provides nice usability as it can output the indices as well as the actuall value (Like "A-1")
    class ChessTile {
        private:

        public:
            std::pair<int, int> getArrayNr();       // Usable array-values of the current Tile
            std::pair<char, int> getFieldNr();      // i.e. "A3" or Other Chess Coordinates

    };

    // Class used to store 
    struct Figure {
        protected:
            std::vector<ChessTile> possibleMoves;

        public:
            // Current Position
            ChessTile position;
            char identifier;

            // Needed to determine in which direction for Example the Peasant can move
            bool startsAtTop;

            void kill(Figure* toKill);
            void getKilled();

            std::vector<ChessTile> getPossibleMoves(char const board[8][8]);

            virtual void move() = 0;
    };

    // Class that contains the actuall internal representation of the board that is beeing played 
    //    -> Provides only conversion functions from internal storage to other notation Form (Char array and FEN-String)
    //    like to the external char[8][8], that can be used much more intuitively
    class ChessBoard {
        private:
            std::string currentBoard;
            char arrayBoard[8][8];                                  // Not actively used to Store Board internaly, but as a static, inScope holder for string2board

            ChessBoard();                                           // Private constructor -> Only usable in Friend (ChessEngine)
        public:
            // Returns the current FEN String representing the Board
            std::string board2string(const char * const board[8]);
            // Returns an 8x8 Char grid containing the Pieces
            char** string2board(const std::string board); 

        friend ChessEngine;
    };

    class ChessEngine {
        private:
            ChessBoard currentBoard;
            std::vector<Figure*> aliveFigures;
        public:
            // Reset the Board and all its Pieces -> Restart for new Game
            // Sets the currentBoard using class ChessBoard
            void reset();

            // Iterate over internal String and return pos of Char as ChessTile
            // Programm than can use Data to populate Board and print Position
            ChessTile getPosition(char const figure) const;

            // Returns Vector of possibles moves for a specific Figure
            std::vector<ChessTile> getPossibleMoves(char const figure) const;
    };

}

#endif
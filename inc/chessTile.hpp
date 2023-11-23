#ifndef CHESS_TILE_HPP
#define CHESS_TILE_HPP

#include <string>

#include <iostream>

namespace engine {

    // Class only used for "Interfacing" with OF Application -> Through ChessEngine pos is found and returned as Tile
    //      Provides nice usability as it can output the indices as well as the actuall value (Like "A-1")
    class ChessTile {
        private:
            int x, y;
        public:
            inline ChessTile() : y(-1), x(-1) {

            }

            inline explicit ChessTile(int const x, int const y) : x(x), y(y) {
                
            };  
                
            inline explicit ChessTile(char const x, int const y) : x(toupper(x) - 'A'), y(y) {
                
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
                ret.first = x + 1;
                ret.second = y + 'A';
                return ret;
            };     
    };
}

#endif
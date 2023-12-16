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

            bool isCaptureMove;
            bool isCastleMove;
            bool isEnPassanteable;
            bool isEnPassante = false;

        public:
            inline ChessTile() : y(-1), x(-1), isCaptureMove(false), isCastleMove(false) {

            }

            inline explicit ChessTile(int x, int y, bool isCaptureMove = false, bool isCastleMove = false, bool isEnPassanteable = false) : x(x), y(y) {
                this->isCaptureMove = isCaptureMove;
                this->isCastleMove = isCastleMove;
                this->isEnPassanteable = isEnPassanteable;
            };  
                
            inline explicit ChessTile(char const x, int const y) : x(toupper(x) - 'A'), y(y - 1) {
                
            };

            // Usable array-values of the current Tile
            inline std::pair<int, int> getArrayNr() const {
                std::pair<int, int> ret;
                ret.first = x;
                ret.second = y;
                return ret;
            }; 

            // i.e. "A3" or Other Chess Coordinates
            std::pair<char, int> getFieldNr() const {
                std::pair<char, int> ret;
                ret.first = x + 'A';
                ret.second = y + 1;
                return ret;
            };

            inline bool getIsCaptureMove() const {
                return this->isCaptureMove;
            };

            inline bool getIsCastleMove() const {
                return this->isCastleMove;
            };

            inline bool getIsEnPassanteable() const {
                return this->isEnPassanteable;
            };

            inline bool getIsEnPassante() const {
                return this->isEnPassante;
            };

            inline void setIsEnPassante(bool isEnPassante) {
                this->isEnPassante = isEnPassante;
            }

            friend bool operator!=(const ChessTile& lhs, const ChessTile& rhs);   
            friend bool operator==(const ChessTile& lhs, const ChessTile& rhs);  
    };

    inline bool operator!=(const ChessTile& lhs, const ChessTile& rhs) {
        bool ret;
        if(lhs.x == rhs.x && lhs.y == rhs.y)
            ret = false;
        else
            ret = true;
        
        return ret;
    }

    inline bool operator==(const ChessTile& lhs, const ChessTile& rhs) {
        bool ret;
        if(lhs.x == rhs.x && lhs.y == rhs.y)
            ret = true;
        else
            ret = false;
        
        return ret;
    }
}

#endif
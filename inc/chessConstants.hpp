#ifndef CHESS_CONSTANTS_HPP
#define CHESS_CONSTANTS_HPP

namespace constants {
    // Black pieces
    constexpr inline char rook = 'r';
    constexpr inline char knight = 'n';
    constexpr inline char bishop = 'b';
    constexpr inline char queen = 'q';
    constexpr inline char king = 'k';
    constexpr inline char pawn = 'p';

    // White Pieces
    constexpr inline char ROOK = 'R';
    constexpr inline char KNIGHT = 'N';
    constexpr inline char BISHOP = 'B';
    constexpr inline char QUEEN = 'Q';
    constexpr inline char KING = 'K';
    constexpr inline char PAWN = 'P';

    // Whose turn is it
    // Can be same as Bishop as it is distinct by the Position it is placed at in the Proctocoll
    constexpr inline char turnBlack = 'b';
    constexpr inline char turnWhite = 'w';

    // TODO consider alternative notation like: 0-6 Type and 8&16 for Colour -> Binary Conversion easy
}

#endif
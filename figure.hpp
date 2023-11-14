#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <vector>

#include "chessInterface.hpp"

using engine::ChessTile;

struct Figure {
    // Current Position
    ChessTile position;

    // Needed to determine in which direction for Example the Peasant can move
    bool startsAtTop;

    std::vector<ChessTile> possibleMoves;

    void kill(Figure* toKill);
    void getKilled();

    virtual void move() = 0;
};

#endif
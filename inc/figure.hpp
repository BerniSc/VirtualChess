#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <vector>

#include "chessInterface.hpp"

using engine::Figure;

struct Pawn : public Figure {
    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]);
    void move();
};

struct King : public Figure {
    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]);
    void move();
};

struct Queen : public Figure {

};

struct Bishop : public Figure {

};

struct Knight : public Figure {

};

struct Rook : public Figure {

};



#endif
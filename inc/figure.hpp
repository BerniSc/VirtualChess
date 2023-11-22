#ifndef Figure_HPP
#define Figure_HPP

#include <vector>

#include "chessTile.hpp"

namespace engine {
    struct Figure {
        protected:
            // Current Position
            engine::ChessTile position;
            char identifier;

        public:
            virtual std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]) = 0;

            virtual ~Figure();
    };
}

struct Pawn : public engine::Figure {
    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]) override;

    Pawn(engine::ChessTile position, char identifier);
};

struct King : public engine::Figure {
    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]) override;

    King(engine::ChessTile position, char identifier);
};

struct Queen : public engine::Figure {
    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]) override;

    Queen(engine::ChessTile position, char identifier);
};

struct Bishop : public engine::Figure {
    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]) override;

    Bishop(engine::ChessTile position, char identifier);
};

struct Knight : public engine::Figure {
    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]) override;

    Knight(engine::ChessTile position, char identifier);
};

struct Rook : public engine::Figure {
    std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]) override;

    Rook(engine::ChessTile position, char identifier);
};



#endif
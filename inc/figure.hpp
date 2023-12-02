#ifndef Figure_HPP
#define Figure_HPP

#include <vector>

#include "chessTile.hpp"
#include "chessInterface.hpp"

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
    // Provides a way of knowing wether the Pawn is a true Pawn or a Fake Pawn (Emulated by King for Checking Check) -> King sets FakePawn 
    //  -> Special Moves that depend on the Pawn Position are Prohibited -> TODO Use
    bool fakePawn = false;

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
    private:
        // Set an array of possible Knight Moves and check them one by one
        // First all on the right Side, then on the left Side
        int const knightMoveVectors[8][2] = {
            {1, 2}, {2, 1}, {2, -1}, {1, -2},
            {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
        };
    public:
        std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]) override;

        Knight(engine::ChessTile position, char identifier);
};

struct Rook : public engine::Figure {
    private:
        std::string castleable;

    public:
        std::vector<engine::ChessTile> getPossibleMoves(char const board[8][8]) override;

        Rook(engine::ChessTile position, char identifier);
};



#endif
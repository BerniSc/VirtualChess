#ifndef CHESS_TESTER_HPP
#define CHESS_TESTER_HPP

#include <string>
#include <iostream>

#include <sstream>

#include "chessInterface.hpp"

struct ChessTester {
    private:
        void parseAndMove(std::string input);
    public:
        engine::ChessEngine& engine;

        ChessTester(engine::ChessEngine&);

        void printBoard(char(*board)[8]);
        void printBoard(std::string board);

        void printBoardWithHighlights(char(* board)[8], const std::vector<engine::ChessTile>& highlights);

        void runMovementTestConsole();

        void testRook();
        void testKnight();
        void testBishop();
        void testQueen();
        void testPawn();

        void testCastling();

        void printPos(engine::ChessTile tile);
};

#endif
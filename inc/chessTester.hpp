#ifndef CHESS_TESTER_HPP
#define CHESS_TESTER_HPP

#include <string>
#include <iostream>

#include "chessInterface.hpp"

struct ChessTester {
    engine::ChessEngine& engine;

    ChessTester(engine::ChessEngine&);

    void printBoard(char(*board)[8]);
    void printBoard(std::string board);

    void printBoardWithHighlights(char(* board)[8], const std::vector<engine::ChessTile>& highlights);

    void testRook();
    void testKnight();
    void testBishop();
    void testQueen();
    void testPawn();

    void printPos(engine::ChessTile tile);
};

#endif
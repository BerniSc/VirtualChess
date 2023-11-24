#include <memory>

#include "inc/chessInterface.hpp"
#include "inc/chessTester.hpp"
#include "inc/figure.hpp"

int main(int argc, char** argv) {
    engine::ChessEngine virtualChessEngine;

    std::unique_ptr<ChessTester> tester;
    tester = std::unique_ptr<ChessTester>(new ChessTester(virtualChessEngine));

    tester->printBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    virtualChessEngine.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    tester->printBoard(engine::ChessBoard::board2string(virtualChessEngine.getCurrentBoard()));

    
    std::vector<engine::ChessTile> test;
    std::cout << "\n===\n";
    // Load Rook TestMovement
    virtualChessEngine.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/8/R3K2R");
    tester->printBoard(engine::ChessBoard::board2string(virtualChessEngine.getCurrentBoard()));
    test = virtualChessEngine.getPossibleMoves(engine::ChessTile(0,1));
    tester->printBoardWithHighlights(virtualChessEngine.getCurrentBoard(), test);
    test = virtualChessEngine.getPossibleMoves(engine::ChessTile(0,7));
    tester->printBoardWithHighlights(virtualChessEngine.getCurrentBoard(), test);
    // Load Bishop TestMovement
    virtualChessEngine.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/8/2BK2R");
    tester->printBoard(engine::ChessBoard::board2string(virtualChessEngine.getCurrentBoard()));
    test = virtualChessEngine.getPossibleMoves(engine::ChessTile(2,7));
    tester->printBoardWithHighlights(virtualChessEngine.getCurrentBoard(), test);
    

    
    
    //tester->printBoard("8/8/8/8/4P3/8/8/8 w - - 0 1");
    //tester->printBoard("8/8/8/3Q4/3N4/8/8/8 b - - 0 1");
    //tester->printBoard("rnbqkbnr/pppppppp/8/8/4P3/5N2/PPPP1PPP/R1BQKBNR b KQkq - 1 2");

    return 0;
}
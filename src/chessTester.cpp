#include "chessTester.hpp"

ChessTester::ChessTester(engine::ChessEngine& engine) : engine(engine) {

}

void ChessTester::printBoard(char(* board)[8]) {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            std::cout << (board[col][row] == 0 ? '.' : board[col][row]);
        }
        std::cout << "\n";
    }
}

void ChessTester::printBoard(std::string board) {
    std::cout << "FEN: " << board << std::endl;
    printBoard(engine::ChessBoard::string2board(board));
}

void ChessTester::printBoardWithHighlights(char(* board)[8], const std::vector<engine::ChessTile>& highlights) {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            // Check if the current position is in the vector of highlights
            bool isHighlighted = false;
            bool isCaptureMove = false;
            for(const auto& tile : highlights) {
                std::pair<int, int> pos = tile.getArrayNr();
                if(pos.first == col && pos.second == row) {
                    isHighlighted = true;
                    isCaptureMove = tile.getIsCaptureMove();
                    break;
                }
            }

            // Print in green if highlighted, otherwise print normally
            if(isHighlighted) {
                // Print all CaptureMoves red and Free Moves green
                if(!isCaptureMove)
                    std::cout << "\033[32m" << (board[col][row] == 0 ? '*' :  board[col][row]) << "\033[0m";
                else
                    std::cout << "\033[31m" << (board[col][row] == 0 ? '*' :  board[col][row]) << "\033[0m";
            } else {
                std::cout << (board[col][row] == 0 ? '*' :  board[col][row]);
            }
        }
        std::cout << "\n";
    }
}

void ChessTester::parseAndMove(std::string input) {
    std::istringstream iss(input);

    int fromRow, fromCol, toRow, toCol;

    std::string sep;

    // Assuming the input format is "fromRow fromCol - toRow toCol"
    //if(!(iss >> fromCol >> fromRow >> std::ws >> std::skipws >> sep >> std::ws >> std::skipws >> toCol >> toRow)) {
    if(!(iss >> fromCol >> fromRow >> toCol >> toRow)) {
        std::cerr << "Invalid input format. Expected: fromRow fromCol - toRow toCol" << std::endl;
        return;
    }

    // Make a move using the ChessEngine
    engine::ChessTile src(fromCol, fromRow);
    engine::ChessTile trg(toCol, toRow);
    std::vector<engine::ChessTile> test = engine.getPossibleMoves(src); 
    this->engine.tryMove(src, trg);    

    this->printBoardWithHighlights(this->engine.getCurrentBoard(), test);
}


void ChessTester::runMovementTestConsole() {
    std::string input;

    while(true) {
        // Read user input
        std::cout << "Enter move (or 'quit' to exit): ";
        std::getline(std::cin, input);

        // Check if the user wants to quit
        if (input == "quit") {
            std::cout << "Exiting continuous test." << std::endl;
            break;
        }

        // Parse and make the move
        parseAndMove(input);

        std::cout << (engine.checkCheck() ? "true" : "false") << "\n";

        // Print the updated board or any other information
        // depending on your requirements
        // printBoard(...);
    }
}

void ChessTester::testRook() {
    // Rook can move in all directions, capture and get hindered by own figures
    std::string testFENPos1 = "r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1";
    std::string testFENPos2 = "r1bqkbnr/1pp1pppp/2n5/8/2PpP3/7p/PP3PP1/RNBQKBNR b KQkq - 0 4";

    std::vector<engine::ChessTile> tmp;
    
    this->engine.loadFEN(testFENPos1);
    tmp = engine.getPossibleMoves(engine::ChessTile(0,0));
    printBoardWithHighlights(this->engine.getCurrentBoard(), tmp);
    if(tmp.size() != 3) throw std::runtime_error("Assertation Rook pos1-1 failed");
    tmp = engine.getPossibleMoves(engine::ChessTile(7,7));
    printBoardWithHighlights(this->engine.getCurrentBoard(), tmp);
    if(tmp.size() != 2) throw std::runtime_error("Assertation Rook pos1-2 failed");

    this->engine.loadFEN(testFENPos2);
    tmp = engine.getPossibleMoves(engine::ChessTile(0,0));
    printBoardWithHighlights(this->engine.getCurrentBoard(), tmp);
    if(tmp.size() != 7) throw std::runtime_error("Assertation Rook pos2-1 failed");
    tmp = engine.getPossibleMoves(engine::ChessTile(7,7));
    printBoardWithHighlights(this->engine.getCurrentBoard(), tmp);
    if(tmp.size() != 2) throw std::runtime_error("Assertation Rook pos2-2 failed");
}

void ChessTester::testKnight() {
    // Knight can move in all directions, capture and get hindered by own figures
    std::string testFENPos1 = "rnbqkbnr/pppppppp/8/4N3/8/3N4/8/2BK2R";
    std::string testFENPos2 = "r1bqkbnr/1pp1pppp/2n5/8/2PpP3/7p/PP3PP1/RNBQKBNR b KQkq - 0 4";

    std::vector<engine::ChessTile> tmp;
    
    this->engine.loadFEN(testFENPos1);
    tmp = engine.getPossibleMoves(engine::ChessTile(4,3));
    printBoardWithHighlights(this->engine.getCurrentBoard(), tmp);
    if(tmp.size() != 7) throw std::runtime_error("Assertation Knight pos1-1 failed");
    tmp = engine.getPossibleMoves(engine::ChessTile(6,0));
    printBoardWithHighlights(this->engine.getCurrentBoard(), tmp);
    if(tmp.size() != 2) throw std::runtime_error("Assertation Knight pos1-2 failed");

    this->engine.loadFEN(testFENPos2);
    tmp = engine.getPossibleMoves(engine::ChessTile(2,2));
    printBoardWithHighlights(this->engine.getCurrentBoard(), tmp);
    if(tmp.size() != 5) throw std::runtime_error("Assertation Knight pos2-1 failed");
    tmp = engine.getPossibleMoves(engine::ChessTile(1,7));
    printBoardWithHighlights(this->engine.getCurrentBoard(), tmp);
    if(tmp.size() != 3) throw std::runtime_error("Assertation Knight pos2-2 failed");
}

void ChessTester::testBishop() {
    // Bishop can move diagonally, capture, and get hindered by own figures
    std::string testFENPos1 = "8/8/8/8/3B4/8/8/8 w - - 0 1";
    std::string testFENPos2 = "rnbqkbnr/pppppppp/8/8/8/RNBQKBNR/8/8 w KQkq - 0 1";

    std::vector<engine::ChessTile> tmp;

    this->engine.loadFEN(testFENPos1);
    tmp = engine.getPossibleMoves(engine::ChessTile(3, 4));  
    printBoardWithHighlights(this->engine.getCurrentBoard(), tmp);
    if (tmp.size() != 13) throw std::runtime_error("Assertation Bishop pos1-1 failed");

    this->engine.loadFEN(testFENPos2);
    tmp = engine.getPossibleMoves(engine::ChessTile(2, 5));
    printBoardWithHighlights(this->engine.getCurrentBoard(), tmp);
    if (tmp.size() != 10) throw std::runtime_error("Assertation Bishop pos2-1 failed");
}


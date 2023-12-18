#ifndef UCI_MOVES_HPP
#define UCI_MOVES_HPP

#include "chessConstants.hpp"

#ifdef AI_MOVES_BLACK

#include "chessInterface.hpp"

#include <iostream>
#include <boost/process.hpp>

namespace bp = boost::process;

typedef std::pair<engine::ChessTile, engine::ChessTile> MOVE;

namespace engine {
    struct UCI_AI {
        private:
            bp::ipstream pipe_stream_out;
            bp::opstream pipe_stream_in;

            const char* cmd = "/usr/bin/python3 /home/berni/Uni/Inf2_2/VirtualChess/scripts/uci_ai.py";

            bp::child child;

        public:
            inline UCI_AI() {
                child = bp::child(cmd, bp::std_out > pipe_stream_out, bp::std_in < pipe_stream_in);
            }

            inline ~UCI_AI() {
                child.terminate();
            }

            MOVE inline getBestMove(const std::string& fen) {
                engine::ChessTile src, trg;

                // Lambda to Send a message to the child process and print the response
                auto sendMessage = [&](const std::string& message) {
                    // Send a message to the child process
                    pipe_stream_in << message << std::endl;
                    pipe_stream_in.flush();

                    // Read the response from the child process
                    std::string response;
                    std::getline(pipe_stream_out, response);

                    // Print the response
                    std::cout << "Received from child process: " << response << std::endl;
                    src = engine::ChessTile(response[0], response[1] - '0');
                    trg = engine::ChessTile(response[2], response[3] - '0');
                    std::cout << "Move " << src.getArrayNr().first << "|" << src.getArrayNr().second << " to " << trg.getArrayNr().first << "|" << trg.getArrayNr().second << "\n";
                };

                sendMessage(fen);

                return MOVE(src, trg);
            }
    };
}

#endif

#endif
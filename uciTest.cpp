#include <iostream>
#include <boost/process.hpp>

namespace bp = boost::process;

int main() {
    bp::ipstream pipe_stream;
    bp::opstream pipe_stream_in;

    //bp::child child("/bin/cat", bp::std_out > pipe_stream, bp::std_in < pipe_stream_in);

    bp::child child("/usr/bin/python3 uciTest.py", bp::std_out > pipe_stream, bp::std_in < pipe_stream_in);

    // Send a message to the child process and print the response
    auto sendMessage = [&](const std::string& message) {
        // Send a message to the child process
        pipe_stream_in << message << std::endl;
        pipe_stream_in.flush();

        // Read the response from the child process
        std::string response;
        std::getline(pipe_stream, response);

        // Print the response
        std::cout << "Received from child process: " << response << std::endl;
    };

    // Main loop for sending messages and receiving responses
    while(true) {
        std::string userMessage;
        std::cout << "Enter a message (or 'exit' to quit): ";
        std::getline(std::cin, userMessage);

        if(userMessage == "exit") {
            break;
        }

        sendMessage(userMessage);
    }

    // Wait for the child process to finish
    child.wait();

    return 0;
}

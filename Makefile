COMPILER = "g++"
PROJECTNAME = bin/chessEngine
SOURCE = main.cpp src/chessBoard.cpp src/chessEngine.cpp src/chessTester.cpp src/utility.cpp
# SOURCE = uciTest.cpp
FLAGS = -std=c++17 -pthread

$(PROJECTNAME) : $(SOURCE)
		$(COMPILER) $(SOURCE) $(FLAGS) -I./inc -o $(PROJECTNAME)

.PHONY: clean run
clean:
		rm chessEngine

run:
		./$(PROJECTNAME)
COMPILER = "g++"
PROJECTNAME = chessEngine
SOURCE = main.cpp chessBoard.cpp utility.cpp
FLAGS = -std=c++17 -pthread

$(PROJECTNAME) : $(SOURCE)
		$(COMPILER) $(SOURCE) $(FLAGS) -I. -o $(PROJECTNAME)

.PHONY: clean
clean:
		rm chessEngine
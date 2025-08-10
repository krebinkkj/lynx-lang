CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: lynx

lynx: src/main.cpp src/Lexer.cpp src/Parser.cpp src/Evaluator.cpp
	$(CXX) $(CXXFLAGS) -o bin/lynx src/main.cpp src/Lexer.cpp src/Parser.cpp src/Evaluator.cpp

.PHONY: clean

clean:
	rm -f bin/lynx
	rm -rf bin/
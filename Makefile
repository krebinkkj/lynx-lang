CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: lynx

lynx: src/main.cpp
	$(CXX) $(CXXFLAGS) -o bin/lynx src/main.cpp src/Lexer.cpp

.PHONY: clean

clean:
	rm -f bin/lynx
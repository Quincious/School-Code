CXX=g++

all: debug game

debug: debug.cpp
	$(CXX) debug.cpp -o debug

game: main.cpp life.cpp life.h
	$(CXX) main.cpp life.cpp -o game

clean: 
	rm -f debug game

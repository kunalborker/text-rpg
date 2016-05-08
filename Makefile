CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -W -pedantic

game: main.o guy.o grid.o ui.o
	$(CXX) -o game main.o guy.o grid.o ui.o

main.o: main.cpp guy.h grid.h ui.h

guy.o: guy.cpp guy.h grid.h ui.h

grid.o: grid.cpp grid.h

ui.o: ui.cpp ui.h grid.h guy.h

clean:
	rm -f *.o game

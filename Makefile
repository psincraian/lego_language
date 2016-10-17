CPPFLAGS= -std=c++11

main: Block Board
	g++ $(CPPFLAGS) -c main.cpp Block.hpp Board.hpp
	g++ -o main main.o Block.o Board.o

Block: Block.cpp Block.hpp
	g++ $(CPPFLAGS) -c Block.cpp

Board: Board.hpp Board.cpp
	g++ $(CPPFLAGS) -c Board.cpp

clean:
	rm *.o *.gch

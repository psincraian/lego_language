CPPFLAGS= -std=c++11

lego: lego.g parser.dlg scan.c Board Block
	antlr -gt lego.g && dlg -ci parser.dlg scan.c && g++ $(CPPFLAGS) -Wno-write-strings -o lego Board.o Block.o lego.c scan.c err.c -I /home/soft/PCCTS_v1.33/include

Block: Block.cpp Block.hpp
	g++ $(CPPFLAGS) -c Block.cpp

Board: Board.hpp Board.cpp
	g++ $(CPPFLAGS) -c Board.cpp

Interpreter: Interpreter.hpp Interpreter.cpp
	g++ $(CPPFLAGS) -c Interpreter.cpp;

clean:
	rm *.o *.gch

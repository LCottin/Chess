all : main.o Board.o Game.o Piece.o Player.o
	g++ main.o Board.o Game.o Piece.o Player.o -o main -std=c++17 -lsfml-graphics -lsfml-system -lsfml-window -Wall

Game.o : Game.cpp Game.hpp
	g++ -std=c++17 -Wall -c Game.cpp

Player.o : Player.cpp Player.hpp
	g++ -std=c++17 -Wall -c Player.cpp

main.o : main.cpp
	g++ -std=c++17 -lsfml-graphics -lsfml-system -lsfml-window -Wall -c main.cpp

Piece.o : Piece.cpp Piece.hpp
	g++ -std=c++17 -Wall -c Piece.cpp

Board.o : Board.cpp Board.hpp
	g++ -std=c++17 -Wall -c Board.cpp

clean:
	rm -rf *.o
	rm main
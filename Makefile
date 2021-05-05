CC = g++
FLAGS = -std=c++17 -Wall
SFML = -lsfml-graphics -lsfml-system -lsfml-window
EXEC = main

SOURCES = 	main.cpp 			\
			Game.cpp 			\
			Player.cpp 			\
			Piece.cpp 			\
			Board.cpp 			\
			Pieces/Pawn.cpp 	\
			Pieces/Rook.cpp 	\
			Pieces/King.cpp 	\
			Pieces/Queen.cpp 	\
			Pieces/Bishop.cpp 	\
			Pieces/Knight.cpp   \
			Display.cpp


OBJECTS = $(SOURCES:.cpp=.o)

all : $(OBJECTS)
	$(CC) $(OBJECTS) $(FLAGS) $(SFML) -o $(EXEC) 

Display.o : Display.cpp
	$(CC) $(FLAGS) -c $^
	
Game.o : Game.cpp 
	$(CC) $(FLAGS) -c $^

Player.o : Player.cpp 
	$(CC) $(FLAGS) -c $^

main.o : main.cpp
	$(CC) $(FLAGS) -c $^

Piece.o : Piece.cpp 
	$(CC) $(FLAGS) -c $^

Board.o : Board.cpp 
	$(CC) $(FLAGS) -c $^

Pawn.o : Pieces/Pawn.cpp 
	$(CC) $(FLAGS) -c $^ -lm

Rook.o : Pieces/Rook.cpp 
	$(CC) $(FLAGS) -c $^ -lm

Bishop.o : Pieces/Bishop.cpp 
	$(CC) $(FLAGS) -c $^ -lm

Knight.o : Pieces/Knight.cpp 
	$(CC) $(FLAGS) -c $^ -lm

King.o : Pieces/King.cpp 
	$(CC) $(FLAGS) -c $^ -lm

Queen.o : Pieces/Queen.cpp 
	$(CC) $(FLAGS) -c $^ -lm

clean:
	rm -rf *.o
	rm -rf Pieces/*.o
	rm $(EXEC)

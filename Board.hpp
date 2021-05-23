#ifndef __BOARD__
#define __BOARD__

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Piece.hpp"

using namespace std;
using namespace sf;

class Board
{
    private:
        const int _SizeX = 8;
        const int _SizeY = 8;

        int** _Board; //board to play

    public:
        Board();
        void printBoard() const;
        void setBoard(const Vector2i to, const bool whiteTurn);
        void updateBoard(const Vector2i from, const Vector2i to, const bool whiteTurn);
        bool collisionCheck(const Vector2i from, const Vector2i to, const int type, const bool whiteTurn) const;
        int  getPiece(const Vector2i pos) const;
        ~Board();
};

extern Board _Board;

#endif
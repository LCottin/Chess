#ifndef __BOARD__
#define __BOARD__

#include <iostream>
#include <string>
#include "Piece.hpp"

using namespace std;

class Board
{
    private:
        const int _SizeX = 8;
        const int _SizeY = 8;

        int** _Board; //board to play

    public:
        Board();
        void printBoard() const;
        void updateBoard(const int oldX, const int oldY, const int newX, const int newY, const bool whiteTurn);
        //void setPiece(const Piece &piece);
        //void setPiece(const int x, const int y, const int value);
        bool collisionCheck(const int oldX, const int oldY, const int newX, const int newY, const int type, const bool whiteTurn) const;
        int  getPiece(const int x, const int y) const;
        ~Board();
};

extern Board _Board;

#endif
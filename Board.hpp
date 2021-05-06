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
        int** _InitBoard; //Initial board with black and white tiles

    public:
        Board();
        void printBoard(const bool printInit) const;
        int getInitPiece(const int x, const int y) const;
        void setPiece(const Piece &piece);
        void setPiece(const int x, const int y, const int value);
        int getPiece(const int x, const int y) const;
        ~Board();
};

static Board* _Board = new Board();

#endif
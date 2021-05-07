#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <string>
#include <vector>

#include "Board.hpp"
#include "Piece.hpp"
#include "Pieces/Bishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Rook.hpp"
#include "Pieces/Pawn.hpp"

using namespace std;

class Player
{
    private:
        string  _Pseudo;
        bool    _IsWhite;
        bool    _IsCheck;
        vector  <Piece*> _Pieces;

    public:
        Player(const string name, const bool white);
        int     getSize() const;
        bool    isCheck() const;
        void    setCheck(const bool isCheck);
        string  getName() const;
        void    play(const int oldX, const int oldY, const int nnewX, const int newY) const;
        Piece*  getPiece(const int x, const int y) const;
        void    play(const int oldX, const int oldY, const int newX, const int newY) const;
        ~Player();
};



#endif

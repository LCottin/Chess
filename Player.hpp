#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <string>
#include <vector>

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

        King*           _King;
        Queen*          _Queen;
        vector<Pawn*>   _Pawn;
        vector<Rook*>   _Rook;
        vector<Knight*> _Knight;
        vector<Bishop*> _Bishop;

    public:
        Player(const string name, const bool white);
        int     getSize() const;
        bool    isCheck() const;
        void    setCheck(const bool isCheck);
        string  getName() const;
        ~Player();
};



#endif

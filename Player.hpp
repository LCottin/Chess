#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <string>
#include <vector>

#include "Piece.hpp"

using namespace std;

class Player
{
    private:
        string          _Pseudo;
        bool            _IsWhite;
        vector<Piece*>  _Set;

    public:
        Player(const string name, const bool white);
        int getSize() const;

        ~Player();
};



#endif

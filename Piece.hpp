#ifndef __PIECE__
#define __PIECE__

#include "TYPES.hpp"

class Piece
{
    protected:
        int         _X;
        int         _Y;
        enum TYPES  _Type;
        bool        _IsAlive;
        bool        _IsWhite;   //Color (True = White, False = black)
        bool        _IsSelected; 

    public:
        Piece(const bool white);
        void    move(const int x, const int y);
        int     getX() const;
        int     getY() const;
        int     getType() const;
        bool    isAlive() const;
        virtual bool isMoveValid(const int x, const int y) const = 0;
        ~Piece();
};

#endif
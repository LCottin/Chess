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

    public:
        Piece(const bool white);
        void            move(const int x, const int y);
        int             getX() const;
        int             getY() const;
        virtual int     getType() const = 0;
        bool            isAlive() const;
        void            kill();
        virtual bool    isMoveValid(const int x, const int y, const bool attacking = 0) = 0;
        virtual ~Piece() = 0;
};

#endif
#ifndef __KNIGHT__
#define __KNIGHT__

#include "../Piece.hpp"
#include "../TYPES.hpp"
#include <math.h>

class Knight : public Piece
{
    private:

    public:
        Knight(const bool white);
        bool isMoveValid(const int x, const int y, const bool attacking);
        ~Knight();
};


#endif
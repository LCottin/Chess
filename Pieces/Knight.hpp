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
        bool isMoveValid(const Vector2i destination, const bool attacking);
        int  getType() const;
        ~Knight();
};


#endif
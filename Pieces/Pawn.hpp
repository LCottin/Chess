#ifndef __PAWN__
#define __PAWN__

#include "../Piece.hpp"
#include "../TYPES.hpp"
#include <math.h>

class Pawn : public Piece
{
    private:

    public:
        Pawn(const bool white);
        bool isMoveValid(const int x, const int y) const;
        ~Pawn();
};


#endif
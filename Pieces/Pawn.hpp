#ifndef __PAWN__
#define __PAWN__

#include "../Piece.hpp"
#include "../TYPES.hpp"
#include <math.h>

class Pawn : public Piece
{
    private:
        bool _FirstMove;

    public:
        Pawn(const bool white);
        bool isMoveValid(const Vector2i destination, const bool attacking);
        int  getType() const;
        ~Pawn();
};


#endif
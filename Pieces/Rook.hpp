#ifndef __ROOK__
#define __ROOK__

#include "../Piece.hpp"
#include "../TYPES.hpp"
#include <math.h>

class Rook : public Piece
{
    private:

    public:
        Rook(const bool white);
        bool isMoveValid(const Vector2i destination, const bool attacking);
        int  getType() const;
        ~Rook();
};


#endif
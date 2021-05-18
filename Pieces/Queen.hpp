#ifndef __QUEEN__
#define __QUEEN__

#include "../Piece.hpp"
#include "../TYPES.hpp"
#include <math.h>

class Queen : public Piece
{
    private:

    public:
        Queen(const bool white);
        bool isMoveValid(const Vector2i destination, const bool attacking);
        int  getType() const;
        ~Queen();
};


#endif
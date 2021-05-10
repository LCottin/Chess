#ifndef __BISHOP__
#define __BISHOP__

#include "../Piece.hpp"
#include "../TYPES.hpp"
#include <math.h>

class Bishop : public Piece
{
    private:

    public:
        Bishop(const bool white);
        bool isMoveValid(const int x, const int y, const bool attacking);
        int  getType() const;
        ~Bishop();
};


#endif
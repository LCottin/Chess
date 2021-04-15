#ifndef __KING__
#define __KING__

#include "../Piece.hpp"
#include "../TYPES.hpp"
#include <math.h>

class King : public Piece
{
    private:
        bool _IsCheckmate;
        
    public:
        King(const bool white);
        bool isMoveValid(const int x, const int y) const;
        ~King();
};


#endif
#include "Queen.hpp"

Queen::Queen(const bool white) : Piece(white)
{
    if(_IsWhite) _Type = W_QUEEN;
    else          _Type = B_QUEEN;
}

/**
 * Indicates ifmoving to the given position is possible
 * @param x,y possible position
 * @returns true ifthe move is possible, else false
 */
bool Queen::isMoveValid(const int x, const int y, const bool attacking)
{
    int dx = (x - _X);
    int dy = (y - _Y);

    //ifthe piece doesn't move
    if(abs(dx) == 0 && abs(dy) == 0) return false;
    
    //Queen can move both like a rook and a bishop
    //only x or y should change, not both
    if(abs(dx) != 0 && abs(dy) != 0)
        if(abs(dx) != abs(dy))
            return false;

    //default
    return true;
}

Queen::~Queen()
{
    
}
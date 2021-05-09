#include "Queen.hpp"

Queen::Queen(const bool white) : Piece(white)
{
    if(_IsWhite) _Type = W_QUEEN;
    else         _Type = B_QUEEN;
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool Queen::isMoveValid(const int x, const int y, const bool attacking)
{
    int dx = abs(x - _X);
    int dy = abs(y - _Y);

    //if the piece doesn't move
    if(dx == 0 && dy == 0) return false;
    
    //Queen can move both like a rook and a bishop
    //only x or y should change, not both
    if(dx != 0 && dy != 0)
        if(dx != dy)
            return false;

    //default
    return true;
}

Queen::~Queen()
{
    
}
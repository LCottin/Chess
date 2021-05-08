#include "Rook.hpp"

Rook::Rook(const bool white) : Piece(white)
{
    if(_IsWhite) _Type = W_ROOK;
    else          _Type = B_ROOK;
}

/**
 * Indicates ifmoving to the given position is possible
 * @param x,y possible position
 * @returns true ifthe move is possible, else false
 */
bool Rook::isMoveValid(const int x, const int y, const bool attacking)
{
    int dx = (x - _X);
    int dy = (y - _Y);

    //ifthe piece doesn't move
    if(abs(dx) == 0 && abs(dy) == 0) return false;
    
    //only x or y should change, not both
    if(abs(dx) != 0 && abs(dy) != 0) return false;

    //default
    return true;
}

Rook::~Rook()
{
    
}
#include "Knight.hpp"

Knight::Knight(const bool white) : Piece(white)
{
    if(_IsWhite) _Type = W_KNIGHT;
    else          _Type = B_KNIGHT;
}

/**
 * Indicates ifmoving to the given position is possible
 * @param x,y possible position
 * @returns true ifthe move is possible, else false
 */
bool Knight::isMoveValid(const int x, const int y, const bool attacking)
{
    int dx = (x - _X);
    int dy = (y - _Y);

    //ifthe piece doesn't move
    if(abs(dx) == 0 && abs(dy) == 0) return false;
    
    //knight can move one tile horizontally and two tiles vertically
    if(abs(dx) + abs(dy) != 3)   return false;
    if(abs(dx) > 2)         return false;
    if(abs(dy) > 2)         return false;

    //default
    return true;
}

Knight::~Knight()
{
    
}
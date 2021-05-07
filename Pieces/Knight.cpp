#include "Knight.hpp"

Knight::Knight(const bool white) : Piece(white)
{
    if (_IsWhite) _Type = W_KNIGHT;
    else          _Type = B_KNIGHT;
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool Knight::isMoveValid(const int x, const int y, const bool attacking)
{
    int dx = abs(_X - x);
    int dy = abs(_Y - y);

    //if the piece doesn't move
    if (dx == 0 && dy == 0) return false;
    
    //knight can move one tile horizontally and two tiles vertically
    if (dx + dy != 3)   return false;
    if (dx > 2)         return false;
    if (dy > 2)         return false;

    //default
    return true;
}

Knight::~Knight()
{
    
}
#include "Bishop.hpp"

Bishop::Bishop(const bool white) : Piece(white)
{
    if(_IsWhite) _Type = W_BISHOP;
    else          _Type = B_BISHOP;
}

/**
 * Indicates ifmoving to the given position is possible
 * @param x,y possible position
 * @returns true ifthe move is possible, else false
 */
bool Bishop::isMoveValid(const int x, const int y, const bool attacking)
{
    int dx = (x - _X);
    int dy = (y - _Y);

    //ifthe piece doesn't move
    if(abs(dx) == 0 && abs(dy) == 0) return false;

    //x and y should change together with the same value
    if(abs(dx) != abs(dy)) return false;

    //default
    return true;
}

Bishop::~Bishop()
{
    
}
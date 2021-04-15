#include "Queen.hpp"

Queen::Queen(const bool white) : Piece(white)
{
    if (_IsWhite) _Type = W_QUEEN;
    else          _Type = B_QUEEN;
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool Queen::isMoveValid(const int x, const int y) const
{
    int dx = abs(_X - x);
    int dy = abs(_Y - y);

    //if the piece doesn't move
    if (dx == 0 && dy == 0) return true;
    
    //Queen can move both like a rook and a bishop

    //default
    return true;
}

Queen::~Queen()
{
    
}
#include "Rook.hpp"

Rook::Rook(const bool white) : Piece(white)
{
    if (_IsWhite) _Type = W_ROOK;
    else          _Type = B_ROOK;
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool Rook::isMoveValid(const int x, const int y) const
{
    int dx = abs(_X - x);
    int dy = abs(_Y - y);

    //if the piece doesn't move
    if (dx == 0 && dy == 0) return true;
    
    //only x or y should change, not both
    if (dx != 0 && dy != 0) return false;

    //default
    return true;
}

Rook::~Rook()
{
    
}
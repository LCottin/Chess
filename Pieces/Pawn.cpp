#include "Pawn.hpp"

Pawn::Pawn(const bool white) : Piece(white)
{
    if (_IsWhite) _Type = W_PAWN;
    else          _Type = B_PAWN;

    _FirstMove = true;
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool Pawn::isMoveValid(const int x, const int y) const
{
    int dx = abs(_X - x);
    int dy = abs(_Y - y);

    //if the piece doesn't move
    if (dx == 0 && dy == 0) return true;
    
    //on first move, pawn can move two tiles forward
    if (_FirstMove && dx > 2) return false;

    //otherwise, only one tile forward is allowed
    if (dx  > 1) return false;

    //Y tile should not change
    if (dy != 0) return false;

    //default
    return true;
}

Pawn::~Pawn()
{

}
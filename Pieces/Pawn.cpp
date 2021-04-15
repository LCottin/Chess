#include "Pawn.hpp"


Pawn::Pawn(const bool white = 1) : Piece(white)
{
    if (_IsWhite) _Type = W_PAWN;
    else          _Type = B_PAWN;
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

    //check distance on X : only one tile forward is allowed
    if (dx  > 1) return false;

    //Y tile should not change
    if (dy != 0) return false;
}

Pawn::~Pawn()
{

}
#include "King.hpp"

King::King(const bool white) : Piece(white)
{
    if (_IsWhite) _Type = W_KING;
    else          _Type = B_KING;

    _IsCheckmate = false;
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool King::isMoveValid(const int x, const int y) const
{
    int dx = abs(_X - x);
    int dy = abs(_Y - y);

    //if the piece doesn't move
    if (dx == 0 && dy == 0) return true;

    //king can move one tile in every direction
    if (dx > 1) return false;
    if (dy > 1) return false;

    //default
    return true;
}

King::~King()
{

}
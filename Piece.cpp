#include "Piece.hpp"

Piece::Piece()
{
    _X          = 0;
    _Y          = 0;
    _Type       = PAWN;
    _Color      = false;
    _IsSelected = false;
} 

/**
 * Change the position of the piece
 * @param x New X
 * @param y New Y
 */
void Piece::move(int x, int y)
{
    _X = x;
    _Y = y;
}

Piece::~Piece()
{
}


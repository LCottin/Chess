#include "Piece.hpp"

Piece::Piece()
{
    _X          = 0;
    _Y          = 0;
    _Type       = PAWN;
    _IsWhite    = false;
    _IsSelected = false;
} 

/**
 * Change the position of the piece
 * @param x New X
 * @param y New Y
 */
void Piece::move(const int x, const int y)
{
    _X = x;
    _Y = y;
}

/**
 * Get X
 * @returns X coordinate
 */
int Piece::getX() const 
{
    return _X;
}

/**
 * Get Y
 * @returns Y coordinate
 */
int Piece::getY() const 
{
    return _Y;
}

/**
 * Get the piece type
 * @returns Type (a number between 0 and 5)
 */
int Piece::getType() const 
{
    return _Type;
}

Piece::~Piece()
{

}


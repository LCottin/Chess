#include "Piece.hpp"

Piece::Piece(const bool white)
{
    _X          = 0;
    _Y          = 0;
    _IsAlive    = true;
    _IsWhite    = white;
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
 * Indicates if the piece is still alive
 * @returns true if the piece is alive, else false
 */
bool Piece::isAlive() const
{
    return _IsAlive;
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


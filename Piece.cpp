#include "Piece.hpp"

Piece::Piece(const bool white)
{
    _X          = 0;
    _Y          = 0;
    _XWindow    = 0;
    _YWindow    = 0; 
    _IsAlive    = true;
    _IsWhite    = white;
} 

/**
 * Changes the position of the piece on the board
 * @param x New X on the board
 * @param y New Y on the board
 */
void Piece::moveBoard(const int x, const int y)
{
    _X = x;
    _Y = y;
    moveWindow( (x*55) + 1, (y*55) + 1);
}

/**
 * Changes the position of the piece on the window 
 * @param x New X on the window (in pixels)
 * @param y New Y on the window (in pixels)
 */
void Piece::moveWindow(const int x, const int y)
{
    _XWindow = x;
    _YWindow = y;
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
 * Kills the piece
 */
void Piece::kill()
{
    _IsAlive = false;
    _Type = EMPTY;
}

/**
 * Gets X
 * @returns X coordinate
 */
int Piece::getX() const 
{
    return _X;
}

/**
 * Gets Y
 * @returns Y coordinate
 */
int Piece::getY() const 
{
    return _Y;
}


Piece::~Piece()
{

}


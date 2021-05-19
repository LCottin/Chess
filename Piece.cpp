#include "Piece.hpp"

Piece::Piece(const bool white)
{
    _X          = 0;
    _Y          = 0;
    _XWindow    = 0;
    _YWindow    = 0; 
    _IsAlive    = true;
    _IsWhite    = white;
    _IsDragged  = false;
} 

/**
 * Changes the state of a piece if it's dragged or not
 * @param isDragged is the piece dragged or no
 */
void Piece::setIsDragged(const bool dragged)
{
    if(dragged)
        _IsDragged = true;
    else
        _IsDragged = false;
}

/**
 * Get the state of a piece if it's dragged or not
 * @return isDragged is the piece dragged or no
 */
bool Piece::getIsDragged() const
{
    return _IsDragged;
}

/**
 * Changes the position of the piece on the board
 * @param to Vector of new coordinate on the board
 */
void Piece::moveBoard(const Vector2i to)
{
    _X = to.x;
    _Y = to.y;
    Vector2i toWindow = (to + Vector2i(1, 1));
    toWindow = toWindow * 55;
    moveWindow(Vector2f(toWindow));
}

/**
 * Changes the position of the piece on the window 
 * @param to Vector of new coordinate on the window (in pixels)
 */
void Piece::moveWindow(const Vector2f to)
{
    _XWindow = to.x;
    _YWindow = to.y;
    _PieceSprite.setPosition(_XWindow, _YWindow);
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
void Piece::kill(const bool unKill, const int xWindow, const int yWindow, const int TYPE)
{
    if(unKill)
    {
        _IsAlive = true;
        _Type = (TYPES)TYPE;
        moveWindow(Vector2f(xWindow,yWindow));
    }
    else
    {
        _IsAlive = false;
        _Type = EMPTY;
        moveWindow(Vector2f(9999,9999));
    }

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

/**
 * Gets X
 * @returns X coordinate
 */
int Piece::getXWindow() const 
{
    return _XWindow;
}

/**
 * Gets Y
 * @returns Y coordinate
 */
int Piece::getYWindow() const 
{
    return _YWindow;
}

/**
 * Returns a pointer to the sprite
 * @returns A pointer to the Piece's sprite
 */ 
Sprite* Piece::getSprite()
{
    return &_PieceSprite;
}

Piece::~Piece()
{
    
}


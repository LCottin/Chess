#include "Knight.hpp"

Knight::Knight(const bool white) : Piece(white)
{
    if(_IsWhite)
    {
        _Type = W_KNIGHT;
        _PieceTexture.loadFromFile("Textures/wkn.png");
    } 
    else
    {
        _Type = B_KNIGHT;
        _PieceTexture.loadFromFile("Textures/bkn.png");
    }  
    _PieceSprite.setTexture(_PieceTexture);       
} 

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool Knight::isMoveValid(const Vector2i destination, const bool attacking)
{
    int dx = abs(destination.x - _X);
    int dy = abs(destination.y - _Y);

    //if the piece doesn't move
    if(dx == 0 && dy == 0) return false;
    
    //knight can move one tile horizontally and two tiles vertically or two tiles horizontally and one tile vertically
    if(dx + dy != 3)  return false;
    if(dx > 2)        return false;
    if(dy > 2)        return false;

    //default
    return true;
}

/**
 * Gets the piece type
 * @returns Type (a number between -6 and 6)
 */
int Knight::getType() const 
{
    return _Type;
}

Knight::~Knight()
{
    
}
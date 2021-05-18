#include "Queen.hpp"

Queen::Queen(const bool white) : Piece(white)
{
    if(_IsWhite) 
    {
        _Type = W_QUEEN;
        _PieceTexture.loadFromFile("Textures/wq.png");
    }
    else
    {   _Type = B_QUEEN;
        _PieceTexture.loadFromFile("Textures/bq.png");
    }
    _PieceSprite.setTexture(_PieceTexture);
}


/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool Queen::isMoveValid(const Vector2i destination, const bool attacking)
{
    int dx = abs(destination.x - _X);
    int dy = abs(destination.y - _Y);

    //if the piece doesn't move
    if(dx == 0 && dy == 0) return false;
    
    //Queen can move both like a rook and a bishop
    //only x or y should change, not both
    if(dx != 0 && dy != 0)
        if(dx != dy)
            return false;

    //default
    return true;
}

/**
 * Gets the piece type
 * @returns Type (a number between -6 and 6)
 */
int Queen::getType() const 
{
    return _Type;
}

Queen::~Queen()
{
    
}
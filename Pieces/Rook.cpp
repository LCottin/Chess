#include "Rook.hpp"

Rook::Rook(const bool white) : Piece(white)
{
    if(_IsWhite) 
    {
        _Type = W_ROOK;
        _PieceTexture.loadFromFile("Textures/wr.png");
    }
    else
    {         
        _Type = B_ROOK;
        _PieceTexture.loadFromFile("Textures/br.png");
    }
    _PieceSprite.setTexture(_PieceTexture);
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool Rook::isMoveValid(const int x, const int y, const bool attacking)
{
    int dx = abs(x - _X);
    int dy = abs(y - _Y);

    //if the piece doesn't move
    if(dx == 0 && dy == 0) return false;
    
    //only x or y should change, not both
    if(dx != 0 && dy != 0) return false;

    //default
    return true;
}

/**
 * Gets the piece type
 * @returns Type (a number between -6 and 6)
 */
int Rook::getType() const 
{
    return _Type;
}

Rook::~Rook()
{
    
}
#include "Pawn.hpp"
#include <iostream>

using namespace std;

Pawn::Pawn(const bool white) : Piece(white)
{
    if(_IsWhite) 
    {
        _Type = W_PAWN;
        _PieceTexture.loadFromFile("Textures/wp.png");
    }
    else         
    {
        _Type = B_PAWN;
        _PieceTexture.loadFromFile("Textures/bp.png");
    }
    _PieceSprite.setTexture(_PieceTexture);
    _FirstMove = true;
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool Pawn::isMoveValid(const Vector2i destination, const bool attacking)
{
    int dx = destination.x - _X;
    int dy = destination.y - _Y;

    //if the piece doesn't move
    if(dx == 0 && dy == 0) return false;

    //if the piece doesn't move in the right direction
    if(_IsWhite)
    {
        if(dy > 0)
        {
            return false;
        } 
    }
    else
    {
        if(dy < 0)
        {
            return false;
        } 
    }
    
    //Pawn's special attack move
    if(attacking)
    {
        if(_IsWhite)
        {
            if((dx != -1) && (dx != 1))
                return false;
            if(dy != -1)
                return false;
        }
        else
        {
            if((dx != -1) && (dx != 1))
                return false;
            if(dy != 1)
                return false;
        }
    }
    else
    {
        //if it is his first move, only 2 tiles forward, otherwise, only one tile forward is allowed
        if(abs(dy)  > (_FirstMove ? 2 : 1)) return false;

        //x tile should not change
        if(abs(dx) != 0) return false;
    }

    //default
    if(_FirstMove)
        _FirstMove = false;

    return true;
}

/**
 * Gets the piece type
 * @returns Type (a number between -6 and 6)
 */
int Pawn::getType() const 
{
    return _Type;
}

Pawn::~Pawn()
{

}
#include "Pawn.hpp"
#include <iostream>

using namespace std;

Pawn::Pawn(const bool white) : Piece(white)
{
    if(_IsWhite) _Type = W_PAWN;
    else         _Type = B_PAWN;

    _FirstMove = true;
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool Pawn::isMoveValid(const int x, const int y, const bool attacking)
{
    int dx = x - _X;
    int dy = y - _Y;

    //if the piece doesn't move
    if(dx == 0 && dy == 0) return false;

    //if the piece doesn't move in the right direction
    if(_IsWhite)
    {
        cout << "white pawn played" << endl;
        if(dy > 0)
        {
            cout << "going in wrong direction" << endl;
            return false;
        } 
    }
    else
    {
        cout << "black pawn played" << endl;
        if(dy < 0)
        {
            cout << "going in wrong direction" << endl;
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

Pawn::~Pawn()
{

}
#include "King.hpp"

King::King(const bool white) : Piece(white)
{
    if(_IsWhite)
    {
        _Type = W_KING;
        _PieceTexture.loadFromFile("Textures/wk.png");
    } 
    else
    {
        _Type = B_KING;
        _PieceTexture.loadFromFile("Textures/bk.png");
    }        

    _PieceSprite.setTexture(_PieceTexture);
    _IsCheck     = false;
    _IsCheckmate = false;
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool King::isMoveValid(const int x, const int y, const bool attacking)
{
    int dx = abs(x - _X);
    int dy = abs(y - _Y);

    //if the piece doesn't move
    if(dx == 0 && dy == 0) return false;

    //king can move one tile in every direction
    if(dx > 1) return false;
    if(dy > 1) return false;

    //default
    return true;
}

/**
 * Gets the piece type
 * @returns Type (a number between -6 and 6)
 */
int King::getType() const 
{
    return _Type;
}

/**
 * Sets king's check status
 * @param check new status
 */
void King::setCheck(const bool check)
{
    _IsCheck = check;
}

/**
 * Sets king's checkmate status
 * @param checkmate new status
 */
void King::setCheckMate(const bool checkmate)
{
    _IsCheckmate = checkmate;
}

/**
 * Tells if the king is checked
 * @returns true if it's checked, else false
 */
bool King::isCheck() const
{
    return _IsCheck;
}

/**
 * Tells if the king is checkmated (needs to be check first)
 * @returns true if it's checkmated, else false
 */
bool King::isCheckMate() const
{
    return _IsCheckmate && _IsCheck;
}

King::~King()
{

}
#include "King.hpp"

King::King(const bool white) : Piece(white)
{
    if(_IsWhite) _Type = W_KING;
    else          _Type = B_KING;

    _IsCheck     = false;
    _IsCheckmate = false;
}

/**
 * Indicates ifmoving to the given position is possible
 * @param x,y possible position
 * @returns true ifthe move is possible, else false
 */
bool King::isMoveValid(const int x, const int y, const bool attacking)
{
    int dx = (x - _X);
    int dy = (y - _Y);

    //ifthe piece doesn't move
    if(abs(dx) == 0 && abs(dy) == 0) return false;

    //king can move one tile in every direction
    if(abs(dx) > 1) return false;
    if(abs(dy) > 1) return false;

    //default
    return true;
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
 * Tells ifthe king is checked
 * @returns true ifit's checked, else false
 */
bool King::isCheck() const
{
    return _IsCheck;
}

/**
 * Tells ifthe king is checkmated (needs to be check first)
 * @returns true ifit's checkmated, else false
 */
bool King::isCheckMate() const
{
    return _IsCheckmate && _IsCheck;
}

King::~King()
{

}
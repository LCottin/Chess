#include "King.hpp"

King::King(const bool white) : Piece(white)
{
    if (_IsWhite) _Type = W_KING;
    else          _Type = B_KING;

    _IsCheck     = false;
    _IsCheckmate = false;
}

/**
 * Indicates if moving to the given position is possible
 * @param x,y possible position
 * @returns true if the move is possible, else false
 */
bool King::isMoveValid(const int x, const int y) const
{
    int dx = abs(_X - x);
    int dy = abs(_Y - y);

    //if the piece doesn't move
    if (dx == 0 && dy == 0) return true;

    //king can move one tile in every direction
    if (dx > 1) return false;
    if (dy > 1) return false;

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
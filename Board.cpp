#include "Board.hpp"

Board _Board;

Board::Board()
{
    cout << "Creation of board " << this << " ...";
    _Board      = new int* [_SizeX];

    for (int i = 0; i < _SizeX; i++)
    {
        _Board[i]       = new int [_SizeY];
        for (int j = 0; j < _SizeY; j++)
        {
            _Board[i][j] = 0;
        }   
    }

    //Init both sides
    for (int i = 0; i < _SizeX; i++)
    {
        _Board[i][0] = -1;
        _Board[i][1] = -1;
        _Board[i][6] =  1;
        _Board[i][7] =  1;
    }
    cout << "Board " << this << " created ! " << endl;
}

/**
 * Update the board when a player moves or attack
 * @param oldX,oldY Old piece position
 * @param newX,newY New piece position
 * @param whiteTurn Tells who's player it is
 * @return Void
 */
void Board::updateBoard(const int oldX, const int oldY, const int newX, const int newY, const bool whiteTurn)
{
    //puts a 0 at the old position
    _Board[oldX][oldY] = 0;

    //puts the type of the piece at the given new position according to whiteTurn status
    _Board[newX][newY] = (whiteTurn ? 1 : -1);
}


/**
 * Check if there are any collision on the desired path
 * @param oldX,oldY Old piece position
 * @param newX,newY New piece position
 * @param IsAttacking Tells if player is targetting an enemy
 * @return bool
 */
bool Board::CollisionCheck(const int oldX, const int oldY, const int newX, const int newY, const int type, const bool whiteTurn)
{
    int cursorX = 1;
    int cursorY = 1;

    switch(type)
    {
        /* Those case are already checked in the IsValidMove from Pawns because of the attackmove
        case -6:
        case  1:
        */
        case -5:
        case  2:
            cursorX = (((newX - oldX) > 0) ? 1 : -1);;
            cursorY = (((newY - oldY) > 0) ? 1 : -1);;
            while((oldY + cursorY != newY) && (oldX + cursorX != newX))
            {
                cout << (getPiece((oldX + cursorX),(oldY + cursorY))) << endl;
                if(getPiece((oldX + cursorX),(oldY + cursorY)) != 0)
                    return false;

                cursorX = cursorX + (((newX - oldX) > 0) ? 1 : -1);
                cursorY = cursorY + (((newY - oldY) > 0) ? 1 : -1);
            }
            cout << (getPiece((oldX + cursorX),(oldY + cursorY))) << endl;
            if(getPiece((oldX + cursorX),(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                return false;
           
            return true;
        case -4:
        case  3:
            if(getPiece(newX,newY) == (whiteTurn ? 1 : -1))
                return false;
            return true;
        case -3:
        case  4:
            cursorX = (((newX - oldX) > 0) ? 1 : -1);;
            cursorY = (((newY - oldY) > 0) ? 1 : -1);;
            if(oldX == newX)
            {
                while(oldY + cursorY != newY)
                {
                    cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                    if(getPiece(oldX,(oldY + cursorY)) != 0)
                        return false;

                    cursorY = cursorY + (((newY - oldY) > 0) ? 1 : -1);
                }
                cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                if(getPiece(oldX,(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                    return false;
            }
            else
            {
                while(oldX + cursorX != newX)
                {
                    cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                    if(getPiece((oldX + cursorX),oldY) != 0)
                        return false;

                    cursorX = cursorX + (((newX - oldX) > 0) ? 1 : -1);
                }
                cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                if(getPiece((oldX + cursorX),oldY) == (whiteTurn ? 1 : -1))
                    return false;
            }
            return true;
        case -2:
        case  5:
            cursorX = (((newX - oldX) > 0) ? 1 : -1);;
            cursorY = (((newY - oldY) > 0) ? 1 : -1);;
            if(oldX == newX)
            {
                while(oldY + cursorY != newY)
                {
                    cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                    if(getPiece(oldX,(oldY + cursorY)) != 0)
                        return false;

                    cursorY = cursorY + (((newY - oldY) > 0) ? 1 : -1);
                }
                cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                if(getPiece(oldX,(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                    return false;
            }
            else if(oldY == newY)
            {
                while(oldX + cursorX != newX)
                {
                    cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                    if(getPiece((oldX + cursorX),oldY) != 0)
                        return false;

                    cursorX = cursorX + (((newX - oldX) > 0) ? 1 : -1);
                }
                cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                if(getPiece((oldX + cursorX),oldY) == (whiteTurn ? 1 : -1))
                    return false;
            }
            else
            {
                cursorX = (((newX - oldX) > 0) ? 1 : -1);;
                cursorY = (((newY - oldY) > 0) ? 1 : -1);;
                while((oldY + cursorY != newY) && (oldX + cursorX != newX))
                {
                    cout << (getPiece((oldX + cursorX),(oldY + cursorY))) << endl;
                    if(getPiece((oldX + cursorX),(oldY + cursorY)) != 0)
                        return false;

                    cursorX = cursorX + (((newX - oldX) > 0) ? 1 : -1);
                    cursorY = cursorY + (((newY - oldY) > 0) ? 1 : -1);
                }
                cout << (getPiece((oldX + cursorX),(oldY + cursorY))) << endl;
                if(getPiece((oldX + cursorX),(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                    return false;
            }
            return true;
        case -1:
        case  6:
            cursorX = (((newX - oldX) > 0) ? 1 : -1);;
            cursorY = (((newY - oldY) > 0) ? 1 : -1);;
            if(oldX == newX)
            {
                if(getPiece(oldX,(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                    return false;
            }
            else if(oldY == newY)
            {
                if(getPiece((oldX + cursorX),oldY) == (whiteTurn ? 1 : -1))
                    return false;
            }
            else
            {
                if(getPiece((oldX + cursorX),(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                    return false;
            }
            return true;
    }
    return true;
}

/**
 * Prints the current board
 */
void Board::printBoard() const 
{
    for (int i = 0; i < _SizeX; i++)
    {
        cout << "-----------------------------------" << endl;
        for (int j = 0; j < _SizeY; j++)
        {
            cout << " | " << _Board[i][j];
        }
        cout << " | " << endl;
    }
    cout << "-----------------------------------" << endl;
}


/**
 * Set a piece at the piece coordinates
 * @param piece Piece to place
 */
void Board::setPiece(const Piece &piece)
{
    _Board[piece.getX()][piece.getY()] = piece.getType();
}

/**
 * Set a piece at the piece coordinates
 * @param x,y Coordinates of the new piece
 * @param value Piece to set
 */
void Board::setPiece(const int x, const int y, const int value)
{
    _Board[x][y] = value;
}


/**
 * Get a piece at a given position
 * @param x,y Position 
 * @returns The number of the piece
 */
int Board::getPiece(const int x, const int y) const
{
    return _Board[x][y];
}

Board::~Board()
{
    for (int i = 0; i < _SizeY; i++)
    {
        delete _Board[i];
    }
    delete _Board;
}
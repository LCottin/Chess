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
 * Updates the board when a player moves or attacks
 * @param oldX,oldY Old piece position
 * @param newX,newY New piece position
 * @param whiteTurn Tells who's player it is
 */
void Board::updateBoard(const int oldX, const int oldY, const int newX, const int newY, const bool whiteTurn)
{
    //puts a 0 at the old position
    _Board[oldX][oldY] = 0;

    //puts the type of the piece at the given new position according to whiteTurn status
    _Board[newX][newY] = (whiteTurn ? 1 : -1);
}


/**
 * Checks if there are any collision on the desired path
 * @param oldX,oldY Old piece position
 * @param newX,newY New piece position
 * @param IsAttacking Tells if player is targetting an enemy
 * @return false if there is collision, else true
 */
bool Board::collisionCheck(const int oldX, const int oldY, const int newX, const int newY, const int type, const bool whiteTurn) const
{
    //cursors on X and Y axis to check every tile between old pos and new pos
    int cursorX = (((newX - oldX) > 0) ? 1 : -1);
    int cursorY = (((newY - oldY) > 0) ? 1 : -1);

    switch(type)
    {
        /* Those case are already checked in the IsValidMove from Pawns because of the attackmove
        case -6:
        case  1:
        */

        //When it's a bishop
        case -5:
        case  2:

            //move along the board until while oldPos and newPOs are different
            while((oldY + cursorY != newY) && (oldX + cursorX != newX))
            {
                cout << (getPiece((oldX + cursorX), (oldY + cursorY))) << endl;
                if(getPiece((oldX + cursorX), (oldY + cursorY)) != 0)
                    return false;

                //update cursors
                cursorY += (((newY - oldY) > 0) ? 1 : -1);
                cursorX += (((newX - oldX) > 0) ? 1 : -1);
            }

            //checks if the piece color at the new position is the same than the piece that moves
            cout << (getPiece((oldX + cursorX),(oldY + cursorY))) << endl;
            if(getPiece((oldX + cursorX),(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                return false;
            return true;

        //checks when it's a knight
        case -4:
        case  3:
            if(getPiece(newX,newY) == (whiteTurn ? 1 : -1))
                return false;
            return true;

        //when it's a rook
        case -3:
        case  4:
            //moves on the same column
            if(oldX == newX)
            {
                while(oldY + cursorY != newY)
                {
                    cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                    if(getPiece(oldX,(oldY + cursorY)) != 0)
                        return false;

                    cursorY += (((newY - oldY) > 0) ? 1 : -1);
                }
                cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                if(getPiece(oldX,(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                    return false;
            }
            //moves on the same line
            else
            {
                while(oldX + cursorX != newX)
                {
                    cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                    if(getPiece((oldX + cursorX),oldY) != 0)
                        return false;

                    cursorX += (((newX - oldX) > 0) ? 1 : -1);
                }
                cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                if(getPiece((oldX + cursorX),oldY) == (whiteTurn ? 1 : -1))
                    return false;
            }
            return true;

        //when it's a queen
        case -2:
        case  5:
            //moves on the same column
            if(oldX == newX)
            {
                while(oldY + cursorY != newY)
                {
                    cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                    if(getPiece(oldX,(oldY + cursorY)) != 0)
                        return false;

                    cursorY += (((newY - oldY) > 0) ? 1 : -1);
                }
                cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                if(getPiece(oldX,(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                    return false;
            }
            //moves on the same line
            else if(oldY == newY)
            {
                while(oldX + cursorX != newX)
                {
                    cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                    if(getPiece((oldX + cursorX),oldY) != 0)
                        return false;

                    cursorX += (((newX - oldX) > 0) ? 1 : -1);
                }
                cout << (getPiece(oldX,(oldY + cursorY))) << endl;
                if(getPiece((oldX + cursorX),oldY) == (whiteTurn ? 1 : -1))
                    return false;
            }
            //moves on a diagonal
            else
            {
                
                while((oldY + cursorY != newY) && (oldX + cursorX != newX))
                {
                    cout << (getPiece((oldX + cursorX),(oldY + cursorY))) << endl;
                    if(getPiece((oldX + cursorX),(oldY + cursorY)) != 0)
                        return false;

                    cursorX += (((newX - oldX) > 0) ? 1 : -1);
                    cursorY += (((newY - oldY) > 0) ? 1 : -1);
                }
                cout << (getPiece((oldX + cursorX),(oldY + cursorY))) << endl;
                if(getPiece((oldX + cursorX),(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                    return false;
            }
            return true;

        //when it's a king
        case -1:
        case  6:
            //moves on the same column
            if(oldX == newX)
            {
                if(getPiece(oldX,(oldY + cursorY)) == (whiteTurn ? 1 : -1))
                    return false;
            }

            //moves on the same line
            else if(oldY == newY)
            {
                if(getPiece((oldX + cursorX),oldY) == (whiteTurn ? 1 : -1))
                    return false;
            }

            //moves on diagonal
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
 * Gets a piece at a given position
 * @param x,y Position 
 * @returns The type of the piece
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
#include "Board.hpp"

Board _Board;

Board::Board()
{
    cout << "Creation of board " << this << " ...";
    _Board      = new int* [_SizeX];

    for (int i = 0; i < _SizeX; i++)
    {
        _Board[i]       = new int [_SizeY];
    }

    //fills both board
    for (int i = 0; i < _SizeX; i++)
    {
        for (int j = 0; j < _SizeY; j++)
        {
            _Board[i][j] = 0;
        }   
    }

    cout << "Board " << this << " created ! " << endl;
}

/**
 * Update the board when a player attacks
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
 * Prints a board
 * @param printInit 1 to print initial board, 0 else
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

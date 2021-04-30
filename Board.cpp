#include "Board.hpp"


Board::Board()
{
    _Board      = new int* [_SizeX];
    _InitBoard  = new int* [_SizeX];

    for (int i = 0; i < _SizeX; i++)
    {
        _Board[i]       = new int [_SizeY];
        _InitBoard[i]   = new int [_SizeY];
    }

     //fills both board
    for (int i = 0; i < _SizeX; i++)
    {
        for (int j = 0; j < _SizeY; j++)
        {
            _Board[i][j]        = 0;
            _InitBoard[i][j]    = 0;
        }   
    }

    //init first line
    _InitBoard[0][0] = -3;
    _InitBoard[0][1] = -4;
    _InitBoard[0][2] = -5;
    _InitBoard[0][3] = -2;
    _InitBoard[0][4] = -1;
    _InitBoard[0][5] = -5;
    _InitBoard[0][5] = -4;
    _InitBoard[0][5] = -3;

    //init second and second to last line
    for (size_t i = 0; i < _SizeX; i++)
    {
        _InitBoard[1][i] = -6;
        _InitBoard[6][i] =  1;
    }

    //init last line
    _InitBoard[7][0] = 4;
    _InitBoard[7][1] = 3;
    _InitBoard[7][2] = 2;
    _InitBoard[7][3] = 5;
    _InitBoard[7][4] = 6;
    _InitBoard[7][5] = 2;
    _InitBoard[7][5] = 3;
    _InitBoard[7][5] = 4;

    _Board = _InitBoard;
}


/**
 * Prints a board
 * @param printInit 1 to print initial board, 0 else
 */
void Board::printBoard(const bool printInit = 0) const 
{
    int** currentBoard;
    if (printInit) currentBoard = _InitBoard;
    else           currentBoard = _Board;
    
    for (int i = 0; i < _SizeX; i++)
    {
        cout << "-----------------------------------" << endl;
        for (int j = 0; j < _SizeY; j++)
        {
            cout << " | " << currentBoard[i][j];
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
 * Get a piece at a given position from the init board
 * @param x,y Position 
 * @returns The number of the piece
 */
int Board::getInitPiece(const int x, const int y) const
{
    return _InitBoard[x][y];
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

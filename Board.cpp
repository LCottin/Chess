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
            _Board[i][j] = 0;

            // if i XOR j then we change 
            if ((i%2 && !(j%2)) || (j%2 && !(i%2)))
            {
                if (_IsTopLeftWhite) _InitBoard[i][j] = 1;
                else                 _InitBoard[i][j] = 0;
            }
            else 
            {
                if (_IsTopLeftWhite) _InitBoard[i][j] = 0;
                else                 _InitBoard[i][j] = 1;
            }
        }   
    }
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

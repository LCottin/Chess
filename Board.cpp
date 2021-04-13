#include "Board.hpp"


Board::Board()
{
    // _SizeX = 8;
    // _SizeY = 8;

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
                _InitBoard[i][j] = 1;
            }
            else 
            {
                _InitBoard[i][j] = 0;
            }
        }   
    }
}

Board::~Board()
{
    for (int i = 0; i < _SizeY; i++)
    {
        delete _Board[i];
    }
    delete _Board;
}

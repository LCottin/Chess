#include "Board.hpp"


Board::Board()
{
    // _SizeX = 8;
    // _SizeY = 8;

    _Board = new int* [_SizeX];

    for (int i = 0; i < _SizeX; i++)
    {
        _Board[i] = new int [_SizeY];
    }

    for (int i = 0; i < _SizeX; i++)
    {
        for (size_t j = 0; j < _SizeY; j++)
        {
            _Board[i][j] = 0;
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

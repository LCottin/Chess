#ifndef __BOARD__
#define __BOARD__

#include <iostream>
#include <string>

using namespace std;

class Board
{
    private:
        const int _SizeX = 8;
        const int _SizeY = 8;
        int** _Board;

    public:
        Board();
        ~Board();
};
 


#endif
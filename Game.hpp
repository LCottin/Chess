#ifndef __GAME__
#define __GAME__

#include <iostream>
#include <string>
#include <vector>

#include "Player.hpp"
#include "Board.hpp"
 
class Game
{
    private:
        Board _Board; 
        Player _White;
        Player _Black;

        int _TurnCount; //how many turns have been playd
        bool _WhiteTurn; //indicades who's turn it is

    public:
        Game();
        ~Game();
};

#endif
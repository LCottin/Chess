#ifndef __GAME__
#define __GAME__

#include <iostream>
#include <string>
#include <vector>

#include "Player.hpp"
#include "Board.hpp"
#include "GameStatus.hpp"

using namespace std;

class Game
{
    private:
        Board*  _Board; //game board
        Player* _White; //white player
        Player* _Black; //black player

        int         _TurnCount; //how many turns have been played
        bool        _WhiteTurn; //indicades who's turn it is
        GAMESTATUS  _Status;    //stores current status of the game

    public:
        Game(const string name1, const string name2);
        void playGame();
        ~Game();
};

#endif
#include "Game.hpp"


Game::Game(const string name1, const string name2)
{
    cout << "Init Game" << endl;
    _White = new Player(name1, 1);
    _Black = new Player(name2, 0);
    _Board = new Board();

    _TurnCount = 0;
    _WhiteTurn = true;
} 

Game::~Game()
{
    delete _White;
    delete _Black;
    delete _Board;
    cout << "Destroy game" << endl;
}


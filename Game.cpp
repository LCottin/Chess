#include "Game.hpp"


Game::Game(const string name1, const string name2)
{
    cout << "Init Game" << endl;
    _White = new Player(name1, 1);
    _Black = new Player(name2, 0);
    _Board = new Board();

    _TurnCount = 0;
    _WhiteTurn = true;
    _Status    = INIT;
} 

/**
 * Starts a new game
 * MORE DETAILS ARE WELCOME
 */
void Game::playGame()
{
    //change to active status
    _Status = ACTIVE;

    while (_Status == ACTIVE)
    {
        /**
         * 0 : update counter
         * 1 : each player plays
         * 2 : check for check
         * 3 : check for pat (in this case it's a draw)
         */

        /* 0 : update counter */
        _TurnCount++;

        /* 1 : players play */
        if (_WhiteTurn)
        {
            //_White->play();
            _WhiteTurn = false;
        }
        else
        {
            //_Black->play();
            _WhiteTurn = true;
        }
        
    
    }     
}

Game::~Game()
{
    delete _White;
    delete _Black;
    delete _Board;
    cout << "Destroy game" << endl;
}


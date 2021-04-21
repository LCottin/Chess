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
 * Starts a new game and follow this patern :
 * 0 : update counter and next turn
 * 1 : check for check
 * 2 : check for checkmate
 * 3 : check for pat (in this case it's a draw) : done later
 * 4 : one player plays 
 * MORE DETAILS ARE WELCOME
 */
void Game::playGame()
{
    //change to active status
    _Status = ACTIVE;

    while (_Status == ACTIVE)
    {
        /* -------------------------------- */
        /* 0 : update counter and next turn */
        /* -------------------------------- */
        _TurnCount++;
        _WhiteTurn = !_WhiteTurn;

        /* ------------------- */
        /* 1 : check for check */
        /* ------------------- */
        _Status = isCheck(); //looks for check and update game status and players' status
        if (_White->isCheck()) //if white is checked
        {
            // do something
        }
        else if (_Black->isCheck()) //else is black is checked
        {
            // do something
        }

        /* ----------------------- */
        /* 2 : check for checkmate */
        /* ----------------------- */
        _Status = isCheckMate();
        if (_Status == B_WINS || _Status == W_WINS)
        {
            //when someone won, stops the loop to print congrats
            break;
        }

        /* ----------------- */
        /* 3 : check for pat */
        /* ----------------- */
        //will be done later ...

        /* ---------------------------------------------------------------------- */
        /* 4 : one player plays according to the previous steps (including check) */
        /* ---------------------------------------------------------------------- */
        if (_WhiteTurn)
        {
            //_White->play();
        }
        else
        {
            //_Black->play();
        }
    }

    switch (_Status)
    {
        case DRAW:
            cout << "It's a draw ... be both better next time ! :) " << endl;
            break;

        case B_WINS:
            cout << _Black->getName() << " wins, congratulations !" << endl;
            break;

        case W_WINS:
            cout << _White->getName() << " wins, congratulations !" << endl;
            break;

        default:
            break;
    }     
}

/**
 * Tells if someone is in checked, changes games status and updates players' status
 * @brief TODO !!
 * @returns New game status (ACTIVE or CHECK)
 */
GAMESTATUS Game::isCheck() const
{
    /* Method to do */
    return ACTIVE;
}

/**
 * Tells if someone is checkmate and update game status
 * @brief TODO !!
 * @returns New game status (ACTIVE or B/W WINS)
 */
GAMESTATUS Game::isCheckMate() const
{
    //needs at least someone checked
    if (_Status != CHECK) return _Status;

    //default
    return _Status;
}

Game::~Game()
{
    delete _White;
    delete _Black;
    delete _Board;
    cout << "Destroy game" << endl;
}


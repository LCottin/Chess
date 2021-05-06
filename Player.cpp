#include "Player.hpp"

/**
 * Init a player with a name and a color
 * @param name Name of the player
 * @param white white = 1, black = 0
 */
Player::Player(const string name, const bool white)
{
    _Pseudo     = name;
    _IsWhite    = white;
    _IsCheck    = false;

    //create and position king
    _Pieces[0]  = new King(white);
    _Pieces[0]->move(4, white?7:0);

    //create and position queen
    _Pieces[1]  = new Queen(white);
    _Pieces[1]->move(3, white?7:0);

    //create and position pawns
    for (int i = 2; i < 10; i++)
    {
        _Pieces[i] = new Pawn(white);
        _Pieces[i]->move(i-2, white?6:1);
    }
    
    //create and position rooks
    _Pieces[10] = new Knight(white);
    _Pieces[10]->move(0, white?7:0);
    _Pieces[11] = new Knight(white);
    _Pieces[11]->move(7, white?7:0);


    //create and position knights
    _Pieces[12] = new Rook(white);
    _Pieces[12]->move(1, white?7:0);
    _Pieces[13] = new Rook(white);
    _Pieces[13]->move(6, white?7:0);
    
    //create and position bishops
    _Pieces[14] = new Bishop(white);
    _Pieces[14]->move(2, white?7:0);
    _Pieces[15] = new Bishop(white);
    _Pieces[15]->move(5, white?7:0);

    cout << "Init player " << _Pseudo << endl;
}

/**
 * Gives the player's name
 * @returns Player's pseudo
 */
string Player::getName() const
{
    return _Pseudo;
}

/**
 * Gives the number of piece still alive in player's set
 * @returns Number of pieces
 */
int Player::getSize() const
{
    return _Pieces.size();
}

/**
 * INdicates if the player is cheched or not
 * @returns true if check, else false
 */
bool Player::isCheck() const
{
    return _IsCheck;
}

/**
 * Changes the player's status
 * @param isCheck New player's status
 */
void Player::setCheck(const bool isCheck)
{
    _IsCheck = isCheck;
}

Player::~Player()
{
    for(int i = 0; i < _Pieces.size(); i++)
    {
        delete _Pieces[i];
    }
    cout << "Destroy player " << _Pseudo << endl;
}
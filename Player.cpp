#include "Player.hpp"


Player::Player(const string name, const bool white)
{
    _Pseudo = name;
    _IsWhite = white;
    cout << "Init player " << _Pseudo << endl;
}

/**
 * Gives the number of piece still alive in player's set
 * @returns Number of piece
 */
int Player::getSize() const
{
    return _Set.size();
}

Player::~Player()
{
    cout << "Destroy player " << _Pseudo << endl;
}
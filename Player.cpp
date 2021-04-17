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
    _Ischeck    = false;

    *_King  = new King(white); //init king
    *_Queen = new Queen(white); //init queen

    //init pawns
    for (int i = 0; i < 6; i++)
    {
        Pawn* pawn = new Pawn(white);
        _Pawn.push_back(pawn);
    }
    
    //init rooks, knights and bishops
    for (size_t i = 0; i < 2; i++)
    {
        Knight* knight = new Knight(white);
        _Knight.push_back(knight);

        Rook* rook = new Rook(white);
        _Rook.push_back(rook);

        Bishop* bishop = new Bishop(white);
        _Bishop.push_back(bishop);
    }
    
    cout << "Init player " << _Pseudo << endl;
}

/**
 * Gives the number of piece still alive in player's set
 * @returns Number of piece
 */
int Player::getSize() const
{
    int nbPieces = 1; //at least one piece : the king
    
    nbPieces += _Rook.size() + _Bishop.size() + _Knight.size() + _Pawn.size();
    if (_Queen->isAlive()) nbPieces++;
    
    return nbPieces;
}

Player::~Player()
{
    //remove every pieces
    delete _King;
    delete _Queen;

    for (size_t i = 0; i < _Pawn.size(); i++)
    {
        delete _Pawn[i];
    }
    
    for (size_t i = 0; i < _Rook.size(); i++)
    {
        delete _Rook[i];
    }

    for (size_t i = 0; i < _Knight.size(); i++)
    {
        delete _Knight[i];
    }

    for (size_t i = 0; i < _Bishop.size(); i++)
    {
        delete _Bishop[i];
    }
    

    cout << "Destroy player " << _Pseudo << endl;
}
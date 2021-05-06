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
    King* king = new King(white);
    king->move(4, white?7:0);
    _Pieces.push_back(king);

    //create and position queen
    Queen* queen  = new Queen(white);
    queen->move(3, white?7:0);
    _Pieces.push_back(queen);

    /*  Did not initiate pawns this way beacause we were not sure how this behaves.
        //create and position pawns
        for (int i = 2; i < 10; i++)
        {
            Pawn* pawn = new Pawn(white);
            pawn->move(i-2, white?6:1);
            _Pieces.push_back(pawn);
        }
    */

    //create and position pawns
    Pawn* pawn1 = new Pawn(white);
    pawn1->move(0, white?6:1);
    _Pieces.push_back(pawn1);
    Pawn* pawn2 = new Pawn(white);
    pawn2->move(1, white?6:1);
    _Pieces.push_back(pawn2);
    Pawn* pawn3 = new Pawn(white);
    pawn3->move(2, white?6:1);
    _Pieces.push_back(pawn3);
    Pawn* pawn4 = new Pawn(white);
    pawn4->move(3, white?6:1);
    _Pieces.push_back(pawn4);
    Pawn* pawn5 = new Pawn(white);
    pawn5->move(4, white?6:1);
    _Pieces.push_back(pawn5);
    Pawn* pawn6 = new Pawn(white);
    pawn6->move(5, white?6:1);
    _Pieces.push_back(pawn6);
    Pawn* pawn7 = new Pawn(white);
    pawn7->move(6, white?6:1);
    _Pieces.push_back(pawn7);
    Pawn* pawn8 = new Pawn(white);
    pawn8->move(7, white?6:1);
    _Pieces.push_back(pawn8);

    //create and position rooks
    Knight* knight1 = new Knight(white);
    knight1->move(0, white?7:0);
    _Pieces.push_back(knight1);
    Knight* knight2 = new Knight(white);
    knight2->move(7, white?7:0);
    _Pieces.push_back(knight2);

    //create and position knights
    Rook* rook1 = new Rook(white);
    rook1->move(1, white?7:0);
    _Pieces.push_back(rook1);
    Rook* rook2 = new Rook(white);
    rook2->move(6, white?7:0);
    _Pieces.push_back(rook2);

    //create and position bishops
    Bishop* bishop = new Bishop(white);
    bishop->move(2, white?7:0);
    _Pieces.push_back(bishop);
    Bishop* temp = new Bishop(white);
    temp->move(5, white?7:0);
    _Pieces.push_back(temp);

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
 * Return the piece loacted at the given postion
 * @param x,y current position
 * @returns The piece at this position
 */
Piece* Player::getPiece(const int x, const int y) const
{
    for (int i = 0; i < _Pieces.size(); i++)
    {
        if (_Pieces[i]->getX() == x && _Pieces[i]->getY() == y)
            return _Pieces[i];
    }
    return NULL;
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
    for(long unsigned int i = 0; i < _Pieces.size(); i++)
    {
        delete _Pieces[i];
    }
    cout << "Destroy player " << _Pseudo << endl;
}
#include "Player.hpp"

/**
 * Inits a player with a name and a color
 * @param name Name of the player
 * @param white white = 1, black = 0
 */
Player::Player(const string name, const bool white)
{
    _Pseudo     = name;
    _IsWhite    = white;
    _IsCheck    = false;

    //creates and positions king
    King* king = new King(white);
    king->move(4, white?7:0);
    _Pieces.push_back(king);

    //creates and positions queen
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

    //creates and positions pawns
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

    //creates and positions rooks
    Rook* rook1 = new Rook(white);
    rook1->move(0, white?7:0);
    _Pieces.push_back(rook1);
    Rook* rook2 = new Rook(white);
    rook2->move(7, white?7:0);
    _Pieces.push_back(rook2);

    //creates and positions knights
    Knight* knight1 = new Knight(white);
    knight1->move(1, white?7:0);
    _Pieces.push_back(knight1);
    Knight* knight2 = new Knight(white);
    knight2->move(6, white?7:0);
    _Pieces.push_back(knight2);

    //creates and positions bishops
    Bishop* bishop = new Bishop(white);
    bishop->move(2, white?7:0);
    _Pieces.push_back(bishop);
    Bishop* temp = new Bishop(white);
    temp->move(5, white?7:0);
    _Pieces.push_back(temp);

    cout << "Init player " << _Pseudo << endl;
}

/**
 * Makes the player plays : update Board and moves the piece
 * @param oldX,oldY current position
 * @param newX,newY future position
 */
void Player::play(const int oldX, const int oldY, const int newX, const int newY)
{
    _Board.updateBoard(oldX, oldY, newX, newY, _IsWhite);
    getPiece(oldX, oldY)->move(newX, newY);
    _IsCheck = false;
}

/**
 * Return the piece loacted at the given postion
 * @param x,y current position
 * @returns The piece at this position
 */
Piece* Player::getPiece(const int x, const int y) const
{
    for (int i = 0; i < (int)_Pieces.size(); i++)
    {
        if((_Pieces[i]->getX() == x && _Pieces[i]->getY() == y) && (_Pieces[i]->isAlive()))
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
 * Tells how many piece a player has
 * @returns Number of piece
 */
int Player::getSize() const
{
    return _Pieces.size();
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
    for(int i = 0; i < (int)_Pieces.size(); i++)
    {
        delete _Pieces[i];
    }
    cout << "Destroy player " << _Pseudo << endl;
}
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
    king->moveBoard(Vector2i(4, white ? 7 : 0));
    _Pieces.push_back(king);

    //creates and positions queen
    Queen* queen  = new Queen(white);
    queen->moveBoard(Vector2i(3, white?7:0));
    _Pieces.push_back(queen);

    //creates and positions pawns
    Pawn* pawn1 = new Pawn(white);
    pawn1->moveBoard(Vector2i(0, white ? 6 : 1));
    _Pieces.push_back(pawn1);
    Pawn* pawn2 = new Pawn(white);
    pawn2->moveBoard(Vector2i(1, white ? 6 : 1));
    _Pieces.push_back(pawn2);
    Pawn* pawn3 = new Pawn(white);
    pawn3->moveBoard(Vector2i(2, white ? 6 : 1));
    _Pieces.push_back(pawn3);
    Pawn* pawn4 = new Pawn(white);
    pawn4->moveBoard(Vector2i(3, white ? 6 : 1));
    _Pieces.push_back(pawn4);
    Pawn* pawn5 = new Pawn(white);
    pawn5->moveBoard(Vector2i(4, white ? 6 : 1));
    _Pieces.push_back(pawn5);
    Pawn* pawn6 = new Pawn(white);
    pawn6->moveBoard(Vector2i(5, white ? 6 : 1));
    _Pieces.push_back(pawn6);
    Pawn* pawn7 = new Pawn(white);
    pawn7->moveBoard(Vector2i(6, white ? 6 : 1));
    _Pieces.push_back(pawn7);
    Pawn* pawn8 = new Pawn(white);
    pawn8->moveBoard(Vector2i(7, white ? 6 : 1));
    _Pieces.push_back(pawn8);

    //creates and positions rooks
    Rook* rook1 = new Rook(white);
    rook1->moveBoard(Vector2i(0, white ? 7 : 0));
    _Pieces.push_back(rook1);
    Rook* rook2 = new Rook(white);
    rook2->moveBoard(Vector2i(7, white ? 7 : 0));
    _Pieces.push_back(rook2);

    //creates and positions knights
    Knight* knight1 = new Knight(white);
    knight1->moveBoard(Vector2i(1, white ? 7 : 0));
    _Pieces.push_back(knight1);
    Knight* knight2 = new Knight(white);
    knight2->moveBoard(Vector2i(6, white ? 7 : 0));
    _Pieces.push_back(knight2);

    //creates and positions bishops
    Bishop* bishop1 = new Bishop(white);
    bishop1->moveBoard(Vector2i(2, white ? 7 : 0));
    _Pieces.push_back(bishop1);
    Bishop* bishop2 = new Bishop(white);
    bishop2->moveBoard(Vector2i(5, white ? 7 : 0));
    _Pieces.push_back(bishop2);
}

/**
 * Makes the player plays : update Board and moves the piece
 * @param from Vector of current position
 * @param to Vector of future position
 */
void Player::play(const Vector2i from, const Vector2i to, const bool undo, const Player* opponent)
{
    Piece* PieceDragged = getPiece(from);
    bool moveIsValid = false;

    if (undo)
    {
        PieceDragged->moveWindow(Vector2f(5555,5555));
        opponent->getPiece(to)->revive();
        return;
    }

    //checks if the move is valid
    if((PieceDragged->getType() == (_IsWhite ? 1 : -6)) && (_Board.getPiece(to) == -(_Board.getPiece(from))))
    {

        moveIsValid = PieceDragged->isMoveValid(to, true);
    }
    else
    {
        moveIsValid = PieceDragged->isMoveValid(to);
    }

    //if it is a valid move
    if (moveIsValid)
    {
        //and the piece can reach the destination
        if (_Board.collisionCheck(from, to, PieceDragged->getType(), _IsWhite))
        {
            //and I am not checked
            if (_IsCheck == false)
            {
                //plays
                PieceDragged->moveWindow(Vector2f(5555,5555));
                if(_Board.getPiece(to) == -(_Board.getPiece(from)))
                {
                    opponent->getPiece(to)->kill();
                }
                _Board.updateBoard(from, to, _IsWhite);
                PieceDragged->moveBoard(to);
            }
        }
    }
}

/**
 * Return the piece loacted at the given postion on the board
 * @param temp Vector of current position
 * @param window set to true if you give coordinates in pixels, else false
 * @returns The piece at this position
 */
Piece* Player::getPiece(const Vector2i temp, const bool window) const
{
    Vector2i boardCoord(temp);

    if(window)
    {
        boardCoord = temp / 55 - Vector2i(1, 1);
    } 

    for (int i = 0; i < (int)_Pieces.size(); i++)
    {
        if((_Pieces[i]->getX() == boardCoord.x && _Pieces[i]->getY() == boardCoord.y) && (_Pieces[i]->isAlive()))
            return _Pieces[i];
    }
    return NULL;
}

/**
 * Return the piece at index i in the player's piece vector
 * @param i index of the Player's Piece Vector
 * @returns The piece at index i
 */
Piece* Player::getPiece(const int i) const
{
    if (i > (int)_Pieces.size() || (i < 0)) 
        return NULL;
    return _Pieces[i];
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

/**
 * Changes the player's status
 * @param promotedPawn pointer to the pawn that is promoted
 * @param TYPE pawn gets promoted into TYPE
 */
void Player::promotion(Piece* promotedPawn, const int TYPE)
{
    switch (TYPE)
    {
        case -2:
        case  5:
        {
            Queen* tempQ  = new Queen(_IsWhite);
            tempQ->moveBoard(Vector2i(promotedPawn->getX(), promotedPawn->getY()));
            _Pieces.push_back(tempQ);
            break;
        }
        case -3:
        case  4:
        {
            Rook* tempR  = new Rook(_IsWhite);
            tempR->moveBoard(Vector2i(promotedPawn->getX(), promotedPawn->getY()));
            _Pieces.push_back(tempR);
            break;
        }
        case -4:
        case  3:
        {
            Knight* tempK  = new Knight(_IsWhite);
            tempK->moveBoard(Vector2i(promotedPawn->getX(), promotedPawn->getY()));
            _Pieces.push_back(tempK);
            break;
        }
        case -5:
        default:
        {
            Bishop* tempB  = new Bishop(_IsWhite);
            tempB->moveBoard(Vector2i(promotedPawn->getX(), promotedPawn->getY()));
            _Pieces.push_back(tempB);
            break;
        }
    }
    promotedPawn->kill();
}

Player::~Player()
{
    for(int i = 0; i < (int)_Pieces.size(); i++)
    {
        delete _Pieces[i];
    }
    cout << "Destroy player " << _Pseudo << endl;
}
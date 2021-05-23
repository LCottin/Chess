#include "Player.hpp"

/**
 * Inits a player with a name and a color
 * @param name Name of the player
 * @param white white = 1, black = 0
 */
Player::Player(const string name, const MODES mode, const bool white)
{
    _Pseudo     = name;
    _IsWhite    = white;
    _IsCheck    = false;

    spawnPieces(mode);
}

/**
 * Inits a player with a name and a color
 * @param mode Chose the mode (only for demo)
 */
void Player::spawnPieces(const MODES mode)
{
    //creates and positions king
    King* king = new King(_IsWhite);
    king->moveBoard(Vector2i(4, _IsWhite ? 7 : 0));
    _Board.setBoard(Vector2i(4, _IsWhite ? 7 : 0), _IsWhite);
    _Pieces.push_back(king);

    switch(mode)
    {
        // NORMAL GAME
        case 0 :
        {
            //creates and positions queen
            Queen* queen  = new Queen(_IsWhite);
            queen->moveBoard(Vector2i(3, _IsWhite?7:0));
            _Pieces.push_back(queen);

            //creates and positions pawns
            Pawn* pawn1 = new Pawn(_IsWhite);
            pawn1->moveBoard(Vector2i(0, _IsWhite ? 6 : 1));
            _Pieces.push_back(pawn1);
            Pawn* pawn2 = new Pawn(_IsWhite);
            pawn2->moveBoard(Vector2i(1, _IsWhite ? 6 : 1));
            _Pieces.push_back(pawn2);
            Pawn* pawn3 = new Pawn(_IsWhite);
            pawn3->moveBoard(Vector2i(2, _IsWhite ? 6 : 1));
            _Pieces.push_back(pawn3);
            Pawn* pawn4 = new Pawn(_IsWhite);
            pawn4->moveBoard(Vector2i(3, _IsWhite ? 6 : 1));
            _Pieces.push_back(pawn4);
            Pawn* pawn5 = new Pawn(_IsWhite);
            pawn5->moveBoard(Vector2i(4, _IsWhite ? 6 : 1));
            _Pieces.push_back(pawn5);
            Pawn* pawn6 = new Pawn(_IsWhite);
            pawn6->moveBoard(Vector2i(5, _IsWhite ? 6 : 1));
            _Pieces.push_back(pawn6);
            Pawn* pawn7 = new Pawn(_IsWhite);
            pawn7->moveBoard(Vector2i(6, _IsWhite ? 6 : 1));
            _Pieces.push_back(pawn7);
            Pawn* pawn8 = new Pawn(_IsWhite);
            pawn8->moveBoard(Vector2i(7, _IsWhite ? 6 : 1));
            _Pieces.push_back(pawn8);

            //creates and positions rooks
            Rook* rook1 = new Rook(_IsWhite);
            rook1->moveBoard(Vector2i(0, _IsWhite ? 7 : 0));
            _Pieces.push_back(rook1);
            Rook* rook2 = new Rook(_IsWhite);
            rook2->moveBoard(Vector2i(7, _IsWhite ? 7 : 0));
            _Pieces.push_back(rook2);

            //creates and positions knights
            Knight* knight1 = new Knight(_IsWhite);
            knight1->moveBoard(Vector2i(1, _IsWhite ? 7 : 0));
            _Pieces.push_back(knight1);
            Knight* knight2 = new Knight(_IsWhite);
            knight2->moveBoard(Vector2i(6, _IsWhite ? 7 : 0));
            _Pieces.push_back(knight2);

            //creates and positions bishops
            Bishop* bishop1 = new Bishop(_IsWhite);
            bishop1->moveBoard(Vector2i(2, _IsWhite ? 7 : 0));
            _Pieces.push_back(bishop1);
            Bishop* bishop2 = new Bishop(_IsWhite);
            bishop2->moveBoard(Vector2i(5, _IsWhite ? 7 : 0));
            _Pieces.push_back(bishop2);
            
            break;
        }
        // PROMOTION DEMONSTRATION
        case 1 :
        {
            //creates and positions pawns
            Pawn* pawn1 = new Pawn(_IsWhite);
            pawn1->moveBoard(Vector2i(0, _IsWhite ? 1 : 6));
            _Pieces.push_back(pawn1);

            break;
        }
        // EN PASSANT DEMONSTRATION
        case 2 :
        {
            //creates and positions pawns
            Pawn* pawn1 = new Pawn(_IsWhite);
            pawn1->moveBoard(Vector2i(_IsWhite ? 4 : 3, _IsWhite ? 4 : 4));
            _Pieces.push_back(pawn1);

            if(_IsWhite)
            {
                Pawn* pawn2 = new Pawn(_IsWhite);
                pawn2->moveBoard(Vector2i(2, 6));
                _Pieces.push_back(pawn2);     
            }

            break;
        }
        // CASTLING DEMONSTRATION
        case 3 :
        {
            if(_IsWhite)
            {
                Rook* rook1 = new Rook(_IsWhite);
                rook1->moveBoard(Vector2i(0, _IsWhite ? 7 : 0));
                _Board.setBoard(Vector2i(0, _IsWhite ? 7 : 0), _IsWhite);
                _Pieces.push_back(rook1);
                Rook* rook2 = new Rook(_IsWhite);
                rook2->moveBoard(Vector2i(7, _IsWhite ? 7 : 0));
                _Board.setBoard(Vector2i(7, _IsWhite ? 7 : 0), _IsWhite);
                _Pieces.push_back(rook2);
            }
            else
            {
                Queen* queen  = new Queen(_IsWhite);
                queen->moveBoard(Vector2i(3, _IsWhite ? 7 : 0));
                _Board.setBoard(Vector2i(3, _IsWhite ? 7 : 0), _IsWhite);
                _Pieces.push_back(queen);
            }
            
            break;
        }
        // STALEMATE DEMONSTRATION
        case 4 :
        {
            if(_IsWhite)
            {
                Queen* queen  = new Queen(_IsWhite);
                queen->moveBoard(Vector2i(1, 3));
                _Pieces.push_back(queen);
            }
            else
            {
                king->moveBoard(Vector2i(0, 0));
            }
            break;
        }
    }

    
}

/**
 * Makes the player plays : update Board and moves the piece
 * @param from Vector of current position
 * @param to Vector of future position
 */
void Player::play(const Vector2i from, const Vector2i to, const Player* Opposite)
{
    getPiece(from)->moveWindow(Vector2f(5555,5555));
    if(_Board.getPiece(to) == -(_Board.getPiece(from)))
        Opposite->getPiece(to)->kill();
        
    _Board.updateBoard(from, to, _IsWhite);
    getPiece(from)->moveBoard(to);
    _IsCheck = false;
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
Piece* Player::getPiece(const double i) const
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
 * @param pawn pawn's adress
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
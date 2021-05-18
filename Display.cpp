#include "Display.hpp"


Display::Display(const string name1, const string name2, const string title)
{
    //Variables initialisation
    _Title = title;
    _Size  = 55;
    _Window.create(VideoMode(_Size*10, _Size*10), _Title, Style::Close);

    //Game initialisation
    _White          = new Player(name1, 1);
    _Black          = new Player(name2, 0);

    _TurnCount      = 0;
    _IsWhiteTurn    = false;
    _Status         = INIT;
    _TextureBoard.loadFromFile("Textures/board.jpg");
    _TextureWhitePlays.loadFromFile("Textures/white_plays.png");
    _TextureBlackPlays.loadFromFile("Textures/black_plays.png");
    _TextureWhiteWins.loadFromFile("Textures/white_wins.png");
    _TextureBlackWins.loadFromFile("Textures/black_wins.png");

    //Sprites init
    _SpriteBoard.setTexture(_TextureBoard);
    _SpriteWhitePlays.setTexture(_TextureWhitePlays);
    _SpriteBlackPlays.setTexture(_TextureBlackPlays);
    _SpriteWhiteWins.setTexture(_TextureWhiteWins);
    _SpriteBlackWins.setTexture(_TextureBlackWins);
}

/**
 * Starts a new game and follow this patern :
 * 0 : update counter and next turn
 * 1 : check for check
 * 2 : check for checkmate
 * 3 : check for pat (in this case it's a draw) : done later
 * 4 : one player plays and window draws the board
 * MORE DETAILS ARE WELCOME
 */
void Display::playGame()
{
    //Variables initialization 
    bool _IsDragged     = false;  
    
    //Stores old position, new position and delta and X and
    Vector2f _DxDy;
    Vector2f _oldPos_Window;
    Vector2i _oldPos_Board;
    Vector2f _newPos_Window;
    Vector2i _newPos_Board;

    Piece* PieceDragged;
    Event event;

    _Status = ACTIVE; 

    // Sets up the window resolution and the window title
    //RenderWindow window(VideoMode(_Size*10, _Size*10), _Title);

    // Loops until the window is closed by the user
    while (_Window.isOpen())
    {   
        while (_Status == ACTIVE)
        {
            /* --------------------------------- */
            /* 0 : updates counter and next turn */
            /* --------------------------------- */
            _TurnCount++;
            _IsWhiteTurn = !_IsWhiteTurn;
            if(_IsWhiteTurn)
            {
                _ActivePlayer   = _White;
                _WaitingPlayer  = _Black;
            }
            else
            {
                _ActivePlayer   = _Black;
                _WaitingPlayer  = _White;
            }   

            /* -------------------- */
            /* 1 : checks for check */
            /* -------------------- */
            isCheck(); //looks for check and update game status and players' status

            /* ------------------------ */
            /* 2 : checks for checkmate */
            /* ------------------------ */
            isCheckMate();
            while(_Status == B_WINS || _Status == W_WINS)
            {
                show(PieceDragged->getSprite(), false, true);
                while(_Window.pollEvent(event))
                
                    if(event.type == Event::Closed)
                    {
                        _Status = STOP;
                        _Window.close();
                    }                   
                }
            

            if (_Window.isOpen())
                _Status = MOVE;


            /* ------------------------ */
            /* 3 : White/Black playing  */
            /* ------------------------ */
            while(_Status == MOVE)
            {
                // Stores the position of the mouse at any time in mouse_pos
                Vector2i mouse_pos = Mouse::getPosition(_Window);

                while (_Window.pollEvent(event))
                {
                    // When the user click o the cross, it closes the window
                    if(event.type == Event::Closed)
                    {
                        _Status = STOP;
                        _Window.close();
                    }

                    // When the mouse left button is pressed, checks if the mouse is hovering one of the pieces.
                    // If so, stores the actual index, the original position of the piece and the distance between 
                    // the mouse and the top left angle of the piece at the moment of the click.
                    if(event.type == Event::MouseButtonPressed)
                    {
                        if(event.mouseButton.button == Mouse::Left)
                        {
                            // for (k = 0; k < 32; k++)
                            // {
                            //     if(_Sprites[k].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                            //     {
                            //         _DraggedPiece = k;
                            //         _oldPos_Window = _Sprites[_DraggedPiece].getPosition();
                            //         _oldPos_Board = Vector2i(_oldPos_Window);
                            //         _oldPos_Board.x = _oldPos_Board.x / _Size - 1;
                            //         _oldPos_Board.y = _oldPos_Board.y / _Size - 1;
                            //         _DxDy = Vector2f(mouse_pos) - _oldPos_Window;
                            //         if(_ActivePlayer->getPiece(_oldPos_Board.x, _oldPos_Board.y) != NULL)
                            //         {
                            //             if(_ActivePlayer->getPiece(_oldPos_Board.x, _oldPos_Board.y)->isAlive())
                            //             {
                            //                 _IsDragged = true;
                            //             }
                            //         }
                            //     }
                            // }

                            for(int i = 0; i < _ActivePlayer->getSize(); i++)
                            {
                                PieceDragged = _ActivePlayer->getPiece(mouse_pos, true);
                                if(PieceDragged != NULL)
                                {
                                    if(PieceDragged->isAlive())
                                    {
                                        _oldPos_Window  = Vector2f(PieceDragged->getX(), PieceDragged->getY());
                                        _oldPos_Board   = Vector2i(PieceDragged->getX(), PieceDragged->getY());
                                        _DxDy = Vector2f(mouse_pos) - _oldPos_Window;
                                        _IsDragged = true;
                                        PieceDragged->setIsDragged(_IsDragged);
                                    }
                                }
                            }
                        }
                    }

                    // If the mouse left button is released, converts the real position (in pixels) into a row/column position,
                    // updates the 2D board matrix (puts a 0 at the old position and the piece's value at the arrival position)
                    if((event.type == Event::MouseButtonReleased) && (_IsDragged == true))
                    {
                        if((event.mouseButton.button == Mouse::Left) && (!(_oldPos_Window.x < 54 || _oldPos_Window.x > 494 || _oldPos_Window.y < 54 || _oldPos_Window.y > 494)))
                        {
                            _newPos_Window  = Vector2f(_Size*int(Vector2f (PieceDragged->getSprite()->getPosition() + Vector2f(_Size/2, _Size/2)).x/_Size), _Size*int(Vector2f (PieceDragged->getSprite()->getPosition() + Vector2f(_Size/2, _Size/2)).y/_Size));
                            _newPos_Board   = Vector2i(_newPos_Window);
                            _newPos_Board.x = _newPos_Board.x / _Size - 1;
                            _newPos_Board.y = _newPos_Board.y / _Size - 1;

                            if(int(_newPos_Window.x) != _oldPos_Window.x || int(_newPos_Window.y) != _oldPos_Window.y)
                            {
                                //if the active piece has been dropped on the playfield
                                if(!(_newPos_Window.x < 54 || _newPos_Window.x > 494 || _newPos_Window.y < 54 || _newPos_Window.y > 494))
                                {
                                    bool moveIsValid = false;
                                    //Tells if the pawn is attacking or not and checks is a white piece is moved over a black one or the other way around
                                    if((PieceDragged->getType() == (_IsWhiteTurn ? 1 : -6)) && (_Board.getPiece(_newPos_Board) == -(_Board.getPiece(_oldPos_Board))))
                                    {
                                        //cout << "This is an attacking pawn" << endl;
                                        moveIsValid = PieceDragged->isMoveValid(_newPos_Board, true);
                                    }
                                    else
                                    {
                                        //cout << "This is not an attacking pawn" << endl;
                                        moveIsValid = PieceDragged->isMoveValid(_newPos_Board);
                                    }

                                    if(moveIsValid)
                                    {   
                                        if(_Board.collisionCheck(_oldPos_Board, _newPos_Board, PieceDragged->getType(), _IsWhiteTurn))
                                        {
                                            //if there is no check currently ....
                                            if (_ActivePlayer->isCheck() == false)
                                            {
                                                _ActivePlayer->play(_oldPos_Board, _newPos_Board);
                                                isCheck();

                                                // and if the move doesn't but the player in check, moves normally
                                                if (!_ActivePlayer->isCheck())
                                                {
                                                    _Status = ACTIVE;
                                                    PieceDragged->moveWindow(Vector2i(5555,5555));
                                                    //If the move is valid and the tile is not empty, kills the piece at this spot
                                                    if(_WaitingPlayer->getPiece(_newPos_Board) != NULL)
                                                        _WaitingPlayer->getPiece(_newPos_Board)->kill();

                                                }
                                                //if the move puts the player in check, moves backward
                                                else
                                                {
                                                    _ActivePlayer->play(_newPos_Board, _oldPos_Board);
                                                    _newPos_Window = _oldPos_Window;
                                                }
                                            }
                                            //else if active player is check
                                            else
                                            {
                                                _ActivePlayer->play(_oldPos_Board, _newPos_Board);
                                                isCheck();

                                                //if after his move he is no longer checked, moves normally
                                                if (_ActivePlayer->isCheck() == false) 
                                                {
                                                    _Status = ACTIVE;
                                                    PieceDragged->moveWindow(Vector2i(5555,5555));
                                                    //If the move is valid and the tile is not empty, kills the piece at this spot
                                                    if(_WaitingPlayer->getPiece(_newPos_Board) != NULL)
                                                        _WaitingPlayer->getPiece(_newPos_Board)->kill();
                                                }
                                                //if he is still checked after his move, backwards the move
                                                else
                                                {        
                                                    _Status = MOVE;
                                                    _ActivePlayer->play(_newPos_Board, _oldPos_Board);
                                                    _newPos_Window = _oldPos_Window;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            //cout << "Collision, move aborted" << endl;
                                            _newPos_Window = _oldPos_Window;
                                        }
                                    }                          
                                    else
                                    {
                                        //cout << "Move is not valid" << endl;
                                        _newPos_Window = _oldPos_Window;
                                    }
                                }
                                else
                                {
                                    //cout << "Not in Playfield" << endl;
                                    _newPos_Window = _oldPos_Window;
                                }
                            }
                            PieceDragged->getSprite()->setPosition(_newPos_Window);
                            _IsDragged = false;
                            PieceDragged->setIsDragged(_IsDragged);
                            //debug();
                        }
                    }
                }

                // This is used during the whole movment (from left button pressed until left button released)
                // It'll move the position of the sprite in real-time during the mouse movement.
                if(_IsDragged)
                {
                    PieceDragged->getSprite()->setPosition(Vector2f(mouse_pos) - _DxDy);
                }
                show(PieceDragged->getSprite(), _IsDragged, false);
            }
        }
    }
}

/**
 * Displays all the sprites
 */
void Display::show(const Sprite* PieceDraggedSprite, const bool _IsDragged, const bool endGame)
{
    // Clears the window
    _Window.clear();

    // Draws the board srpite
    _Window.draw(_SpriteBoard);
    
    // Draws all the whites' sprites
    for (int i = 0; i < (int)_White->getSize(); i++)
    {
        if(_White->getPiece(i)->getIsDragged() == false)
        {
            _Window.draw(*_White->getPiece(i)->getSprite());
        }
        else
        {
            if(_White->getPiece(i)->getIsDragged() == false)
            {
                _Window.draw(*_White->getPiece(i)->getSprite());
            }
        }
    }

    // Draws all the whites' sprites
    for (int i = 0; i < (int)_Black->getSize(); i++)
    {
        if(_Black->getPiece(i)->getIsDragged() == false)
        {
            _Window.draw(*_Black->getPiece(i)->getSprite());
        }
        else
        {
            if(_Black->getPiece(i)->getIsDragged() == false)
            {
                _Window.draw(*_Black->getPiece(i)->getSprite());
            }
        }
    }

    // Draws the piece that is being dragged
    if(_IsDragged == true)
    {
        _Window.draw(*PieceDraggedSprite);
    }

    if(endGame)
    {                 
        if(_Status == B_WINS)
            _Window.draw(_SpriteBlackWins);
        else
            _Window.draw(_SpriteWhiteWins);
    }
    else
    {
        if(_IsWhiteTurn)
        {
            _Window.draw(_SpriteWhitePlays);
        }
        else
        {
            _Window.draw(_SpriteBlackPlays);
        }
    }

    // Displays on screen what has been rendered to the window
    _Window.display();
}

/**
 * Debugging purpose only, prints collisions board and pieces board
 */
void Display::debug() const
{
    // This is for debugging purpose only
    for(int j = 0; j < 8; j++)
    {
        cout << "[";
        for(int i = 0; i < 8; i++)
        {
            if(_Board.getPiece(Vector2i(i, j)) < 0)
                if(i < 7)
                    cout << _Board.getPiece(Vector2i(i, j)) <<"][";
                else
                    cout << _Board.getPiece(Vector2i(i, j)) <<"]";
            else
                if(i < 7)
                    cout << " "<< _Board.getPiece(Vector2i(i, j)) <<"][";
                else
                    cout << " "<< _Board.getPiece(Vector2i(i, j)) <<"]";
        }
        cout << "    ";
        cout << "[";
        for(int i = 0; i < 8; i++)
        {
            if(i < 7)
            {
                if((_Black->getPiece(Vector2i(i, j)) != NULL) && (_Black->getPiece(Vector2i(i, j))->isAlive()))
                    cout << _Black->getPiece(Vector2i(i, j))->getType() << "][";
                else if(_White->getPiece(Vector2i(i, j)) && (_White->getPiece(Vector2i(i, j))->isAlive()))
                    cout << " " << _White->getPiece(Vector2i(i, j))->getType() << "][";
                else
                    cout << " 0][";
            }
            else
            {
                if((_Black->getPiece(Vector2i(i, j)) != NULL) && (_Black->getPiece(Vector2i(i, j))->isAlive()))
                    cout << _Black->getPiece(Vector2i(i, j))->getType() << "]";
                else if((_White->getPiece(Vector2i(i, j)) != NULL) && (_White->getPiece(Vector2i(i, j))->isAlive()))
                    cout << " " << _White->getPiece(Vector2i(i, j))->getType() << "]";
                else
                    cout << " 0]";
            }
        }
        cout << endl;
    }
    cout << "           COLLISIONS                            PIECES"<< endl;
}

/**
 * Tells if someone is in checked, changes games status and updates players' status
 * @returns true if someon eis checked, else false
 */
void Display::isCheck()
{
    //Stores current pieces
    Piece* whitePiece;
    Piece* blackPiece;

    //Stores kings' position
    Vector2i bKing;
    Vector2i wKing;

    //first, looks for both kings and stores their position
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            whitePiece = _White->getPiece(Vector2i(i, j));
            blackPiece = _Black->getPiece(Vector2i(i, j));
            if ((blackPiece != NULL) && (blackPiece->getType() == B_KING))
            {
                bKing.x = i;
                bKing.y = j;
            }
            if ((whitePiece != NULL) && (whitePiece->getType() == W_KING))
            {
                wKing.x = i;
                wKing.y = j;
            }
        }
    }

    //then checks if one of the piece puts a player in check
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // takes the piece
            whitePiece = _White->getPiece(Vector2i(i, j));
            blackPiece = _Black->getPiece(Vector2i(i, j));

            //makes sure it's not a king
            if ((whitePiece != NULL) && (whitePiece->getType() != W_KING))
            {
                //if the piece can reach the king, there is check
                if (whitePiece->isMoveValid(bKing, true)) 
                {
                    if(_Board.collisionCheck(Vector2i(whitePiece->getX(), whitePiece->getY()), bKing, whitePiece->getType(), true))
                    {
                        _Black->setCheck(true);
                        //_Status = CHECK;
                    }
                }
            }

            if ((blackPiece != NULL) && (blackPiece->getType() != B_KING))
            {
                if (blackPiece->isMoveValid(wKing, true))
                {
                    if(_Board.collisionCheck(Vector2i(blackPiece->getX(), blackPiece->getY()), wKing, blackPiece->getType(), false))
                    {
                        _White->setCheck(true);
                        //_Status = CHECK;
                    }   
                }
            }
        }
    }
}

/**
 * Tells if someone is checkmate and update game status
 */
void Display::isCheckMate()
{
    //needs at least someone checked
    if ((_White->isCheck() == false) && (_Black->isCheck() == false)) return;

    //Stores current pieces
    Piece* whitePiece;
    Piece* blackPiece;

    Vector2i blackKing;
    Vector2i whiteKing;

    //stores current position of the king
    Vector2i curPos;

    //stores players status
    int blackPossibleMoves = 8;
    int whitePossibleMoves = 8;

    //first, looks for both kings and stores their position
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            whitePiece = _White->getPiece(Vector2i(i, j));
            blackPiece = _Black->getPiece(Vector2i(i, j));
            if ((blackPiece != NULL) && (blackPiece->getType() == B_KING))
            {
                blackKing.x = i;
                blackKing.y = j;
            }
            if ((whitePiece != NULL) && (whitePiece->getType() == W_KING))
            {
                whiteKing.x = i;
                whiteKing.y = j;
            }
        }
    }

    //both players can't be checkmated at the same time 
    //moves the king one tile in every direction and check if there is somewhere 
    //where it is no longer checked

    //checks if black king is checkmated
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            //no need to check the same spot
            if (i == 0 && j == 0) continue;
            
            //next position of the king : moves virtually but stays on the board
            if(((blackKing.x + i) >= 0) && ((blackKing.x + i) <= 7) && (_Board.getPiece(Vector2i((blackKing.x + i), blackKing.y)) == 0))
                curPos.x = blackKing.x + i;
            else
                curPos.x = blackKing.x;

            if(((blackKing.y + j) >= 0) && ((blackKing.y + j) <= 7) && (_Board.getPiece(Vector2i(blackKing.x, (blackKing.y + j))) == 0))
                curPos.y = blackKing.y + j;
            else
                curPos.y = blackKing.y;

            //checks if any of the piece can reach the king at its new position
            for (int k = 0; k < 8; k++)
            {
                for (int l = 0; l < 8; l++)
                {
                    //gets a piece
                    whitePiece = _White->getPiece(Vector2i(k, l));
                    if (whitePiece != NULL)
                    {
                        //if the move is possible ...
                        if (whitePiece->isMoveValid(curPos, true))
                        {
                            //...and if it can reach the king
                            if (_Board.collisionCheck(Vector2i(whitePiece->getX(), whitePiece->getY()), curPos, whitePiece->getType(), true))
                            {
                                //tile is not safe and this move is not good
                                blackPossibleMoves--;
                            }
                        }
                    }
                }
            }
        }
    }
    //if the king can't move then it's checkmate
    if (blackPossibleMoves <= 0)
    {
        _Status = W_WINS;
        return;
    }

    //checks if white king is checkmated
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            //no need to check the same spot
            if (i == 0 && j == 0) continue;
            
            if(((whiteKing.x + i) >= 0) && ((whiteKing.x + i) <= 7) && (_Board.getPiece(Vector2i((whiteKing.x + i), whiteKing.y)) == 0))
                curPos.x = whiteKing.x + i;
            else
                curPos.x = whiteKing.x;

            if(((whiteKing.y + j) >= 0) && ((whiteKing.y + j) <= 7) && (_Board.getPiece(Vector2i(whiteKing.x, (whiteKing.y + j))) == 0))
                curPos.y = whiteKing.y + j;
            else
                curPos.y = whiteKing.y;

            //checks if any of the piece can reach the king at its new position
            for (int k = 0; k < 8; k++)
            {
                for (int l = 0; l < 8; l++)
                {
                    //gets a piece
                    blackPiece = _Black->getPiece(Vector2i(k, l));
                    if (blackPiece != NULL)
                    {
                        //if the move is possible ...
                        if (blackPiece->isMoveValid(curPos, true))
                        {
                            //...and if it can reach the king
                            if (_Board.collisionCheck(Vector2i(blackPiece->getX(), blackPiece->getY()), curPos, blackPiece->getType(), false))
                            {
                                //tile is not safe and this move is not good
                                whitePossibleMoves--;
                            }
                        }
                    }
                }
            }
        }
    }
    //if the king can't move then it's checkmate
    if (whitePossibleMoves <= 0)
    {
        _Status = B_WINS;
        return;
    }
}

Display::~Display()
{
    delete _White;
    delete _Black;
}

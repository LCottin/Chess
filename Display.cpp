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
    _TexturePromotion.loadFromFile("Textures/promotion.jpg");
    _TexturePromWQ.loadFromFile("Textures/BIG_wq.png");
    _TexturePromWR.loadFromFile("Textures/BIG_wr.png");
    _TexturePromWB.loadFromFile("Textures/BIG_wb.png");
    _TexturePromWKN.loadFromFile("Textures/BIG_wkn.png");
    _TexturePromBQ.loadFromFile("Textures/BIG_bq.png");
    _TexturePromBR.loadFromFile("Textures/BIG_br.png");
    _TexturePromBB.loadFromFile("Textures/BIG_bb.png");
    _TexturePromBKN.loadFromFile("Textures/BIG_bkn.png");

    _TextureWhitePlays.loadFromFile("Textures/white_plays.png");
    _TextureBlackPlays.loadFromFile("Textures/black_plays.png");
    _TextureWhiteWins.loadFromFile("Textures/white_wins.png");
    _TextureBlackWins.loadFromFile("Textures/black_wins.png");

    //Sprites init
    _SpriteBoard.setTexture(_TextureBoard);
    _SpritePromotion.setTexture(_TexturePromotion);
    _SpritePromWQ.setTexture(_TexturePromWQ);
    _SpritePromWR.setTexture(_TexturePromWR);
    _SpritePromWB.setTexture(_TexturePromWB);
    _SpritePromWKN.setTexture(_TexturePromWKN);
    _SpritePromBQ.setTexture(_TexturePromBQ);
    _SpritePromBR.setTexture(_TexturePromBR);
    _SpritePromBB.setTexture(_TexturePromBB);
    _SpritePromBKN.setTexture(_TexturePromBKN);
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

    Color _Alpha(0,0,0,100);
    Color _Full(0,0,0,255);
    _SpritePromWQ.setPosition(65,65);
    _SpritePromWQ.setColor(_Alpha);
    _SpritePromWR.setPosition(285,65);
    _SpritePromWR.setColor(_Alpha);
    _SpritePromWB.setPosition(65,285);
    _SpritePromWB.setColor(_Alpha);
    _SpritePromWKN.setPosition(285,285);
    _SpritePromWKN.setColor(_Alpha);
    _SpritePromBQ.setPosition(65,65);
    _SpritePromBQ.setColor(_Alpha);
    _SpritePromBR.setPosition(285,65);
    _SpritePromBR.setColor(_Alpha);
    _SpritePromBB.setPosition(65,285);
    _SpritePromBB.setColor(_Alpha);
    _SpritePromBKN.setPosition(285,285);
    _SpritePromBKN.setColor(_Alpha);

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
                {
                    if(event.type == Event::Closed)
                    {
                        _Status = STOP;
                        _Window.close();
                    }
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
                            for(int i = 0; i < _ActivePlayer->getSize(); i++)
                            {
                                PieceDragged = _ActivePlayer->getPiece(mouse_pos, true);
                                if(PieceDragged != NULL)
                                {
                                    if(PieceDragged->isAlive())
                                    {
                                        _oldPos_Window  = Vector2f(PieceDragged->getXWindow(), PieceDragged->getYWindow());
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
                                                _ActivePlayer->play(_oldPos_Board, _newPos_Board, _WaitingPlayer);
                                                isCheck();

                                                // and if the move doesn't but the player in check, moves normally
                                                if (!_ActivePlayer->isCheck())
                                                {
                                                    _Status = ACTIVE;
                                                    if((PieceDragged->getType() == (_IsWhiteTurn ? 1 : -6)) && _newPos_Board.y == (_IsWhiteTurn ? 0 : 7))
                                                        _Status = PROMOTION;
                                                }
                                                //if the move puts the player in check, moves backward
                                                else
                                                {
                                                    _Status = MOVE;
                                                    _ActivePlayer->play(_newPos_Board, _oldPos_Board, _WaitingPlayer);
                                                    _newPos_Window = _oldPos_Window;
                                                }
                                            }
                                            //else if active player is check
                                            else
                                            {
                                                _ActivePlayer->play(_oldPos_Board, _newPos_Board, _WaitingPlayer);
                                                isCheck();

                                                //if after his move he is no longer checked, moves normally
                                                if (_ActivePlayer->isCheck() == false) 
                                                {
                                                    _Status = ACTIVE;
                                                    if((PieceDragged->getType() == (_IsWhiteTurn ? 1 : -6)) && _newPos_Board.y == (_IsWhiteTurn ? 0 : 7))
                                                        _Status = PROMOTION;
                                                }
                                                //if he is still checked after his move, backwards the move
                                                else
                                                {        
                                                    _Status = MOVE;
                                                    _ActivePlayer->play(_newPos_Board, _oldPos_Board, _WaitingPlayer);
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
                            if(PieceDragged->isAlive())
                            {
                                PieceDragged->moveWindow(_newPos_Window);
                            }

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
                    PieceDragged->moveWindow(Vector2f(mouse_pos) - _DxDy);
                }
                show(PieceDragged->getSprite(), _IsDragged, false);
            }
        }
        while(_Status == PROMOTION)
        {
            promotion(_IsWhiteTurn);
            while(_Window.pollEvent(event))
            {
                Vector2i mouse_pos = Mouse::getPosition(_Window);
                if(mouse_pos.x>=65 && mouse_pos.x<265 && mouse_pos.y>=65 && mouse_pos.y<=265)
                {
                    if(_IsWhiteTurn)
                        _SpritePromWQ.setColor(_Full);
                    else
                        _SpritePromBQ.setColor(_Full);
                }
                else
                {
                    _SpritePromWQ.setColor(_Alpha);
                    _SpritePromBQ.setColor(_Alpha);
                }
                
                if(mouse_pos.x>=285 && mouse_pos.x<485 && mouse_pos.y>=65 && mouse_pos.y<=265)
                {
                    if(_IsWhiteTurn)
                        _SpritePromWR.setColor(_Full);
                    else
                        _SpritePromBR.setColor(_Full);
                }
                else
                {
                    _SpritePromWR.setColor(_Alpha);
                    _SpritePromBR.setColor(_Alpha);
                }

                if(mouse_pos.x>=65 && mouse_pos.x<265 && mouse_pos.y>=285 && mouse_pos.y<=485)
                {
                    if(_IsWhiteTurn)
                        _SpritePromWB.setColor(_Full);
                    else
                        _SpritePromBB.setColor(_Full);
                }
                else
                {
                    _SpritePromWB.setColor(_Alpha);
                    _SpritePromBB.setColor(_Alpha);
                }

                if(mouse_pos.x>=285 && mouse_pos.x<485 && mouse_pos.y>=285 && mouse_pos.y<=485)
                {
                    if(_IsWhiteTurn)
                        _SpritePromWKN.setColor(_Full);
                    else
                        _SpritePromBKN.setColor(_Full);
                }
                else
                {
                    _SpritePromWKN.setColor(_Alpha);
                    _SpritePromBKN.setColor(_Alpha);
                }
                
                if(event.type == Event::Closed)
                {
                    _Status = STOP;
                    _Window.close();
                }

                if(event.type == Event::MouseButtonReleased)
                {
                    if(mouse_pos.x>=65 && mouse_pos.x<265 && mouse_pos.y>=65 && mouse_pos.y<=265)
                    {
                        _ActivePlayer->promotion(PieceDragged, (_IsWhiteTurn ? 5 : -2));
                        _Status = ACTIVE;
                    }
                    else if(mouse_pos.x>=285 && mouse_pos.x<485 && mouse_pos.y>=65 && mouse_pos.y<=265)
                    {
                        _ActivePlayer->promotion(PieceDragged, (_IsWhiteTurn ? 4 : -3));
                        _Status = ACTIVE;     
                    }
                    else if(mouse_pos.x>=65 && mouse_pos.x<265 && mouse_pos.y>=285 && mouse_pos.y<=485)
                    {
                        _ActivePlayer->promotion(PieceDragged, (_IsWhiteTurn ? 2 : -5));
                        _Status = ACTIVE;   
                    }
                    else if(mouse_pos.x>=285 && mouse_pos.x<485 && mouse_pos.y>=285 && mouse_pos.y<=485)
                    {
                        _ActivePlayer->promotion(PieceDragged, (_IsWhiteTurn ? 3 : -4));
                        _Status = ACTIVE; 
                    }
                }
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
 * Displays promotion screen
 */
void Display::promotion(const bool _IsWhiteTurn)
{
    // Clears the window
    _Window.clear();

    // Draws the promotion background
    _Window.draw(_SpritePromotion);
    
    if(_IsWhiteTurn)
    {
        _Window.draw(_SpritePromWQ);
        _Window.draw(_SpritePromWR);
        _Window.draw(_SpritePromWB);
        _Window.draw(_SpritePromWKN);
    }
    else
    {
        _Window.draw(_SpritePromBQ);
        _Window.draw(_SpritePromBR);
        _Window.draw(_SpritePromBB);
        _Window.draw(_SpritePromBKN);
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
    cout << "           COLLISIONS                            PIECES"<< endl << endl;
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

    vector <Piece*> Wattackers;
    vector <Piece*> Battackers;

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
                                if(curPos == blackKing)
                                {
                                    if(Wattackers.size() == 0)
                                        Wattackers.push_back(whitePiece);
                                    else if(Wattackers.size() > 0)
                                            if(whitePiece != Wattackers.back())
                                                Wattackers.push_back(whitePiece);
                                }
                                //tile is not safe and this move is not good
                                blackPossibleMoves--;
                                cout << blackPossibleMoves << endl;
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
        cout << "Nombre d'attaquants = " << Wattackers.size() << endl;
        if (Wattackers.size() > 1)
        {
            cout << "plus d'un attaquant" << endl;
            _Status = W_WINS;
            return;
        }
        else
        {
            for(int k = 0; k < _Black->getSize(); k++)
            {
                Piece* temp = _Black->getPiece(k);
                cout << "La piece " << temp->getType() << " est testee aux coord x = " << temp->getX() << " y = " << temp->getY() << endl;
                if (temp->isMoveValid(Vector2i(Wattackers[0]->getX(), Wattackers[0]->getY()), true))
                {
                    if (_Board.collisionCheck(Vector2i(temp->getX(), temp->getY()), Vector2i(Wattackers[0]->getX(), Wattackers[0]->getY()), temp->getType(), false))
                    {
                        break;
                    }
                }

                int dx = Wattackers[0]->getX() - blackKing.x;
                int dy = Wattackers[0]->getY() - blackKing.y;

                cout << "dx = " << dx << endl;
                cout << "dy = " << dy << endl;

                if((abs(dx) == 1) && (abs(dy) == 1))
                {
                    cout << "plus d'un attaquant" << endl;
                    _Status = W_WINS;
                    return;
                }
                else
                {
                    int i = 0;
                    int j = 0;
                    bool safeMoveFound = false;
                    while(i != dx && j!= dy && !safeMoveFound)
                    {
                        if (temp->isMoveValid(Vector2i(Wattackers[0]->getX() + i, Wattackers[0]->getY() + j), false))
                        {
                            if (_Board.collisionCheck(Vector2i(temp->getX(), temp->getY()), Vector2i(Wattackers[0]->getX() + i, Wattackers[0]->getY() + j), temp->getType(), false))
                            {
                                safeMoveFound = true;
                            }
                        }
                        if(dx > 0)
                            i++;
                        else if(dx < 0)
                            i--;
                        if(dy > 0)
                            j++;
                        else if (dy < 0)
                            j--;
                                
                        cout << "j = " << j << endl;
                        cout << "i = " << i << endl;
                    }
                }
            }
        }
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
                                if(Battackers.size() == 0)
                                        Battackers.push_back(blackPiece);
                                    else if(Battackers.size() > 0)
                                            if(blackPiece != Battackers.back())
                                                Battackers.push_back(blackPiece);
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
        cout << "Nombre d'attaquants = " << Battackers.size() << endl;
        if (Battackers.size() > 1)
        {
            cout << "plus d'un attaquant" << endl;
            _Status = B_WINS;
            return;
        }
        else
        {
            for(int k = 0; k < _Black->getSize(); k++)
            {
                Piece* temp = _Black->getPiece(k);
                cout << "La piece " << temp->getType() << " est testee aux coord x = " << temp->getX() << " y = " << temp->getY() << endl;
                if (temp->isMoveValid(Vector2i(Battackers[0]->getX(), Battackers[0]->getY()), true))
                {
                    if (_Board.collisionCheck(Vector2i(temp->getX(), temp->getY()), Vector2i(Battackers[0]->getX(), Battackers[0]->getY()), temp->getType(), true))
                    {
                        break;
                    }
                }

                int dx = Battackers[0]->getX() - whiteKing.x;
                int dy = Battackers[0]->getY() - whiteKing.y;

                cout << "dx = " << dx << endl;
                cout << "dy = " << dy << endl;

                if((abs(dx) == 1) && (abs(dy) == 1))
                {
                    _Status = B_WINS;
                    return;
                }
                else
                {
                    int i = 0;
                    int j = 0;
                    bool safeMoveFound = false;
                    while(i != dx && j!= dy && !safeMoveFound)
                    {
                        if (temp->isMoveValid(Vector2i(Battackers[0]->getX() + i, Battackers[0]->getY() + j), false))
                        {
                            if (_Board.collisionCheck(Vector2i(temp->getX(), temp->getY()), Vector2i(Battackers[0]->getX() + i, Battackers[0]->getY() + j), temp->getType(), true))
                            {
                                safeMoveFound = true;
                            }
                        }
                        if(dx > 0)
                            i++;
                        else if(dx < 0)
                            i--;
                        if(dy > 0)
                            j++;
                        else if (dy < 0)
                            j--;
                                
                        cout << "j = " << j << endl;
                        cout << "i = " << i << endl;
                    }
                }
            }
        }
    }
}

Display::~Display()
{
    delete _White;
    delete _Black;
}
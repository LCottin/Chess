#include "Display.hpp"


Display::Display(const string name1, const string name2, const string title)
{
    //Variables initialisation
    _Title = title;
    _Size = 55;
    _Window.create(VideoMode(_Size*10, _Size*10), _Title);

    //Game initialisation
    _White = new Player(name1, 1);
    _Black = new Player(name2, 0);
    _ActivePlayer = _Black;
    // _WaitingPlayer = _White;

    _TurnCount      = 0;
    _IsWhiteTurn    = false;
    _Status         = INIT;

    //textures initialisation
    _TextureBp.loadFromFile("Textures/bp.png");
    _TextureBb.loadFromFile("Textures/bb.png");
    _TextureBkn.loadFromFile("Textures/bkn.png");
    _TextureBr.loadFromFile("Textures/br.png");
    _TextureBq.loadFromFile("Textures/bq.png");
    _TextureBk.loadFromFile("Textures/bk.png");
    _TextureWp.loadFromFile("Textures/wp.png");
    _TextureWb.loadFromFile("Textures/wb.png");
    _TextureWkn.loadFromFile("Textures/wkn.png");
    _TextureWr.loadFromFile("Textures/wr.png");
    _TextureWq.loadFromFile("Textures/wq.png");
    _TextureWk.loadFromFile("Textures/wk.png");
    _TextureBoard.loadFromFile("Textures/board.jpg");
    _TextureWhitePlays.loadFromFile("Textures/white_plays.png");
    _TextureBlackPlays.loadFromFile("Textures/black_plays.png");
    _TextureWhiteWins.loadFromFile("Textures/black_wins.png");
    _TextureBlackWins.loadFromFile("Textures/white_wins.png");

    //Sprites init
    _SpriteBoard.setTexture(_TextureBoard);
    _SpriteWhitePlays.setTexture(_TextureWhitePlays);
    _SpriteBlackPlays.setTexture(_TextureBlackPlays);
    _SpriteWhiteWins.setTexture(_TextureWhiteWins);
    _SpriteBlackWins.setTexture(_TextureBlackWins);
    _SpriteBb.setTexture(_TextureBb);
    _SpriteBp.setTexture(_TextureBp);
    _SpriteBkn.setTexture(_TextureBkn);
    _SpriteBr.setTexture(_TextureBr);
    _SpriteBq.setTexture(_TextureBq);
    _SpriteBk.setTexture(_TextureBk);
    _SpriteWp.setTexture(_TextureWp);
    _SpriteWb.setTexture(_TextureWb);
    _SpriteWkn.setTexture(_TextureWkn);
    _SpriteWr.setTexture(_TextureWr);
    _SpriteWq.setTexture(_TextureWq);
    _SpriteWk.setTexture(_TextureWk);


    // Scans through the board and load the 32 Sprites of both players with the right texture, accordingly with the values stored in the 2D matrix
    int k = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(j > 1 && j < 6) continue;
            int n = 0;
            if(_White->getPiece(i,j) != NULL)
                n = _White->getPiece(i,j)->getType();
            else
                n = _Black->getPiece(i,j)->getType();
            switch(n)
            {
                case -6:
                    _Sprites.push_back(_SpriteBp);
                    break;
                case -5:
                    _Sprites.push_back(_SpriteBb);
                    break;
                case -4:
                    _Sprites.push_back(_SpriteBkn);
                    break;
                case -3:
                    _Sprites.push_back(_SpriteBr);
                    break;
                case -2:
                    _Sprites.push_back(_SpriteBq);
                    break;
                case -1:
                    _Sprites.push_back(_SpriteBk);
                    break;
                case 1:
                    _Sprites.push_back(_SpriteWp);
                    break;
                case 2:
                    _Sprites.push_back(_SpriteWb);
                    break;
                case 3:
                    _Sprites.push_back(_SpriteWkn);
                    break;
                case 4:
                    _Sprites.push_back(_SpriteWr);
                    break;
                case 5:
                    _Sprites.push_back(_SpriteWq);
                    break;
                default :
                    _Sprites.push_back(_SpriteWk);
                    break;
            }
            _Sprites[k].setPosition(_Size*(i+1),_Size*(j+1));
            k++;
        }
    }
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
    int _DraggedPiece   = 0;
    int k               = 0;
    bool _IsDragged     = false;  
    Vector2f _DxDy;
    Vector2f _oldPos_Window;
    Vector2i _oldPos_Board;
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
                _ActivePlayer = _White;
                cout << "White turn" << endl;
            }
            else
            {
                _ActivePlayer = _Black;
                cout << "Black turn" << endl;
            }

            /* -------------------- */
            /* 1 : checks for check */
            /* -------------------- */
            isCheck(); //looks for check and update game status and players' status

            if(_White->isCheck()) //if white is checked
            {
                cout << "White is check" << endl;
            }
            else if(_Black->isCheck()) //else is black is checked
            {
                cout << "Black is check" << endl;
            }

            /* ------------------------ */
            /* 2 : checks for checkmate */
            /* ------------------------ */
            isCheckMate();
            while(_Status == B_WINS || _Status == W_WINS)
            {
                while(_Window.pollEvent(event))
                {
                    if(event.type == Event::Closed)
                    {
                        _Status = STOP;
                        _Window.close();
                        cout << "Window closed" << endl;
                    }
                    show(_DraggedPiece, false, true);                    
                }
            }

            if (_Window.isOpen())
            {
                cout << "Game is still going ..." << endl;
                _Status = MOVE;
            }
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
                            for (k = 0; k < 32; k++)
                            {
                                if(_Sprites[k].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                                {
                                    _DraggedPiece = k;
                                    _oldPos_Window = _Sprites[_DraggedPiece].getPosition();
                                    _oldPos_Board = Vector2i(_oldPos_Window);
                                    _oldPos_Board.x = _oldPos_Board.x / _Size - 1;
                                    _oldPos_Board.y = _oldPos_Board.y / _Size - 1;
                                    _DxDy = Vector2f(mouse_pos) - _oldPos_Window;
                                    if(_ActivePlayer->getPiece(_oldPos_Board.x, _oldPos_Board.y) != NULL)
                                    {
                                        if(_ActivePlayer->getPiece(_oldPos_Board.x, _oldPos_Board.y)->isAlive())
                                        {
                                            _IsDragged = true;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // If the mouse left button is released, converts the real position (in pixels) into a row/column position,
                    // updates the 2D board matrix (puts a 0 at the old position and the piece's value at the arrival position)
                    if((event.type == Event::MouseButtonReleased) && (_IsDragged == true))
                    {
                        // cout << "_oldPos_Window.x : " << _oldPos_Window.x << endl;
                        // cout << "_oldPos_Window.y : " << _oldPos_Window.y << endl;

                        if((event.mouseButton.button == Mouse::Left) && (!(_oldPos_Window.x < 54 || _oldPos_Window.x > 494 || _oldPos_Window.y < 54 || _oldPos_Window.y > 494)))
                        {
                            Vector2f _newPos_Window = Vector2f(_Size*int(Vector2f (_Sprites[_DraggedPiece].getPosition() + Vector2f(_Size/2, _Size/2)).x/_Size), _Size*int(Vector2f (_Sprites[_DraggedPiece].getPosition() + Vector2f(_Size/2, _Size/2)).y/_Size));
                            Vector2i _newPos_Board = Vector2i(_newPos_Window);
                            _newPos_Board.x = _newPos_Board.x / _Size - 1;
                            _newPos_Board.y = _newPos_Board.y / _Size - 1;

                            // cout << "_newPos_Window.x : " << _newPos_Window.x << endl;
                            // cout << "_newPos_Window.y : " << _newPos_Window.y << endl;
                           
                            if(int(_newPos_Window.x) != _oldPos_Window.x || int(_newPos_Window.y) != _oldPos_Window.y)
                            {
                                //if the active piece has been dropped on the playfield
                                if(!(_newPos_Window.x < 54 || _newPos_Window.x > 494 || _newPos_Window.y < 54 || _newPos_Window.y > 494))
                                {
                                    //cout << "Piece dragged is dropped in the playfield" << endl;
                                    Piece* temp = _ActivePlayer->getPiece(_oldPos_Board.x, _oldPos_Board.y);
                                    if(temp != NULL)
                                    {
                                        bool moveIsValid = false;
                                        //Tells if the pawn is attacking or not
                                        if((temp->getType() == (_IsWhiteTurn ? 1 : -6)) && (_Board.getPiece(_newPos_Board.x, _newPos_Board.y) == -(_Board.getPiece(_oldPos_Board.x, _oldPos_Board.y))))
                                        {
                                            //cout << "This is an attacking pawn" << endl;
                                            moveIsValid = temp->isMoveValid(_newPos_Board.x, _newPos_Board.y, true);
                                        }
                                        else
                                        {
                                            //cout << "This is not an attacking pawn" << endl;
                                            moveIsValid = temp->isMoveValid(_newPos_Board.x, _newPos_Board.y);
                                        }

                                        if(moveIsValid)
                                        {   
                                            if(_Board.collisionCheck(_oldPos_Board.x, _oldPos_Board.y, _newPos_Board.x, _newPos_Board.y, temp->getType(), _IsWhiteTurn))
                                            {
                                                //if there is no check currently ....
                                                if (_ActivePlayer->isCheck() == false)
                                                {
                                                    _ActivePlayer->play(_oldPos_Board.x, _oldPos_Board.y, _newPos_Board.x, _newPos_Board.y);
                                                    isCheck();

                                                    // and if the move doesn't but the player in check, moves normally
                                                    if (!_ActivePlayer->isCheck())
                                                    {
                                                        cout << "Active player not checked" << endl;
                                                        _Status = ACTIVE;
                                                        _Sprites[_DraggedPiece].setPosition(5555,5555);
                                                        //If the move is valid and the tile is not empty, kills the piece at this spot
                                                        if(_IsWhiteTurn)
                                                        {
                                                            if(_Black->getPiece(_newPos_Board.x, _newPos_Board.y) != NULL)
                                                            {
                                                                _Black->getPiece(_newPos_Board.x, _newPos_Board.y)->kill();
                                                                for(int i = 0; i < (int)_Sprites.size(); i++)
                                                                {
                                                                    if(_Sprites[i].getGlobalBounds().contains(_newPos_Window.x, _newPos_Window.y))
                                                                    {
                                                                        _Sprites[i].setPosition(9999, 9999);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            if(_White->getPiece(_newPos_Board.x, _newPos_Board.y) != NULL)
                                                            {
                                                                _White->getPiece(_newPos_Board.x, _newPos_Board.y)->kill();
                                                                for(int i = 0; i < (int)_Sprites.size(); i++)
                                                                {
                                                                    if(_Sprites[i].getGlobalBounds().contains(_newPos_Window.x, _newPos_Window.y))
                                                                    {
                                                                        _Sprites[i].setPosition(9999, 9999);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                    //if the move puts the player in check, moves backward
                                                    else
                                                    {
                                                        cout << "Active player is now checked" << endl;
                                                        _ActivePlayer->play(_newPos_Board.x, _newPos_Board.y, _oldPos_Board.x, _oldPos_Board.y);
                                                        _newPos_Window = _oldPos_Window;
                                                    }
                                                }

                                                //else if active player is check
                                                else
                                                {
                                                    cout << "Active player checked" << endl;
                                                    _ActivePlayer->play(_oldPos_Board.x, _oldPos_Board.y, _newPos_Board.x, _newPos_Board.y);
        
                                                    isCheck();

                                                    //if after his move he is no longer checked, moves normally
                                                    if (_ActivePlayer->isCheck() == false) 
                                                    {
                                                        cout << "Active player no more checked" << endl;
                                                        _Status = ACTIVE;
                                                        _Sprites[_DraggedPiece].setPosition(5555,5555);
                                                        if(_IsWhiteTurn)
                                                        {
                                                            if(_Black->getPiece(_newPos_Board.x, _newPos_Board.y) != NULL)
                                                            {
                                                                _Black->getPiece(_newPos_Board.x, _newPos_Board.y)->kill();
                                                                for(int i = 0; i < (int)_Sprites.size(); i++)
                                                                {
                                                                    if(_Sprites[i].getGlobalBounds().contains(_newPos_Window.x, _newPos_Window.y))
                                                                    {
                                                                        _Sprites[i].setPosition(9999, 9999);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            if(_White->getPiece(_newPos_Board.x, _newPos_Board.y) != NULL)
                                                            {
                                                                _White->getPiece(_newPos_Board.x, _newPos_Board.y)->kill();
                                                                for(int i = 0; i < (int)_Sprites.size(); i++)
                                                                {
                                                                    if(_Sprites[i].getGlobalBounds().contains(_newPos_Window.x, _newPos_Window.y))
                                                                    {
                                                                        _Sprites[i].setPosition(9999, 9999);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }

                                                    //if he is still checked after his move, backwards the move
                                                    else
                                                    {        
                                                        cout << "Active player still checked" << endl;        
                                                        _Status = MOVE;
                                                        _ActivePlayer->play(_newPos_Board.x, _newPos_Board.y, _oldPos_Board.x, _oldPos_Board.y);
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
                                        //cout << "Not a player's piece" << endl;
                                        _newPos_Window = _oldPos_Window;
                                    }
                                }
                                else
                                {
                                    //cout << "Not in Playfield" << endl;
                                    _newPos_Window = _oldPos_Window;
                                }
                            }
                            _Sprites[_DraggedPiece].setPosition(_newPos_Window);
                            _IsDragged = false;
                            debug();
                        }
                    }
                }

                // This is used during the whole movment (from left button pressed until left button released)
                // It'll move the position of the sprite in real-time during the mouse movement.
                if(_IsDragged)
                {
                    _Sprites[_DraggedPiece].setPosition(Vector2f(mouse_pos) - _DxDy);
                }
                show(_DraggedPiece, _IsDragged, false);
            }
        }
    }
}

/**
 * Displays all the sprites
 */
void Display::show(const int draggedPiece, const bool _IsDragged, const bool endGame)
{
    // Clears the window
    _Window.clear();

    // Draws the board srpite
    _Window.draw(_SpriteBoard);
    
    // Draws all the 32 pieces' sprites
    for (int i = 0; i < (int)_Sprites.size(); i++)
    {
        if(_IsDragged == false)
        {
            _Window.draw(_Sprites[i]);
        }
        else
        {
            if(i != draggedPiece)
            {
                _Window.draw(_Sprites[i]);
            }
        }
    }
    
    // Draws the piece that is being dragged
    if(_IsDragged == true)
    {
        _Window.draw(_Sprites[draggedPiece]);
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
            if(_Board.getPiece(i, j) < 0)
                if(i < 7)
                    cout << _Board.getPiece(i, j) <<"][";
                else
                    cout << _Board.getPiece(i, j) <<"]";
            else
                if(i < 7)
                    cout << " "<< _Board.getPiece(i, j) <<"][";
                else
                    cout << " "<< _Board.getPiece(i, j) <<"]";
        }
        cout << "    ";
        cout << "[";
        for(int i = 0; i < 8; i++)
        {
            if(i < 7)
            {
                if((_Black->getPiece(i, j) != NULL) && (_Black->getPiece(i, j)->isAlive()))
                    cout << _Black->getPiece(i, j)->getType() << "][";
                else if(_White->getPiece(i, j) && (_White->getPiece(i, j)->isAlive()))
                    cout << " " << _White->getPiece(i, j)->getType() << "][";
                else
                    cout << " 0][";
            }
            else
            {
                if((_Black->getPiece(i, j) != NULL) && (_Black->getPiece(i, j)->isAlive()))
                    cout << _Black->getPiece(i, j)->getType() << "]";
                else if((_White->getPiece(i, j) != NULL) && (_White->getPiece(i, j)->isAlive()))
                    cout << " " << _White->getPiece(i, j)->getType() << "]";
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
    int bKing_x, bKing_y;
    int wKing_x, wKing_y;

    //first, looks for both kings and stores their position
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            whitePiece = _White->getPiece(i, j);
            blackPiece = _Black->getPiece(i, j);
            if ((blackPiece != NULL) && (blackPiece->getType() == B_KING))
            {
                bKing_x = i;
                bKing_y = j;
            }
            if ((whitePiece != NULL) && (whitePiece->getType() == W_KING))
            {
                wKing_x = i;
                wKing_y = j;
            }
        }
    }

    //then checks if one of the piece puts a player in check
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // takes the piece
            whitePiece = _White->getPiece(i, j);
            blackPiece = _Black->getPiece(i, j);

            //makes sure it's not a king
            if ((whitePiece != NULL) && (whitePiece->getType() != W_KING))
            {
                //if the piece can reach the king, there is check
                if (whitePiece->isMoveValid(bKing_x, bKing_y, true)) 
                {
                    if(_Board.collisionCheck(whitePiece->getX(), whitePiece->getY(), bKing_x, bKing_y, whitePiece->getType(), true))
                    {
                        _Black->setCheck(true);
                        //_Status = CHECK;
                    }
                }
            }

            if ((blackPiece != NULL) && (blackPiece->getType() != B_KING))
            {
                if (blackPiece->isMoveValid(wKing_x, wKing_y, true))
                {
                    if(_Board.collisionCheck(blackPiece->getX(), blackPiece->getY(), wKing_x, wKing_y, blackPiece->getType(), false))
                    {
                        _White->setCheck(true);
                        //_Status = CHECK;                    }
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

    cout << "looking for checkmate" << endl;
    //Stores current pieces
    Piece* whitePiece;
    Piece* blackPiece;

    King* whiteKing;
    King* blackKing;

    //stores current position of the king
    int curPos_x, curPos_y;

    //stores players status
    bool blackSafe = true;
    bool whiteSafe = true;
    int blackPossibleMoves = 8;
    int whitePossibleMoves = 8;

    //first, looks for both kings and stores their position
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            whitePiece = _White->getPiece(i, j);
            blackPiece = _Black->getPiece(i, j);
            if ((blackPiece != NULL) && (blackPiece->getType() == B_KING))
            {
                blackKing = (King*)_Black->getPiece(i, j);
            }
            if ((whitePiece != NULL) && (whitePiece->getType() == W_KING))
            {
                whiteKing = (King*)_White->getPiece(i, j);
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
            curPos_x = (whiteKing->getX() + i >= 0 ? whiteKing->getX() + i : whiteKing->getX());
            curPos_x = (whiteKing->getX() + i <= 7 ? whiteKing->getX() + i : whiteKing->getX());
            curPos_y = (whiteKing->getY() + j >= 0 ? whiteKing->getY() + j : whiteKing->getY());
            curPos_y = (whiteKing->getY() + j <= 7 ? whiteKing->getY() + j : whiteKing->getY());
            
            //checks if any of the piece can reach the king at its new position
            for (int k = 0; blackSafe == true && k < 8; k++)
            {
                for (int l = 0; blackSafe == true && l < 8; l++)
                {
                    //gets a piece
                    whitePiece = _White->getPiece(k, l);
                    if (whitePiece != NULL)
                    {
                        //if the move is possible ...
                        if (whitePiece->isMoveValid(curPos_x, curPos_y), true)
                        {
                            //...and if it can reach the king
                            if (_Board.collisionCheck(whitePiece->getX(), whitePiece->getY(), curPos_x, curPos_y, whitePiece->getType(), true) == false)
                            {
                                //tile is not safe and this move is not good
                                blackSafe = false;
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
        cout << "BLACK PLAYER IS CHECKED AND MATED" << endl;
        return;
    }
    
    //checks if white king is checkmated
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            //no need to check the same spot
            if (i == 0 && j == 0) continue;
            
            //next position of the king : moves virtually but stays on the board
            curPos_x = (whiteKing->getX() + i >= 0 ? whiteKing->getX() + i : whiteKing->getX());
            curPos_x = (whiteKing->getX() + i <= 7 ? whiteKing->getX() + i : whiteKing->getX());
            curPos_y = (whiteKing->getY() + j >= 0 ? whiteKing->getY() + j : whiteKing->getY());
            curPos_y = (whiteKing->getY() + j <= 7 ? whiteKing->getY() + j : whiteKing->getY());
            
            //checks if any of the piece can reach the king at its new position
            for (int k = 0; whiteSafe == true && k < 8; k++)
            {
                for (int l = 0; whiteSafe == true && l < 8; l++)
                {
                    //gets a piece
                    blackPiece = _White->getPiece(k, l);
                    if (blackPiece != NULL)
                    {
                        //if the move is possible ...
                        if (blackPiece->isMoveValid(curPos_x, curPos_y), true)
                        {
                            //...and if it can reach the king
                            if (_Board.collisionCheck(blackPiece->getX(), blackPiece->getY(), curPos_x, curPos_y, blackPiece->getType(), true) == false)
                            {
                                //tile is not safe and this move is not good
                                whiteSafe = false;
                                whitePossibleMoves--;
                            }
                        }
                    }
                }
            }
        }
    }
    //if the king can't move then it's checkmate
    if (whiteSafe <= 0)
    {
        _Status = B_WINS;
        cout << "WHITE PLAYER IS CHECKED AND MATED" << endl;
        return;
    }
}

Display::~Display()
{
    delete _White;
    delete _Black;
}

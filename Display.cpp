#include "Display.hpp"


Display::Display(const string name1, const string name2, const string title)
{
    //Variables initialisation
    _Title = title;
    _Size = 55;

    //Game initialisation
    _White = new Player(name1, 1);
    _Black = new Player(name2, 0);
    _ActivePlayer = _Black;

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

    //Sprites init
    _SpriteBoard.setTexture(_TextureBoard);
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
    int n           = 0;
    int k           = 0;
    bool _IsDragged = false;  
    Vector2f _DxDy;
    Vector2f _oldPos_Window;
    Vector2i _oldPos_Board;

    _Status = ACTIVE; 

    // Sets up the window resolution and the window title
    RenderWindow window(VideoMode(_Size*10, _Size*10), _Title);

    // Loops until the window is closed by the user
    while (window.isOpen())
    {   
        while (_Status == ACTIVE)
        {
            /* --------------------------------- */
            /* 0 : updates counter and next turn */
            /* -------------------------------- */
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
                cout << "Black" << endl;
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
            _Status = isCheckMate();
            if(_Status == B_WINS || _Status == W_WINS)
            {
                //when someone won, stops the loop to print congrats
                break;
            }

            /* ------------------ */
            /* 3 : checks for pat */
            /* ------------------ */
            //will be done later ...

            /* ---------------------------------------------------------------------- */
            /* 4 : one player plays according to the previous steps (including check) */
            /* ---------------------------------------------------------------------- */

            _Status = MOVE;

            Event event;
            while (_Status == MOVE)
            {
                // Stores the position of the mouse at any time in mouse_pos
                Vector2i mouse_pos = Mouse::getPosition(window);

                while (window.pollEvent(event))
                {
                    // When the user click o the cross, it closes the window
                    if(event.type == Event::Closed)
                    {
                        _Status = STOP;
                        window.close();
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
                                    n = k;
                                    _oldPos_Window = _Sprites[n].getPosition();
                                    _oldPos_Board = Vector2i(_oldPos_Window);
                                    _oldPos_Board.x = _oldPos_Board.x / 55 - 1;
                                    _oldPos_Board.y = _oldPos_Board.y / 55 - 1;
                                    _DxDy = Vector2f(mouse_pos) - _oldPos_Window;
                                    if(_ActivePlayer->getPiece(_oldPos_Board.x, _oldPos_Board.y) != NULL)
                                    {
                                        _IsDragged = true;
                                    }
                                        
                                }
                            }
                        }
                    }

                    // If the mouse left button is released, converts the real position (in pixels) into a row/column position,
                    // updates the 2D board matrix (puts a 0 at the old position and the piece's value at the arrival position)
                    if(event.type == Event::MouseButtonReleased)
                    {
                        if(event.mouseButton.button == Mouse::Left)
                        {
                            Vector2f _newPos_Window = Vector2f(_Size*int(Vector2f (_Sprites[n].getPosition() + Vector2f(_Size/2, _Size/2)).x/_Size), _Size*int(Vector2f (_Sprites[n].getPosition() + Vector2f(_Size/2, _Size/2)).y/_Size));
                            Vector2i _newPos_Board = Vector2i(_newPos_Window);
                            _newPos_Board.x = _newPos_Board.x / 55 - 1;
                            _newPos_Board.y = _newPos_Board.y / 55 - 1;
                           
                            if(int(_newPos_Window.x) != _oldPos_Window.x || int(_newPos_Window.y) != _oldPos_Window.y)
                            {
                                //if the active piece has been dropped on the playfield
                                if(!(_newPos_Window.x < 54 || _newPos_Window.x > 494 || _newPos_Window.y < 54 || _newPos_Window.y > 494))
                                {
                                    cout << "Piece dragged is dropped in the playfield" << endl;
                                    Piece* temp = _ActivePlayer->getPiece(_oldPos_Board.x, _oldPos_Board.y);
                                    if(temp != NULL)
                                    {
                                        bool moveIsValid = false;
                                        //Tells if the pawn is attacking or not
                                        if((temp->getType() == (_IsWhiteTurn ? 1 : -6)) && (_Board.getPiece(_newPos_Board.x, _newPos_Board.y) == -(_Board.getPiece(_oldPos_Board.x, _oldPos_Board.y))))
                                        {
                                            cout << "This is an attacking pawn" << endl;
                                            moveIsValid = temp->isMoveValid(_newPos_Board.x, _newPos_Board.y, true);
                                        }
                                        else
                                        {
                                            cout << "This is not an attacking pawn" << endl;
                                            moveIsValid = temp->isMoveValid(_newPos_Board.x, _newPos_Board.y);
                                        }

                                        if(moveIsValid)
                                        {   
                                            if(_Board.collisionCheck(_oldPos_Board.x, _oldPos_Board.y, _newPos_Board.x, _newPos_Board.y, temp->getType(), _IsWhiteTurn))
                                            {
                                                //If the move is valid and the tile is not empty, kills the piece at this spot
                                                if(_IsWhiteTurn)
                                                {
                                                    if(_Black->getPiece(_newPos_Board.x, _newPos_Board.y) != NULL)
                                                        _Black->getPiece(_newPos_Board.x, _newPos_Board.y)->kill();
                                                }
                                                else
                                                {
                                                    if(_White->getPiece(_newPos_Board.x, _newPos_Board.y) != NULL)
                                                        _White->getPiece(_newPos_Board.x, _newPos_Board.y)->kill();
                                                }
                                                _ActivePlayer->play(_oldPos_Board.x, _oldPos_Board.y, _newPos_Board.x, _newPos_Board.y);
                                                _Status = ACTIVE;
                                            }
                                            else
                                            {
                                                cout << "Collision, move aborted" << endl;
                                                _newPos_Window = _oldPos_Window;
                                            }
                                        }                          
                                        else
                                        {
                                            cout << "Move is not valid" << endl;
                                            _newPos_Window = _oldPos_Window;
                                        }
                                    }
                                    else
                                    {
                                        cout << "Not a player's piece" << endl;
                                        _newPos_Window = _oldPos_Window;
                                    }
                                }
                                else
                                {
                                    cout << "Not in Playfield" << endl;
                                    _newPos_Window = _oldPos_Window;
                                }
                            }
                            _Sprites[n].setPosition(_newPos_Window);
                            
                            // This is for debugging purpose only (each time a piece is moved, output the 2D Matrix)
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
                                cout << endl;
                            }
                            cout << endl;
                            _IsDragged = false;
                        }
                    }
                }

            // This is used during the whole movment (from left button pressed until left button released)
            // It'll move the position of the sprite in real-time during the mouse movement.
            if(_IsDragged)
            {
                _Sprites[n].setPosition(Vector2f(mouse_pos) - _DxDy);
            }

            // Clears the window
            window.clear();

            // Draws the board srpite
            window.draw(_SpriteBoard);
            
            // Draws all the 32 pieces' sprites
            for (int i = 0; i < (int)_Sprites.size(); i++)
            {
                if(_IsDragged == false)
                {
                    window.draw(_Sprites[i]);
                }
                else
                {
                    if(i != n)
                    {
                        window.draw(_Sprites[i]);
                    }
                }
            }
            
            // Draws the piece that is being dragged
            if(_IsDragged == true)
            {
                window.draw(_Sprites[n]);
            }

            // Displays on screen what has been rendered to the window
            window.display();
            }
        }
    }
}


/**
 * Tells if someone is in checked, changes games status and updates players' status
 * @brief TODO !!
 * @returns New game status (ACTIVE or CHECK)
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
                if (whitePiece->isMoveValid(bKing_x, bKing_y)) 
                { 
                    _Black->setCheck(true);
                    _Status = CHECK;
                }
            }

            if ((blackPiece != NULL) && (blackPiece->getType() != B_KING))
            {
                if (blackPiece->isMoveValid(wKing_x, wKing_y))
                {
                    _White->setCheck(true);
                    _Status = CHECK;
                }   
            }
        }
    }
}

/**
 * Tells if someone is checkmate and update game status
 * @brief TODO !!
 * @returns New game status (ACTIVE or B/W WINS)
 */
GAMESTATUS Display::isCheckMate()
{
    //needs at least someone checked
    if (_Status != CHECK) return _Status;

    //default
    return _Status;
}

Display::~Display()
{
    delete _White;
    delete _Black;
}

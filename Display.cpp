#include "Display.hpp"


Display::Display()
{
    _Board = new Board();


    //Variables initialisation
    _IsDragged = false;   
    _Dx = 0;
    _Dy = 0;
    _OldPosX = 0;
    _OldPosY = 0;
    _Size = 55;
    k = 0;
    n = 0;

    //textures initialisation
    texture_bp.loadFromFile("Textures/bp.png");
    texture_bb.loadFromFile("Textures/bb.png");
    texture_bkn.loadFromFile("Textures/bkn.png");
    texture_br.loadFromFile("Textures/br.png");
    texture_bq.loadFromFile("Textures/bq.png");
    texture_bk.loadFromFile("Textures/bk.png");
    texture_wp.loadFromFile("Textures/wp.png");
    texture_wb.loadFromFile("Textures/wb.png");
    texture_wkn.loadFromFile("Textures/wkn.png");
    texture_wr.loadFromFile("Textures/wr.png");
    texture_wq.loadFromFile("Textures/wq.png");
    texture_wk.loadFromFile("Textures/wk.png");
    texture_board.loadFromFile("Textures/board.jpg");

    //Sprites init
    sprite_board.setTexture(texture_board);
    sprite_bb.setTexture(texture_bb);
    sprite_bp.setTexture(texture_bp);
    sprite_bkn.setTexture(texture_bkn);
    sprite_br.setTexture(texture_br);
    sprite_bq.setTexture(texture_bq);
    sprite_bk.setTexture(texture_bk);
    sprite_wp.setTexture(texture_wp);
    sprite_wb.setTexture(texture_wb);
    sprite_wkn.setTexture(texture_wkn);
    sprite_wr.setTexture(texture_wr);
    sprite_wq.setTexture(texture_wq);
    sprite_wk.setTexture(texture_wk);


    // Scan through the board and load the 32 Sprites of both players with the right texture, accordingly with the values stored in the 2D matrix
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            int n = _Board->getInitPiece(i, j);
            if (n == 0) continue;
            switch (n)
            {
                case -6:
                    _Pieces.push_back(sprite_bp);
                    break;
                case -5:
                    _Pieces.push_back(sprite_bb);
                    break;
                case -4:
                    _Pieces.push_back(sprite_bkn);
                    break;
                case -3:
                    _Pieces.push_back(sprite_br);
                    break;
                case -2:
                    _Pieces.push_back(sprite_bq);
                    break;
                case -1:
                    _Pieces.push_back(sprite_bk);
                    break;
                case 1:
                    _Pieces.push_back(sprite_wp);
                    break;
                case 2:
                    _Pieces.push_back(sprite_wb);
                    break;
                case 3:
                    _Pieces.push_back(sprite_wkn);
                    break;
                case 4:
                    _Pieces.push_back(sprite_wr);
                    break;
                case 5:
                    _Pieces.push_back(sprite_wq);
                    break;
                default :
                    _Pieces.push_back(sprite_wk);
                    break;
            }
            _Pieces[k].setPosition(_Size*(j+1),_Size*(i+1));
            k++;
        }
    }
}

/**
 * Draw the board on the screen
 */
void Display::show()
{

    // Set up the window resolution and the window title
    RenderWindow window(VideoMode(550, 550), "ChessGame");

    // Loop until the window is closed by the user
    while (window.isOpen())
    {   
        // Store the position of the mouse at any time in mouse_pos
        Vector2i mouse_pos = Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            // When the user click o the cross, it closes the window
            if (event.type == Event::Closed)
                window.close();
            
            // When the mouse left button is pressed, checks if the mouse is hovering one of the pieces.
            // If so, stores the actual index, the original position of the piece and the distance between 
            // the mouse and the top left angle of the piece at the moment of the click.
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    for (k = 0; k < 32; k++)
                    {
                        if (_Pieces[k].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                        {
                            n = k;
                            _IsDragged = true;

                            _OldPosX = _Pieces[n].getPosition().x;
                            _OldPosY = _Pieces[n].getPosition().y;
                            _Dx = mouse_pos.x - _OldPosX;
                            _Dy = mouse_pos.y - _OldPosY;
                        }
                    }
                }
            }

            // If the mouse left button is released, converts the real position (in pixels) into a row/column position,
            // updates the 2D board matrix (puts a 0 at the old position and the piece's value at the arrival position)
            if (event.type == Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2f newPos = Vector2f(_Size*int(Vector2f (_Pieces[n].getPosition() + Vector2f(_Size/2, _Size/2)).x/_Size), _Size*int(Vector2f (_Pieces[n].getPosition() + Vector2f(_Size/2, _Size/2)).y/_Size));
                    _Pieces[n].setPosition(newPos);

                    cout << int(newPos.x) << endl;
                    cout << int(newPos.y)  << endl;
                    cout << _OldPosX << endl;
                    cout << _OldPosY << endl;

                    if (int(newPos.x) != _OldPosX || int(newPos.y) != _OldPosY)
                    {
                        int temp = _Board->getPiece(int(_OldPosY/55) - 1, int(_OldPosX/55) - 1);
                        _Board->setPiece(int(newPos.y/55) - 1, int(newPos.x/55) - 1, temp);
                        _Board->setPiece(int(_OldPosY/55) - 1, int(_OldPosX/55) - 1, 0);
                    }
                    
                    // This is for debugging purpose only (each time a piece is moved, output the 2D Matrix)
                    for(int i = 0; i < 8; i++)
                    {
                        cout << "[";
                        for(int j = 0; j < 8; j++)
                        {
                            if (_Board->getPiece(i, j) < 0)
                                if (j < 7)
                                    cout << _Board->getPiece(i, j) <<"][";
                                else
                                    cout << _Board->getPiece(i, j) <<"]";
                            else
                                if (j < 7)
                                    cout << " "<< _Board->getPiece(i, j) <<"][";
                                else
                                    cout << " "<< _Board->getPiece(i, j) <<"]";
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
        if (_IsDragged)
        {
            _Pieces[n].setPosition(mouse_pos.x - _Dx, mouse_pos.y - _Dy);
        }

        // Clears the window
        window.clear();

        // Draws the board srpite
        window.draw(sprite_board);

        // Draws all the 32 pieces' sprites
        for (int i = 0; i < _Pieces.size(); i++)
        {
            if (_IsDragged == false)
                //if (Piece[i].isAlive())
                    window.draw(_Pieces[i]);
            else
                if (i != n)
                //if (Piece[i].isAlive())
                    window.draw(_Pieces[i]);
        }
        
        // Draw the piece that is being dragged
        if (_IsDragged == true)
            window.draw(_Pieces[n]);
            
        // Display on screen what has been rendered to the window
        window.display();

    }
}

Display::~Display()
{
}

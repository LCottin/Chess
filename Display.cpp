#include "Display.hpp"


Display::Display(const string title)
{
    _Title = title;

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


    // Scan through the board and load the 32 Sprites of both players with the right texture, accordingly with the values stored in the 2D matrix
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            int n = _Board->getInitPiece(i, j);
            if (n == 0) continue;
            switch (n)
            {
                case -6:
                    _Pieces.push_back(_SpriteBp);
                    break;
                case -5:
                    _Pieces.push_back(_SpriteBb);
                    break;
                case -4:
                    _Pieces.push_back(_SpriteBkn);
                    break;
                case -3:
                    _Pieces.push_back(_SpriteBr);
                    break;
                case -2:
                    _Pieces.push_back(_SpriteBq);
                    break;
                case -1:
                    _Pieces.push_back(_SpriteBk);
                    break;
                case 1:
                    _Pieces.push_back(_SpriteWp);
                    break;
                case 2:
                    _Pieces.push_back(_SpriteWb);
                    break;
                case 3:
                    _Pieces.push_back(_SpriteWkn);
                    break;
                case 4:
                    _Pieces.push_back(_SpriteWr);
                    break;
                case 5:
                    _Pieces.push_back(_SpriteWq);
                    break;
                default :
                    _Pieces.push_back(_SpriteWk);
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
    RenderWindow window(VideoMode(550, 550), _Title);

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
        window.draw(_SpriteBoard);

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

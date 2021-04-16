#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Piece.hpp"

using namespace sf;
using namespace std;

// Initialize array of 32 pieces (16 for each players)
Sprite pieces[32];

// Initialize 2D array (8x8) representing the chess board
int board[8][8] = {                                          
    {-3,-4,-5,-2,-1,-5,-4,-3},
    {-6,-6,-6,-6,-6,-6,-6,-6},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 1, 1, 1, 1, 1, 1, 1},
    { 4, 3 ,2 ,5, 6, 2, 3, 4}};

int main(int argc, char* const argv[])
{
    Game* game = new Game("Thomas", "Léonard");
    delete game;


    // This boolean variable is used for the drag'n'drop feature (True if a piece is being dragged)
    bool isDragged = false;                

    // These float variables are used for the positionning of the pieces during the drag'n'drop
    // oldPos_x and oldPos_y are the position of the dragged piece at the time it's being grabbed (used to update the board matrix)
    // dx and dy will be used to store the distance between the mouse and the real position of the piece being grabbed (used for the visual animation)
               
    float dx = 0, dy = 0, oldPos_x = 0, oldPos_y = 0;

    // Set up the window resolution and the window title
    RenderWindow window(VideoMode(550, 550), "ChessGame");
    
    // Texture initializations
    Texture texture_board, texture_bp, texture_bb, texture_bkn, texture_br, texture_bk, texture_bq, texture_wp, texture_wb, texture_wkn, texture_wr, texture_wq, texture_wk;
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

    // Create a sprite from the board texture
    Sprite sprite_board(texture_board);

    // Those 2 variables are used in for
    int k = 0, n = 0;

    // This variable represents the size of the pieces in the game (related to the size of each images 55x55 px²)
    int size = 55;

    // Scan through the board and load the 32 Sprites of both players with the right texture, accordingly with the values stored in the 2D matrix
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            int n = board[i][j];
            if (n == 0) continue;
            switch (n)
            {
                case -6:
                    pieces[k].setTexture(texture_bp);
                    break;
                case -5:
                    pieces[k].setTexture(texture_bb);
                    break;
                case -4:
                    pieces[k].setTexture(texture_bkn);
                    break;
                case -3:
                    pieces[k].setTexture(texture_br);
                    break;
                case -2:
                    pieces[k].setTexture(texture_bq);
                    break;
                case -1:
                    pieces[k].setTexture(texture_bk);
                    break;
                case 1:
                    pieces[k].setTexture(texture_wp);
                    break;
                case 2:
                    pieces[k].setTexture(texture_wb);
                    break;
                case 3:
                    pieces[k].setTexture(texture_wkn);
                    break;
                case 4:
                    pieces[k].setTexture(texture_wr);
                    break;
                case 5:
                    pieces[k].setTexture(texture_wq);
                    break;
                default :
                    pieces[k].setTexture(texture_wk);
                    break;
            }
            pieces[k].setPosition(size*(j+1),size*(i+1));
            k++;
        }
    }

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
                if (event.mouseButton.button == Mouse::Left)
                {
                    for (k=0; k<32; k++)
                    {
                        if (pieces[k].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                        {
                            n = k;
                            isDragged = true;

                            oldPos_x = pieces[n].getPosition().x;
                            oldPos_y = pieces[n].getPosition().y;
                            dx = mouse_pos.x - oldPos_x;
                            dy = mouse_pos.y - oldPos_y;
                        }
                    }
                }

            // If the mouse left button is released, converts the real position (in pixels) into a row/column position,
            // updates the 2D board matrix (puts a 0 at the old position and the piece's value at the arrival position)
            if (event.type == Event::MouseButtonReleased)
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2f newPos = Vector2f(size*int(Vector2f (pieces[n].getPosition() + Vector2f(size/2, size/2)).x/size), size*int(Vector2f (pieces[n].getPosition() + Vector2f(size/2, size/2)).y/size));
                    pieces[n].setPosition(newPos);
                    board[int(newPos.y/55) - 1][int(newPos.x/55) - 1] = board[int(oldPos_y/55) - 1][int(oldPos_x/55) - 1];
                    board[int(oldPos_y/55) - 1][int(oldPos_x/55) - 1] = 0;

                    // This is for debugging purpose only (each time a piece is moved, output the 2D Matrix)
                    for(int i=0;i<8;i++)
                    {
                        std::cout << "[";
                        for(int j=0;j<8;j++)
                        {
                            if (board[i][j] < 0)
                                if (j < 7)
                                    cout << board[i][j] <<"][";
                                else
                                    cout << board[i][j] <<"]";
                            else
                                if (j < 7)
                                    cout << " "<< board[i][j] <<"][";
                                else
                                    cout << " "<< board[i][j] <<"]";
                        }
                        cout << endl;
                    }
                    cout << endl;
                    isDragged = false;
                }
        }

        // This is used during the whole movment (from left button pressed until left button released)
        // It'll move the position of the sprite in real-time during the mouse movement.
        if (isDragged)
        {
            pieces[n].setPosition(mouse_pos.x - dx, mouse_pos.y - dy);
        }

        // Clears the window
        window.clear();

        // Draws the board srpite
        window.draw(sprite_board);

        // Draws all the 32 pieces' sprites
        for (int i=0; i<32; i++) window.draw(pieces[i]);;

        // Display on screen what has been rendered to the window
        window.display();

    }
    return 0;
}
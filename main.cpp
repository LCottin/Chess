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

Sprite pieces[32];

int board[8][8] = 
    {{-3,-4,-5,-2,-1,-5,-4,-3},
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

    bool isDragged = false;
    float dx = 0, dy = 0;

    RenderWindow window(VideoMode(550, 550), "ChessGame");
    
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

    Sprite sprite_board(texture_board);

    int k, n=0;
    int size = 55;

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            int n = board[i][j];
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
                case 6:
                    pieces[k].setTexture(texture_wk);
                    break;
                default:
                    continue;
            }
            pieces[k].setPosition(size*(j+1),size*(i+1));
            k++;
        }
    }


    while (window.isOpen())
    {
        Vector2i mouse_pos = Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            
            if (event.type == Event::MouseButtonPressed)
                if (event.mouseButton.button == Mouse::Left)
                    for (n=0; n<32; n++)
                    {
                        if (pieces[n].getGlobalBounds().contains(dx, dy))
                        {
                            isDragged = true;
                            dx = mouse_pos.x - pieces[n].getPosition().x;
                            dy = mouse_pos.y - pieces[n].getPosition().y;
                        }
                    }

            if (event.type == Event::MouseButtonReleased)
                if (event.mouseButton.button == Mouse::Left)
                    isDragged = false;
        }

        if (isDragged)
        {
            pieces[n].setPosition(mouse_pos.x - dx, mouse_pos.y - dy);
        }

        window.clear();
        window.draw(sprite_board);
        for (int i=0; i<32; i++) window.draw(pieces[i]);;
        window.display();
    }
    return 0;
}

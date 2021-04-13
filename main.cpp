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

int main(int argc, char* const argv[])
{
    Game* game = new Game("Thomas", "Léonard");
    delete game;

    sf::RenderWindow window(sf::VideoMode(600, 600), "ChessGame");
    
    sf::Texture texture1;
    texture1.loadFromFile("Textures/board.jpg");

    sf::Sprite sprites(texture1);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprites);
        window.display();
    }

    return 0;
}

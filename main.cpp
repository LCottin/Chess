#include <iostream>
#include <string>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Piece.hpp"

int main(int argc, char const *argv[])
{
    Game* game = new Game("Thomas", "Léonard");
    delete game;
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Display.hpp"

using namespace sf;
using namespace std;

int main(int argc, char* const argv[])
{
    Display* _dis = new Display("Thomas", "Léonard");
    _dis->playGame();
    delete _dis;
    return 0;
}
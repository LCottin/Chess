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
    Display* _dis;

    if(argv[1] == NULL)
        _dis = new Display("Thomas", "Léonard", NORMAL);
    else
    {
        switch(atoi(argv[1]))
        {
            case 1 :
                _dis = new Display("Thomas", "Léonard", PROMO);
                break;

            case 2 :
                _dis = new Display("Thomas", "Léonard", EN_PASSANT);
                break;

            case 3 :
                _dis = new Display("Thomas", "Léonard", CASTLE);
                break;

            case 4 :
                _dis = new Display("Thomas", "Léonard", STALEMATE);
                break;

            default :
                _dis = new Display("Thomas", "Léonard", NORMAL);
                break;
        }
    }
    
    _dis->playGame();
    delete _dis;
    return 0;
}
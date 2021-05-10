#ifndef __DISPLAY__
#define __DISPLAY__

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GameStatus.hpp"
#include "Board.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

class Display
{
    private:
        
    //Drawing variables
        //title of the window
        string _Title;

        //vector of pieces of each player
        vector <Sprite> _Sprites;

        //Textures initialization
        Texture _TextureBoard, _TextureBp, _TextureBb, _TextureBkn, _TextureBr, _TextureBk, _TextureBq, _TextureWp, _TextureWb, _TextureWkn, _TextureWr, _TextureWq, _TextureWk;
    
        //Sprites initializations
        Sprite _SpriteBoard, _SpriteBb, _SpriteBp, _SpriteBkn, _SpriteBr, _SpriteBq, _SpriteBk, _SpriteWp, _SpriteWb, _SpriteWkn, _SpriteWr, _SpriteWq, _SpriteWk;
        int _Size;

    //Game variables
        Player*     _White;         //white player
        Player*     _Black;         //black player
        Player*     _ActivePlayer;  //active player
        int         _TurnCount;     //how many turns have been played
        bool        _IsWhiteTurn;   //indicates who's turn it is
        GAMESTATUS  _Status;        //stores current status of the game     

    public:
        Display(const string name1, const string name2, const string title = "ChessGame");
        void playGame();
        GAMESTATUS isCheck();
        GAMESTATUS isCheckMate();
        ~Display();
};


#endif
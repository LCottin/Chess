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
        RenderWindow _Window;

        //Textures initialization
        Texture _TextureBoard, _TextureWhitePlays, _TextureBlackPlays, _TextureWhiteWins, _TextureBlackWins;
        Texture _TexturePromotion, _TexturePromWQ, _TexturePromWR, _TexturePromWB, _TexturePromWKN, _TexturePromBQ, _TexturePromBR, _TexturePromBB, _TexturePromBKN;
    
        //Sprites initializations
        Sprite _SpriteBoard, _SpriteWhitePlays, _SpriteBlackPlays, _SpriteWhiteWins, _SpriteBlackWins; 
        Sprite _SpritePromotion, _SpritePromWQ, _SpritePromWR, _SpritePromWB, _SpritePromWKN, _SpritePromBQ, _SpritePromBR, _SpritePromBB, _SpritePromBKN;
        
        int _Size;

    //Game variables
        Player*     _White;         //white player
        Player*     _Black;         //black player
        Player*     _ActivePlayer;  //active player
        Player*     _WaitingPlayer;  //waiting player
        int         _TurnCount;     //how many turns have been played
        bool        _IsWhiteTurn;   //indicates who's turn it is
        GAMESTATUS  _Status;        //stores current status of the game     

    public:
        Display(const string name1, const string name2, const string title = "ChessGame");
        void playGame();
        void isCheck();
        void isCheckMate();
        void debug() const;
        void show(const Sprite* PieceDragged, const bool _IsDragged, const bool endGame);
        void promotion();
        ~Display();
};


#endif
#ifndef __DISPLAY__
#define __DISPLAY__

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Board.hpp"

using namespace std;
using namespace sf;

class Display
{
    private:
        
        //new board 
        //extern Board _Board;

        //title of the window
        string _Title;

        //vector of pieces of each player
        vector <Sprite> _Pieces;

        // This boolean variable is used for the drag'n'drop feature (True if a piece is being dragged)
        bool _IsDragged;     

        //Stores old position
        float _OldPosX, _OldPosY;

        //Stores dx and dy
        float _Dx, _Dy;

        //Textures initialization
        Texture _TextureBoard, _TextureBp, _TextureBb, _TextureBkn, _TextureBr, _TextureBk, _TextureBq, _TextureWp, _TextureWb, _TextureWkn, _TextureWr, _TextureWq, _TextureWk;
    
        //Sprites initializations
        Sprite _SpriteBoard, _SpriteBb, _SpriteBp, _SpriteBkn, _SpriteBr, _SpriteBq, _SpriteBk, _SpriteWp, _SpriteWb, _SpriteWkn, _SpriteWr, _SpriteWq, _SpriteWk;
        int _Size;
        int k, n;

    public:
        Display(const string title = "ChessGame");
        void show();
        ~Display();
};


#endif
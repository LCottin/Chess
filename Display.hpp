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
        Board* _Board;

        //vector of pieces of each player
        vector <Sprite> _Pieces;

        // This boolean variable is used for the drag'n'drop feature (True if a piece is being dragged)
        bool _IsDragged;     

        //Stores old position
        float _OldPosX, _OldPosY;

        //Stores dx and dy
        float _Dx, _Dy;

        //Textures initialization
        Texture texture_board, texture_bp, texture_bb, texture_bkn, texture_br, texture_bk, texture_bq, texture_wp, texture_wb, texture_wkn, texture_wr, texture_wq, texture_wk;
    
        //Sprites initializations
        Sprite sprite_board, sprite_bb, sprite_bp, sprite_bkn, sprite_br, sprite_bq, sprite_bk, sprite_wp, sprite_wb, sprite_wkn, sprite_wr, sprite_wq, sprite_wk;
        int _Size;
        int k, n;

    public:
        Display();
        void show();
        ~Display();
};


#endif
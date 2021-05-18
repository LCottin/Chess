#ifndef __PIECE__
#define __PIECE__

#include "TYPES.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Piece
{
    protected:
        int         _X;
        int         _Y;
        int         _XWindow;
        int         _YWindow;
        enum TYPES  _Type;
        bool        _IsAlive;
        bool        _IsWhite;   //Color (True = White, False = black)
        Sprite      _PieceSprite;
        Texture     _PieceTexture;        

    public:
        Piece(const bool white);
        void            moveBoard(const int x, const int y);
        void            moveWindow(const int x, const int y);
        int             getX() const;
        int             getY() const;
        int             getXWindow() const;
        int             getYWindow() const;
        virtual int     getType() const = 0;
        bool            isAlive() const;
        void            kill();
        virtual bool    isMoveValid(const int x, const int y, const bool attacking = 0) = 0;
        virtual ~Piece() = 0;
};

#endif
#ifndef __PIECE__
#define __PIECE__

#include "TYPES.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Piece
{
    protected:
        int         _X;
        int         _Y;
        int         _XWindow;
        int         _YWindow;
        enum TYPES  _Type;
        bool        _IsDragged;
        bool        _IsAlive;
        bool        _IsWhite;   //Color (True = White, False = black)
        Sprite      _PieceSprite;
        Texture     _PieceTexture;        

    public:
        Piece(const bool white);
        void            moveBoard(const Vector2i to);
        void            moveWindow(const Vector2i to);
        int             getX() const;
        int             getY() const;
        int             getXWindow() const;
        int             getYWindow() const;
        bool            isAlive() const;
        void            kill();
        void            setIsDragged(const bool dragged);
        bool            getIsDragged() const;
        Sprite*         getSprite();
        virtual int     getType() const = 0;
        virtual bool    isMoveValid(const Vector2i destination, const bool attacking = 0) = 0;
        virtual ~Piece() = 0;
};

#endif
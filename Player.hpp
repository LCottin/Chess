#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <string>
#include <vector>

#include "Board.hpp"
#include "Piece.hpp"
#include "Pieces/Bishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Rook.hpp"
#include "Pieces/Pawn.hpp"
#include "MODES.hpp"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player
{
    private:
        string  _Pseudo;
        bool    _IsWhite;
        bool    _IsCheck;
        vector  <Piece*> _Pieces;
        void    spawnPieces(const MODES mode);

    public:
        Player(const string name, const MODES mode, const bool white);
        bool    isCheck() const;
        int     getSize() const;
        void    promotion(Piece* promotedPawn, const int TYPE);
        void    setCheck(const bool isCheck);
        Piece*  getPiece(const double i) const;
        Piece*  getPiece(const Vector2i temp, const bool window = false) const;
        void    play(const Vector2i from, const Vector2i to, const Player* Opposite = NULL);
        ~Player();
};



#endif

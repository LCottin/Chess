#ifndef __PIECE__
#define __PIECE__

class Piece
    {
    private:
        enum _TYPE {PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING};
        int _X;
        int _Y;
        enum _TYPE _Type;          //Type of piece (fool, king ...)
        bool _Color;        //Color (True = Black, False = white)
        bool _IsSelected; 

    public:
        Piece();
        void move(int x, int y);
        bool isMoveValid(int x, int y);
        ~Piece();
};

#endif
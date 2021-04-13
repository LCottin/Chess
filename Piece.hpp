#ifndef __PIECE__
#define __PIECE__

class Piece
    {
    private:
        enum _TYPE {PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING};
        int _X;
        int _Y;
        enum _TYPE _Type;          //Type of piece (fool, king ...)
        bool _IsWhite;             //Color (True = White, False = black)
        bool _IsSelected; 

    public:
        Piece();
        void move(const int x, const int y);
        bool isMoveValid(const int x, const int y) const;
        int getX() const;
        int getY() const;
        int getType() const;
        ~Piece();
};

#endif
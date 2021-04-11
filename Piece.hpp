#ifndef __PIECE__
#define __PIECE__

class Piece
    {
    private:

        int _X;
        int _Y;
        int _Type;          //Type of piece (fool, king ...)
        bool _Color;        //Color (True = Black, False = white)
        bool _IsSelected; 

    public:
        Piece();
        ~Piece();
};

#endif
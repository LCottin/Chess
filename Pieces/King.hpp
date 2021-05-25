#ifndef __KING__
#define __KING__

#include "../Piece.hpp"
#include "../TYPES.hpp"
#include <math.h>

class King : public Piece
{
    private:
        bool _IsCheck;
        bool _IsCheckmate;
        
    public:
        King(const bool white);
        
        bool isMoveValid(const Vector2i destination, const bool attacking = 0);
        int  getType() const;

        void setCheck(const bool check);
        void setCheckMate(const bool checkmate);

        bool isCheck() const;
        bool isCheckMate() const;

        ~King();
};


#endif
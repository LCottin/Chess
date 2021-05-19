#include "Board.hpp"

Board _Board;

Board::Board()
{
    cout << "Creation of board " << this << " ...";
    _Board = new int* [_SizeX];

    //fills board with 0
    for (int i = 0; i < _SizeX; i++)
    {
        _Board[i] = new int [_SizeY];
        for (int j = 0; j < _SizeY; j++)
        {
            _Board[i][j] = 0;
        }   
    }

    //Init both sides
    for (int i = 0; i < _SizeX; i++)
    {
        _Board[i][0] = -1;
        _Board[i][1] = -1;
        _Board[i][6] =  1;
        _Board[i][7] =  1;
    }
    cout << "Board " << this << " created ! " << endl;
}

/**
 * Updates the board when a player moves or attacks
 * @param from Vector of old piece position
 * @param to Vector of new piece position
 * @param whiteTurn Tells who's player it is
 */
void Board::updateBoard(const Vector2i from, const Vector2i to, const bool whiteTurn)
{
    //puts a 0 at the old position
    _Board[from.x][from.y] = 0;

    //puts the type of the piece at the given new position according to whiteTurn status
    _Board[to.x][to.y] = (whiteTurn ? 1 : -1);
}


/**
 * Checks if there are any collision on the desired path
 * @param from Vector of old piece position
 * @param to Vector of new piece position
 * @param type Type of the piece that moves
 * @param whiteTurn Tells if white is playing
 * @return false if there is collision, else true
 */
bool Board::collisionCheck(const Vector2i from, const Vector2i to, const int type, const bool whiteTurn) const
{
    //cursors on X and Y axis to check every tile between old pos and new pos
    int cursorX = (((to.x - from.x) > 0) ? 1 : -1);
    int cursorY = (((to.y - from.y) > 0) ? 1 : -1);

    switch(type)
    {
        /* Those case are already checked in the IsValidMove from Pawns because of the attackmove
        case -6:
        case  1:
        */

        //When it's a bishop
        case -5:
        case  2:

            //move along the board until while oldPos and newPos are different
            while((from.y + cursorY != to.y) && (from.x + cursorX != to.x))
            {
                if(getPiece(Vector2i((from.x + cursorX), (from.y + cursorY))) != 0)
                    return false;

                //update cursors
                cursorY += (((to.y - from.y) > 0) ? 1 : -1);
                cursorX += (((to.x - from.x) > 0) ? 1 : -1);
            }

            //checks if the piece color at the new position is the same than the piece that moves
            if(getPiece(Vector2i((from.x + cursorX),(from.y + cursorY))) == (whiteTurn ? 1 : -1))
                return false;
            return true;

        //checks when it's a knight
        case -4:
        case  3:
            if(getPiece(to) == (whiteTurn ? 1 : -1))
                return false;
            return true;

        //when it's a rook
        case -3:
        case  4:
            //moves on the same column
            if(from.x == to.x)
            {
                while(from.y + cursorY != to.y)
                {
                    if(getPiece(Vector2i(from.x,(from.y + cursorY))) != 0)
                        return false;

                    cursorY += (((to.y - from.y) > 0) ? 1 : -1);
                }
                if(getPiece(Vector2i(from.x,(from.y + cursorY))) == (whiteTurn ? 1 : -1))
                    return false;
            }
            //moves on the same line
            else
            {
                while(from.x + cursorX != to.x)
                {
                    if(getPiece(Vector2i((from.x + cursorX),from.y)) != 0)
                        return false;

                    cursorX += (((to.x - from.x) > 0) ? 1 : -1);
                }
                if(getPiece(Vector2i((from.x + cursorX),from.y)) == (whiteTurn ? 1 : -1))
                    return false;
            }
            return true;

        //when it's a queen
        case -2:
        case  5:
            //moves on the same column
            if(from.x == to.x)
            {
                while(from.y + cursorY != to.y)
                {
                    if(getPiece(Vector2i(from.x,(from.y + cursorY))) != 0)
                        return false;

                    cursorY += (((to.y - from.y) > 0) ? 1 : -1);
                }
                if(getPiece(Vector2i(from.x,(from.y + cursorY))) == (whiteTurn ? 1 : -1))
                    return false;
            }
            //moves on the same line
            else if(from.y == to.y)
            {
                while(from.x + cursorX != to.x)
                {
                    if(getPiece(Vector2i((from.x + cursorX),from.y)) != 0)
                        return false;

                    cursorX += (((to.x - from.x) > 0) ? 1 : -1);
                }
                if(getPiece(Vector2i((from.x + cursorX),from.y)) == (whiteTurn ? 1 : -1))
                    return false;
            }
            //moves on a diagonal
            else
            {
                
                while((from.y + cursorY != to.y) && (from.x + cursorX != to.x))
                {
                    if(getPiece(Vector2i((from.x + cursorX),(from.y + cursorY))) != 0)
                        return false;

                    cursorX += (((to.x - from.x) > 0) ? 1 : -1);
                    cursorY += (((to.y - from.y) > 0) ? 1 : -1);
                }
                if(getPiece(Vector2i((from.x + cursorX),(from.y + cursorY))) == (whiteTurn ? 1 : -1))
                    return false;
            }
            return true;

        //when it's a king
        case -1:
        case  6:
            //moves on the same column
            if(from.x == to.x)
            {
                if(getPiece(Vector2i(from.x,(from.y + cursorY))) == (whiteTurn ? 1 : -1))
                    return false;
            }

            //moves on the same line
            else if(from.y == to.y)
            {
                if(getPiece(Vector2i((from.x + cursorX),from.y)) == (whiteTurn ? 1 : -1))
                    return false;
            }

            //moves on diagonal
            else
            {
                if(getPiece(Vector2i((from.x + cursorX),(from.y + cursorY))) == (whiteTurn ? 1 : -1))
                    return false;
            }
            return true;
    }
    return true;
}

/**
 * Prints the current board
 */
void Board::printBoard() const 
{
    for (int i = 0; i < _SizeX; i++)
    {
        cout << "-----------------------------------" << endl;
        for (int j = 0; j < _SizeY; j++)
        {
            cout << " | " << _Board[i][j];
        }
        cout << " | " << endl;
    }
    cout << "-----------------------------------" << endl;
}


/**
 * Gets a piece at a given position
 * @param pos Vector of the new position 
 * @returns The type of the piece
 */
int Board::getPiece(const Vector2i pos) const
{
    return _Board[pos.x][pos.y];
}

Board::~Board()
{
    for (int i = 0; i < _SizeY; i++)
    {
        delete _Board[i];
    }
    delete _Board;
}
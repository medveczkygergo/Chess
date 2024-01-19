/***********************************************************************
 * Header File:
 *    Pawn : The King class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Controls the movement and interaction with a chess king
 ************************************************************************/

#ifndef King_h
#define King_h
#include "Piece.h"
#include <stdio.h>
#include "constants.h"
class King : public Piece
{
private:
    friend class TestKing;
public:
    //Constructor with row col
    King(int r, int c, bool isWhite) : Piece(r, c, isWhite)
    {
        this->position.set(r,c);
        this->isWhite = isWhite;
        this->nMoves = 0;
        this->lastMove = 0;
    }
    
    //Constructor with Position
   King(Position pos, bool isWhite) : Piece(pos, isWhite)
    {
        this->position.set(pos.getRow(),pos.getColumn());
        this->isWhite = isWhite;
        this->nMoves = 0;
        this->lastMove = 0;
    }
    
    //Get letter
    virtual char getLetter() const{return KING;};
    
    //Display King
    virtual void display(const ogstream &gout) const{gout.drawKing(position.getIndex(),isWhite);}
    //Get Possible Moves for King
    virtual set<Move> getMoves(const Board &board) const;
};
#endif /* King_hpp */


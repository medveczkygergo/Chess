//
//  Bishop.hpp
//  Lab01
//
//  Created by Gergo Medveczky on 10/9/22.
//

#ifndef Bishop_h
#define Bishop_h

#include <stdio.h>
#include "Piece.h"
#include "constants.h"
#include <stdio.h>
class Bishop : public Piece
{
private:
    friend class TestKing;
public:
    //Bishop constructor with row and col
    Bishop(int r, int c, bool isWhite) : Piece(r, c, isWhite)
    {
        this->position.set(r,c);
        this->isWhite = isWhite;
        this->nMoves = 0;
        this->lastMove = 0;
    }
    //Bishop constructor with position
   Bishop(Position pos, bool isWhite) : Piece(pos, isWhite)
    {
        this->position.set(pos.getRow(),pos.getColumn());
        this->isWhite = isWhite;
        this->nMoves = 0;
        this->lastMove = 0;
    }
    //Getter for letter
    virtual char getLetter() const{return KNIGHT;};
    //Display the piece on the board
    virtual void display(const ogstream &gout) const {gout.drawBishop(position.getIndex(), isWhite);}
    //Get Possible Moves for Knight
    virtual set<Move> getMoves(const Board &board) const;
};
#endif /* Bishop_h */

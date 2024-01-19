#pragma once
#include "Piece.h"
class Rook :
    public Piece
{
private:
   friend class TestKing;
public:
    //Rook constructor with row and col
   Rook(int r, int c, bool isWhite);
    //Rook constructor with position
    Rook(Position pos, bool isWhite);
    //Get letter of rook
   virtual char getLetter() const { return ROOK; };
    //Display rook
    virtual void display(const ogstream& gout) const {gout.drawRook(position.getIndex(), isWhite);};
    //Get all possible moves for rook
   virtual set<Move> getMoves(const Board& board) const;
   
};


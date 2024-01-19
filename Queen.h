#pragma once
/***********************************************************************
 * Header File:
 *    Queen : The Queen class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Controls the movement and interaction with a chess Queen
 ************************************************************************/

#include "Piece.h"
using namespace std;

class Queen : public Piece
{
public:
    //Queen constructor with row and col
   Queen(int r, int c, bool isWhite) : Piece(r, c, isWhite) {};
    //Queen constructor with position
   Queen(Position pos, bool isWhite) : Piece(pos, isWhite) {};
    //GETTER for letter
   virtual char getLetter() const { return PAWN; };
    //Display the piece
   virtual void display(const ogstream& gout) const;
    //Get all the possible move function.
   virtual set<Move> getMoves(const Board& board) const;
};

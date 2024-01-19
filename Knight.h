#pragma once
/***********************************************************************
 * Header File:
 *    Knight : The Knight class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Controls the movement and interaction with a chess Knight
 ************************************************************************/
#include "Piece.h"
using namespace std;

class Knight :  public Piece
{
public:

   Knight(int r, int c, bool isWhite) : Piece(r, c, isWhite) {};
   Knight(Position pos, bool isWhite) : Piece(pos, isWhite) {};
   virtual char getLetter() const { return PAWN; };
   virtual void display(const ogstream& gout) const;
   virtual set<Move> getMoves(const Board& board) const;
};


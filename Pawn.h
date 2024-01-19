#pragma once
/***********************************************************************
 * Header File:
 *    Pawn : The Pawn class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Controls the movement and interaction with a chess pawn
 ************************************************************************/

#include "Piece.h"
using namespace std;

class Pawn : public Piece
{
public:
   friend class TestPawn;

   Pawn(int r, int c, bool isWhite) : Piece(r, c, isWhite){};
   Pawn(Position pos, bool isWhite) : Piece(pos, isWhite) {};
   virtual char getLetter() const { return PAWN; };
   virtual void display(const ogstream& gout) const;
   virtual set<Move> getMoves(const Board &board) const;
};

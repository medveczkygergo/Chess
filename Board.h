#pragma once
/***********************************************************************
 * Header File:
 *    Board : The Board class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Tracks all the pieces and the number of turns.
 ************************************************************************/

class Piece;
#include "uiDraw.h"
#include "Position.h"
#include "Move.h"
#include "Piece.h"
#include "constants.h"

using namespace std;

class Board
{
public:
   friend class TestPawn;
   friend class TestKing;
   Board();
   int getCurrentMove() const { return currentMove; };
   bool whiteTurn() const { return currentMove % 2 == 1; };
   Piece* getPieceAt(Position pos) const;
   void display(Position hoverPos, Position selectedPos) const;
   void erase();
   void move(Move move);
   void place(Piece *piece);
   Piece* operator [](Position &p) const;

private:
   Piece *board[64];
   int currentMove;
   
   void swap(Position pos1, Position pos2);
   void assertBoard() const{};
};

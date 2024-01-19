#pragma once
/***********************************************************************
 * Header File:
 *    Piece : The Piece class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Base class for chess pieces. Provides a framework for tracking
 *    a piece's location and actions.
 ************************************************************************/

class Board;
#include "uiDraw.h"
#include "Position.h"
#include "Move.h"
#include "Board.h"
#include "constants.h"
#include <set>

using namespace std;
class Piece
{
public:
   //Piece() { };
   Piece(int r, int c, bool white);
    //Piece non-default constructor with position
   Piece(Position pos, bool isWhite);
    //Is the piece white?
   bool getIsWhite() const { return isWhite; }
    //Has the piece moved yet?
   bool hasMoved() const { return nMoves != 0; }
    //Get the number of moves
   int getNMoves() const { return nMoves; }
    //Check the last time of the piece's turn.
   int turnLastMoved() const { return lastMove; }
    //Getter for position
   Position getPosition() const { return position; }
    //Move the piece to a location
   void moveTo(Position pos, int turnNumber);
   // copy the attributes from to a new piece
   void copyAttributesFrom(const Piece *otherPiece);
    //Virtual Getter for letter
   virtual char getLetter() const = 0;
    //Virtual Display
   virtual void display(const ogstream &gout) const = 0;
    //Virtual get all possible moves
   virtual set<Move> getMoves(const Board &board) const  = 0;

protected:
   Position position;
   bool isWhite;
   int nMoves;
   int lastMove;
};

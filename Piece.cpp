/***********************************************************************
 * Source File:
 *    Piece : The Piece class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Base class for all other chess pieces. Provides a framework to track
 *    the information necessary to represent and interact with a chess piece.
 ************************************************************************/

#include "Piece.h"
#include <cassert>

Piece::Piece(int r, int c, bool white)
{
   Position pos = Position(r, c);
   assert(pos.isValid());
   this->position = pos;
   this->isWhite = white;
   this->nMoves = 0;
   this->lastMove = 0;
}

Piece::Piece(Position pos, bool white)
{
   assert(pos.isValid());
   this->position = pos;
   this->isWhite = white;
   this->nMoves = 0;
   this->lastMove = 0;
}

/************************************************************************
* MOVE TO
* Moves this piece to the specified position, increments the number of
* times this piece has moved, and sets the turn on which this piece
* most recently moved.
*   INPUT  pos         The position to move to
*          turnNumber  The current turn number
*************************************************************************/
void Piece::moveTo(Position pos, int turnNumber)
{
   assert(pos.isValid());
   position = pos;
   nMoves++;
   lastMove = turnNumber;
}

/************************************************************************
* COPY ATTRIBUTES FROM
* Copies all attributes from another piece to this one
*   INPUT  otherPiece  The piece from which attributes are to be copied.
*************************************************************************/
void Piece::copyAttributesFrom(const Piece* otherPiece)
{
   this->position = otherPiece->position;
   this->isWhite = otherPiece->isWhite;
   this->nMoves = otherPiece->nMoves;
   this->lastMove = otherPiece->lastMove;
}


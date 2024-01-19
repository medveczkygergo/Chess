/***********************************************************************
 * Source File:
 *    Pawn : The Pawn class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Controls the movement and interaction with a chess pawn
 ************************************************************************/

#include "Pawn.h"
#include <cassert>
#include "constants.h"

 /************************************************************************
 * DISPLAY
 * Draws the pawn to the screen using the given output method.
 *   INPUT  ogstream  the output graphics to use to draw.
 *************************************************************************/
void Pawn::display(const ogstream& gout) const
{
   gout.drawPawn(position.getIndex(), isWhite);
}

/************************************************************************
* GET MOVES
* Analyzes the board and decides which moves this pawn can make
*   INPUT  board  the representation of the current board with all the pieces
*************************************************************************/
set<Move> Pawn::getMoves(const Board &board) const
{
   set<Move> moveSet = set<Move>();

   // Check single forward move
   Position forwardOne = position;
   forwardOne.adjustRow(-1 + (2 * isWhite)); // -1 for black, +1 for white
   Piece* checkPiece = board.getPieceAt(forwardOne);
   if (checkPiece->getLetter() == SPACE)
   {
      // Can move forward one
      Move move = Move();
      move.setAsWhite(isWhite);
      move.setSrc(position);
      move.setDest(forwardOne);
      // Is it a promotion?
      if (forwardOne.getRow() == 7 * (isWhite)) // 0 for black, 7 for white
      {
         // Need to promote!
         move.setPromotion(QUEEN);
      }
      moveSet.insert(move);

      // Check for double forward move
      if (!hasMoved())
      {
         Position forwardTwo = position;
         forwardTwo.adjustRow(-2 + (4 * isWhite)); // -2 for black, +2 for white
         checkPiece = board.getPieceAt(forwardTwo);
         if (checkPiece->getLetter() == SPACE)
         {
            // Can move forward two
            Move move = Move();
            move.setAsWhite(isWhite);
            move.setSrc(position);
            move.setDest(forwardTwo);
            moveSet.insert(move);
         }
      }
   }
   for (int dCol = -1; dCol < 2; dCol += 2)
   {
      // Check for left and right capture
      Position forwardSide = position;
      forwardSide.adjustRow(-1 + (2 * isWhite)); // -1 for black, +1 for white
      forwardSide.adjustCol(dCol);
      if (forwardSide.isValid())
      {
         checkPiece = board.getPieceAt(forwardSide);
         if (checkPiece->getIsWhite() != isWhite && checkPiece->getLetter() != SPACE)
         {
            // Can left capture
            Move move = Move();
            move.setAsWhite(isWhite);
            move.setSrc(position);
            move.setDest(forwardSide);
            move.setCapture(checkPiece->getLetter());
            // Is it a promotion?
            if (forwardSide.getRow() == (NUM_ROWS - 1) * (isWhite)) // 0 for black, 7 for white
            {
               // Need to promote!
               move.setPromotion(QUEEN);
            }
            moveSet.insert(move);
         }
      }

      // Check left and right enPassant
      Position side = position;
      side.adjustCol(dCol);
      if (side.isValid())
      {
         checkPiece = board.getPieceAt(side);
         if (checkPiece->getLetter() == PAWN
            && checkPiece->getIsWhite() != isWhite
            && checkPiece->getNMoves() == 1
            && checkPiece->turnLastMoved() == board.getCurrentMove() - 1)
         {
            // Can EnPassant
            Move move = Move();
            move.setSrc(position);
            move.setDest(forwardSide);
            move.setCapture(PAWN);
            move.setAsWhite(isWhite);
            move.setEnPassant();
            moveSet.insert(move);
         }
      }
   }

   return moveSet;
}

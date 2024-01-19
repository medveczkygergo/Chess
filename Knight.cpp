/***********************************************************************
 * Source File:
 *    Knight : The Knight class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Controls the movement and interaction with a chess Knight
 ************************************************************************/

#include "Knight.h"
#include "constants.h"

 /************************************************************************
 * DISPLAY
 * Draws the Knight to the screen using the given output method.
 *   INPUT  ogstream  the output graphics to use to draw.
 *************************************************************************/
void Knight::display(const ogstream& gout) const
{
   gout.drawKnight(position.getIndex(), isWhite);
}

/************************************************************************
* GET MOVES
* Analyzes the board and decides which moves this pawn can make
*   INPUT  board  the representation of the current board with all the pieces
*************************************************************************/
set<Move> Knight::getMoves(const Board& board) const
{
   set<Move> moveSet = set<Move>();

   // Knight can move in 8 directions:
   //     x x
   //    x   x
   //      N
   //    x   x
   //     x x
   int directions[8][2] = {         {2, -1},  {2, 1},
                           {1, -2},                    {1, 2},
                                          /*N*/
                           {-1, -2},                   {-1, 2},
                                    {-2, -1}, {-2, 1} };
   for (int* dir : directions)
   {
      //gather info about the position
      Position targetPos = position;
      targetPos.adjustRow(dir[0]);
      targetPos.adjustCol(dir[1]);
      if (targetPos.isValid())
      {
         Piece* piece_in_question = board.getPieceAt(targetPos);
         char letter_in_question = piece_in_question->getLetter();

         if (letter_in_question == SPACE
            || piece_in_question->getIsWhite() != isWhite)
         {
            // can move there
            Move move = Move();
            move.setSrc(position);
            move.setDest(targetPos);
            move.setAsWhite(isWhite);
            if (letter_in_question != SPACE)
               move.setCapture(letter_in_question); // ID LIKE TO CHANGE THE MOVE ASSERT TO INCLUDE SPACES SO THIS IF STATEMENT IS UNNECESSARY
            moveSet.insert(move);
         }
      }
   }

   return moveSet;
}

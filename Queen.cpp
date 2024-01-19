/***********************************************************************
 * Source File:
 *    Queen : The Queen class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Controls the movement and interaction with a chess Queen
 ************************************************************************/

#include "Queen.h"
#include "constants.h"

 /************************************************************************
 * DISPLAY
 * Draws the queen to the screen using the given output method.
 *   INPUT  ogstream  the output graphics to use to draw.
 *************************************************************************/
void Queen::display(const ogstream& gout) const
{
   gout.drawQueen(position.getIndex(), isWhite);
}

/************************************************************************
* GET MOVES
* Analyzes the board and decides which moves this pawn can make
*   INPUT  board  the representation of the current board with all the pieces
*************************************************************************/
set<Move> Queen::getMoves(const Board& board) const
{
   set<Move> moveSet = set<Move>();

   // Queen can move in 8 directions:
   //     xxx
   //     xQx
   //     xxx
   int directions[8][2] = { {1, -1},  {1, 0},  {1, 1}, 
                            {0, -1},   /*Q*/   {0, 1},
                            {-1, -1}, {-1, 0}, {-1, 1} };
    //Loop through all the possible directions
   for (int* dir : directions)
   {
      bool pathIsClear = true;
      Position nextPos = position;
      while (pathIsClear)
      {
         //gather info about the next spot in the line
         nextPos.adjustRow(dir[0]);
         nextPos.adjustCol(dir[1]);
         if (nextPos.isValid())
         {
            Piece* piece_in_question = board.getPieceAt(nextPos);
            char letter_in_question = piece_in_question->getLetter();

            if (letter_in_question == SPACE
               || piece_in_question->getIsWhite() != isWhite)
            {
               // can move there
               Move move = Move();
               move.setSrc(position);
               move.setDest(nextPos);
               move.setAsWhite(isWhite);
               if (letter_in_question != SPACE)
                  move.setCapture(letter_in_question);
               moveSet.insert(move);
            }
            if (letter_in_question != SPACE)
               pathIsClear = false; // can't move further
         }
         else
            pathIsClear = false; // hit an edge
      }
   }

   return moveSet;
}

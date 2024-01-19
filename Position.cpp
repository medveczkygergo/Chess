/***********************************************************************
 * Source File:
 *    Piece : The Piece class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Base class for all other chess pieces. Provides a framework to track
 *    the information necessary to represent and interact with a chess piece.
 ************************************************************************/

#include "Position.h"
#include<cassert>

double Position::squareHeight = 0;
double Position::squareWidth = 0;

//Set Row and Column from location
Position::Position(char loc)
{
   setRow(loc / NUM_COLS);
   setCol(loc % NUM_COLS);
}

/************************************************************************
* IS VALID
* Checks whether this position is a valid position on a chessboard
*************************************************************************/
bool Position::isValid() const
{
   if (row < 0 || row >= NUM_ROWS)
      return false;

   return col >= 0 && col < NUM_ROWS;
}

/***********************************************************************
 * Source File:
 *    Move : The Move class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Holds all the information to execute a move in chess.
 ************************************************************************/

#include "Move.h"
#include <cassert>
#include "constants.h"

/************************************************************************
* Move constructor.
* Initializes all values to default, blank, or false.
*************************************************************************/
Move::Move()
{
   source = Position(-1);
   destination = Position(-1);
   promotion = SPACE;
   capture = SPACE;
   enPassant = false; 
   castleK = false;
   castleQ = false;
   isWhite = false;
}

/************************************************************************
* GET TEXT
* Returns a string of the Smith notation representation of this move.
*************************************************************************/
string Move::getText()
{
   // do the opposite of parse
   string output = "";

   // add source
   output += char(source.getColumn() + 'a');
   output += char(source.getRow() + '1');

   // add destination
   output += char(destination.getColumn() + 'a');
   output += char(destination.getRow() + '1');

   // add capture OR castling OR enPassant
   if (enPassant)
      output += 'E';
   else if (castleK)
      output += 'c';
   else if (castleQ)
      output += 'C';
   else if (capture != SPACE)
      output += char(tolower(capture));

   // add promotion
   if (promotion != SPACE)
      output += promotion;
   
   return output;
}


/************************************************************************
* SET SOURCE
* Sets the source position of this move (the location from which the piece
* will be moving.)
*   INPUT  src  The starting position of the move.
*************************************************************************/
void Move::setSrc(Position src)
{
   assert(src.isValid());
   assert(src != destination);
   source = src;
}

/************************************************************************
* SET DESTINATION
* Sets the destination position of this move (the location to which the
* piece will be moving.)
*   INPUT  dest  The ending position of the move.
*************************************************************************/
void Move::setDest(Position dest)
{
   assert(dest.isValid());
   assert(source != dest);
   destination = dest;
}

/************************************************************************
* SET CASTLE
* Sets the move to be a castling move, and declares whether it is kingside
* or queenside.
*   INPUT  isKingside  Whether this move is kingside castling or queenside
*************************************************************************/
void Move::setCastle(bool isKingside)
{
   assert(!enPassant);
   assert(capture == SPACE);
   assert(promotion == SPACE);
   castleK = isKingside;
   castleQ = !isKingside;
}

/************************************************************************
* SET CAPTURE
* Set this move as a capturing move where another piece will be removed
* from the board.
*   INPUT  piece  The character code of the piece to be captured.
*************************************************************************/
void Move::setCapture(char piece)
{
   assert(!castleK);
   assert(!castleQ);
   assert(piece == KING || piece == QUEEN || piece == BISHOP ||
      piece == KNIGHT || piece == ROOK || piece == PAWN);
   capture = piece;
}

/************************************************************************
* SET PROMOTION
* Set this move as a promoting move where the pawn at source will be
* removed and a piece will be added at destination.
*   INPUT  newPiece  The character code of the new piece to be added.
*************************************************************************/
void Move::setPromotion(char newPiece)
{
   assert(!enPassant);
   assert(!castleK);
   assert(!castleQ);
   assert(newPiece == QUEEN || newPiece == BISHOP ||
      newPiece == KNIGHT || newPiece == ROOK);
   promotion = newPiece;
}

/************************************************************************
* PARSE
* Reads a string representing a move in Smith notation, and makes this
* move represent that move.
*   INPUTS  move  Smith notation representation of a move.
*************************************************************************/
void Move::parse(string smithNotation)
{
   string::const_iterator it = smithNotation.cbegin();

   // get the source
   int col = *it - 'a';
   it++;
   int row = *it - '1';
   it++;
   Position positionFrom = Position(row, col);
   setSrc(positionFrom);

   // get the destination
   col = *it - 'a';
   it++;
   row = *it - '1';
   it++;
   Position positionTo = Position(row, col);
   setDest(positionTo);

   // capture and promotion information
   for (; it != smithNotation.end(); ++it)
   {
      switch (*it)
      {
      case 'p':   // capture a pawn
      case 'n':   // capture a knight
      case 'b':   // capture a bishop
      case 'r':   // capture a rook
      case 'q':   // capture a queen
      case 'k':   // !! you can't capture a king you silly!
         setCapture(toupper(*it));
         break;

      case 'c':  // short castling or king's castle
         setCastle(true);
         break;
      case 'C':  // long castling or queen's castle
         setCastle(false);
         break;
      case 'E':  // En-passant
         setEnPassant();
         break;

      case 'N':  // Promote to knight
      case 'B':  // Promote to Bishop
      case 'R':  // Promote to Rook
      case 'Q':  // Promote to Queen
         setPromotion(*it);
         break;

      }
   }
}

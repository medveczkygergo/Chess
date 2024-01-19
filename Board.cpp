/***********************************************************************
 * Source File:
 *    Board : The Board class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Keeps track of the state of the board and all its pieces in a game of chess.
 ************************************************************************/

#include "Board.h"
#include "Pawn.h"
#include "Space.h"
#include "King.h"
#include <cassert>
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "Bishop.h"


 /************************************************************************
 * BOARD
 * Default constructor. Sets up a standard game of chess
 *   0  1  2  3  4  5  6  7
 * 0 r  k  b  q  k  b  k  r
 * 1 p  p  p  p  p  p  p  p
 * 2
 * 3
 * 4
 * 5
 * 6 P  P  P  P  P  P  P  P
 * 7 R  K  B  Q  K  B  K  R
 *************************************************************************/
Board::Board()
{
   // FROM BOTTOM TO TOP

   // black pieces
   board[0] = new Rook(Position(0, 0), true);
   board[1] = new Knight(Position(0, 1), true);
   board[2] = new Bishop(Position(0, 2), true);
   board[3] = new Queen(Position(0, 3), true);
   board[4] = new King(Position(0, 4), true);
   board[5] = new Bishop(Position(0, 5), true);
   board[6] = new Knight(Position(0, 6), true);
   board[7] = new Rook(Position(0, 7), true);
   for (int i = 8; i < 16; i++)
      board[i] = new Pawn(Position(i), true);

   // spaces
   for (int i = 16; i < 48; i++)
      board[i] = new Space(Position(i));

   // white pieces
   board[56] = new Rook(Position(7, 0), false);
   board[57] = new Knight(Position(7, 1), false);
   board[58] = new Bishop(Position(7, 2), false);
   board[59] = new Queen(Position(7, 3), false);
   board[60] = new King(Position(7, 4), false);
   board[61] = new Bishop(Position(7, 5), false);
   board[62] = new Knight(Position(7, 6), false);
   board[63] = new Rook(Position(7, 7), false);
   for (int i = 48; i < 56; i++)
      board[i] = new Pawn(Position(i), false);

   currentMove = 1;
}


// TODO: Delete this function and use [] instead.
Piece* Board::getPieceAt(Position pos) const
{
   assert(pos.isValid());

   return board[pos.getIndex()]; 
}

/************************************************************************
* DISPLAY
* Draws the Board to the screen using the given output method.
*   INPUT  ogstream  the output graphics to use to draw.
*************************************************************************/
void Board::display(Position hoverPos, Position selectedPos) const
{
    ogstream gout;
    gout.drawBoard();
    gout.drawHover(hoverPos.getIndex());
    gout.drawSelected(selectedPos.getIndex());
    
    if (selectedPos.isValid())
    {
        // draw the possible moves
        set<Move>moves = getPieceAt(selectedPos)->getMoves(*this);
        set <Move> :: iterator it;
        for (it = moves.begin(); it != moves.end(); ++it)
        {
           Move possibleMove = *it;
           gout.drawPossible(possibleMove.getDest().getIndex());
        }
    }
    for (int i  = 0;i<64;i++)
    {
        board[i]->display(gout);
    }
}

void Board::erase()
{
   for (int i = 0; i < NUM_COLS * NUM_ROWS; i++)
   {
       delete board[i];
       Space *space = new Space(Position(i));
       board[i] = space;
   }
   currentMove = 1;
}

void Board::move(Move move)
{
    Piece *piece = getPieceAt(move.getSrc());
    piece->moveTo(move.getDest(),getCurrentMove());
    delete board[move.getDest().getIndex()];
    board[move.getDest().getIndex()] = piece;
    Space *space = new Space(move.getSrc());
    board[move.getSrc().getIndex()] = space;

    if (move.getEnPassant())
    {
       Position capturePos = Position(move.getSrc().getRow(), move.getDest().getColumn());
       delete board[capturePos.getIndex()];
       board[capturePos.getIndex()] = new Space(capturePos);
    }
    else if (move.getPromotion() != SPACE)
    {
       Piece* oldPawn = getPieceAt(move.getDest()); // because the pawn has already been moved.
       Piece* newPiece;
       switch (move.getPromotion())
       {
       case QUEEN:
          newPiece = new Queen(move.getDest(), oldPawn->getIsWhite());
          break;
       case KNIGHT:
          newPiece = new Knight(move.getDest(), oldPawn->getIsWhite());
          break;
       case BISHOP:
          newPiece = new Bishop(move.getDest(), oldPawn->getIsWhite());
          break;
       case ROOK:
          newPiece = new Rook(move.getDest(), oldPawn->getIsWhite());
          break;
       default:
          assert(false);
          break;
       }
       newPiece->copyAttributesFrom(oldPawn);
       delete board[move.getDest().getIndex()];
       board[move.getDest().getIndex()] = newPiece;
    }
    else if(move.getCastleK() || move.getCastleQ())
    {
       Position rookPos;
       Position newRookPos;
       if (move.getCastleK())
       {
          rookPos = Position(move.getSrc().getRow(), NUM_COLS - 1);
          newRookPos = Position(move.getSrc().getRow(), move.getDest().getColumn() - 1);
       }
       else
       {
          rookPos = Position(move.getSrc().getRow(), 0);
          newRookPos = Position(move.getSrc().getRow(), move.getDest().getColumn() + 1);
       }
       getPieceAt(rookPos)->moveTo(newRookPos, currentMove);
       delete board[newRookPos.getIndex()];
       board[newRookPos.getIndex()] = board[rookPos.getIndex()];
       board[rookPos.getIndex()] = new Space(rookPos);
    }

    currentMove++;
}

void Board::place(Piece *piece)
{
   assert(piece->getPosition().isValid());

   delete board[piece->getPosition().getIndex()];
   board[piece->getPosition().getIndex()] = piece;
}

void Board::swap(Position pos1, Position pos2)
{
   assert(pos1.isValid());
   assert(pos2.isValid());

   Piece* temp = board[pos1.getIndex()];
   board[pos1.getIndex()] = board[pos2.getIndex()];
   board[pos2.getIndex()] = temp;
}

/********
*********/
Piece* Board::operator [](Position &p) const
{
   assert(p.isValid());
   return board[p.getIndex()];
}

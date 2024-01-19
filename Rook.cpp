#include "Rook.h"

Rook::Rook(int r, int c, bool isWhite) : Piece(r, c, isWhite)
 {
     this->position.set(r,c);
     this->isWhite = isWhite;
     this->nMoves = 0;
     this->lastMove = 0;
}

Rook::Rook(Position pos, bool isWhite) : Piece(pos, isWhite)
 {
     this->position.set(pos.getRow(),pos.getColumn());
     this->isWhite = isWhite;
     this->nMoves = 0;
     this->lastMove = 0;
 }

set<Move> Rook::getMoves(const Board &board) const
{
    
    set<Move> moveSet = set<Move>();

    // Queen can move in 4 directions:
    //     *x*
    //     xRx
    //     *x*
    int directions[4][2] = {           {1, 0},
                             {0, -1},   /*R*/   {0, 1},
                                       {-1, 0}        };
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

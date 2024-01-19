//
//  Bishop.cpp
//  Lab01
//
//  Created by Gergo Medveczky on 10/9/22.
//

#include "Bishop.h"
set<Move> Bishop::getMoves(const Board &board) const
{
    set<Move> moveSet = set<Move>();

    // Queen can move in 8 directions:
    //     x.x
    //     .B.
    //     x.x
    int directions[8][2] = { {1, -1},           {1, 1},
                                       /*B*/
                             {-1, -1},         {-1, 1} };
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

/***********************************************************************
 * Source File:
 *    King: King class
 * Author:
 *   Gergo Medveczky
 * Summary:
 *    Controls the movement and interaction with a chess king
 ************************************************************************/

#include "King.h"

//Get all the possible moves for king
set<Move> King::getMoves(const Board &board) const
{
    set<Move> moveSet = set<Move>();

    // Queen can move in 8 directions:
    //     x.x
    //     .B.
    //     x.x
    int directions[8][2] = { {1, -1},  {1, 0},  {1, 1},
                             {0, -1},   /*K*/   {0, 1},
                            {-1, -1}, {-1, 0}, {-1, 1} };
     //Loop through all the possible directions
    for (int* dir : directions)
    {
       
       Position nextPos = position;
       
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
          }
       }
    

    //Check number of Moves for castling
    if (this->nMoves == 0)
    {
        //King Side Castling
            Position kingSideRook(this->position.getRow(),this->position.getColumn()+3);
            if (board.getPieceAt(kingSideRook)->getLetter() == ROOK && this->getIsWhite() == board.getPieceAt(kingSideRook)->getIsWhite() && board.getPieceAt(kingSideRook)->getNMoves() == 0)
            {
                //Check for empty spots between KING AND ROOK on board
                Position kingAdjacent(this->position.getRow(),this->position.getColumn()+1);
                Position rookAdjacent(this->position.getRow(),this->position.getColumn()+2);
                if(board.getPieceAt(kingAdjacent)->getLetter() == SPACE && board.getPieceAt(rookAdjacent)->getLetter() == SPACE)
                {
                    Move possibleMove;
                    possibleMove.setSrc(this->position);
                    possibleMove.setDest(rookAdjacent);
                    possibleMove.setCastle(true);
                    moveSet.insert(possibleMove);
                }
            }
        //Queen Side Castling
        Position queenSideRook(this->position.getRow(),this->position.getColumn()-4);
        if (board.getPieceAt(queenSideRook)->getLetter() == ROOK && this->getIsWhite() == board.getPieceAt(queenSideRook)->getIsWhite() && board.getPieceAt(queenSideRook)->getNMoves() == 0)
        {
            //Check for empty spots between KING AND ROOK on board
            Position kingAdjacent(this->position.getRow(),this->position.getColumn()-1);
            Position middlespot(this->position.getRow(),this->position.getColumn()-2);
            Position rookAdjacent(this->position.getRow(),this->position.getColumn()-3);
            if(board.getPieceAt(kingAdjacent)->getLetter() == SPACE && board.getPieceAt(rookAdjacent)->getLetter() == ' ' &&board.getPieceAt(middlespot)->getLetter() == SPACE)
            {
                Move possibleMove;
                possibleMove.setSrc(this->position);
                possibleMove.setDest(middlespot);
                possibleMove.setCastle(false);
                moveSet.insert(possibleMove);
            }
        }
        
    }

    
    return moveSet;
}


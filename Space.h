/***********************************************************************
 * Header File:
 *    Move : The Space class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Represents a space on the board or empty spot.
 ************************************************************************/

#ifndef Space_h
#define Space_h
#include "Piece.h"
#include <stdio.h>

class Space : public Piece
{
private:
    friend class TestKing;
public:
    //Space non-default constructor with position
   Space(Position pos) : Piece(pos, false) {};
    
   bool getIsWhite() const;
    //Getter for space
    virtual char getLetter()const{return ' ';}
    //Display empty space "NOTHING"
   virtual void display(const ogstream &gout)const{};
    //Getmoves for space
   virtual set<Move> getMoves(const Board &board)const{return set<Move>();}
};
#endif /* Space_hpp */

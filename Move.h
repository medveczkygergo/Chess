#pragma once
/***********************************************************************
 * Header File:
 *    Move : The Move class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Holds all the information to execute a move in chess.
 ************************************************************************/

#include "Position.h"
#include <string>
#include <iostream>
using namespace std;

class Move
{
public:
    //Move default constructor
   Move();
    //Get string text
   string getText();
    //Get Source Position
   Position getSrc() { return source; };
    //Get Destination Position
   Position getDest() { return destination; };
    //Get Promotion
   char getPromotion() { return promotion; };
    //Get Capture
   char getCapture() { return capture; };
    //Get Enpassant
   bool getEnPassant() { return enPassant; };
    //Get King-side castle
   bool getCastleK() { return castleK; };
    //Get queen-side castle
   bool getCastleQ() { return castleQ; };
    //Getter for isWhite?
   bool getIsWhite() { return isWhite; };
    //Setter for enpassant
   void setEnPassant() { enPassant = true; };
    //Setter for aswhite
   void setAsWhite(bool white) { isWhite = white; };
    //Setter for source
   void setSrc(Position src);
    //Setter for destination
   void setDest(Position dest);
    //Setter for castle
   void setCastle(bool isKingside);
    //Setter for capture
   void setCapture(char piece);
    //Setter for promotion
   void setPromotion(char newPiece);
    //Parse the move string
   void parse(string smithNotation);
    // << sign overloaded operator
   friend ostream& operator<<(ostream& output, Move& move) { output << move.getText(); return output; };
    // >> sign overloaded operator
   friend istream& operator>>(istream& input, Move& move)
   {
      string smithNotation;
      input >> smithNotation;
      move.parse(smithNotation);
      return input;
   };
    // == sign overloaded operator
   friend bool operator==(const Move& lhs, const Move& rhs)
   {
      return lhs.destination == rhs.destination // This should be all we need to compare
         && lhs.source == rhs.source // The rest is for safety (NO BUGS)
         && lhs.isWhite == rhs.isWhite
         && lhs.capture == rhs.capture
         && lhs.castleK == rhs.castleK
         && lhs.castleQ == rhs.castleQ
         && lhs.enPassant == rhs.enPassant
         && lhs.promotion == rhs.promotion;
   }
    // < sign overloaded operator
   friend bool operator<(const Move& lhs, const Move& rhs)
   {
      if (lhs.destination < rhs.destination)
         return true;
      return false;
   };
    // > sign overloaded operator
   friend bool operator>(const Move& lhs, const Move& rhs)
   {
      if (lhs.destination > rhs.destination)
         return true;
      return false;
   };

private:
   Position source;
   Position destination;
   char capture;
   char promotion;
   bool enPassant;
   bool castleK;
   bool castleQ;
   bool isWhite;
   string error;
};


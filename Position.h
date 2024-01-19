#pragma once
/***********************************************************************
 * Header File:
 *    Position : The Position class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Tracks a position on a chessboard
 ************************************************************************/
#include "constants.h"
#include <cassert>
#include <iostream>
class Position
{
public:
    //Position default constructor
   Position() : row(0), col(0) {};
    //Position non-default constructor with row&col
   Position(int r, int c) : row(r), col(c) {};
    //Position non-default constructor with location
   Position(char loc);
    //Check if position is valid
   bool isValid() const;
    //Getter for index
   int getIndex() const { return row * NUM_COLS + col; };
    //Getter for row
   int getRow() const { return row; }
    //Getter for column
   int getColumn() const { return col; }
    //Getter for x
   int getX() const { return 0; };
    //Getter for y
   int getY() const { return 0; };
    //Setter for row
   void setRow(int r){row = r;};
    //Setter for col
   void setCol(int c){col = c;};
    //Setter both row and col
   void set(int r, int c) { setRow(r); setCol(c); }
    //Adjust Row
   void adjustRow(int dRow) { setRow(row + dRow); };
    //Adjust Column
   void adjustCol(int dCol) { setCol(col + dCol); };
    
    // == sign overloaded operator
   friend bool operator==(const Position& lhs, const Position& rhs)
   {
      return lhs.row == rhs.row && lhs.col == rhs.col;
   };
    
    // != sign overloaded operator
   friend bool operator!=(const Position& lhs, const Position& rhs)
   {
      return lhs.row != rhs.row || lhs.col != rhs.col;
   };
    
    // < sign overloaded operator
   friend bool operator<(const Position& lhs, const Position& rhs)
   {
      if (lhs.row != rhs.row)
         return lhs.row < rhs.row;
      return lhs.col < rhs.col;
   };
    
    // > sign overloaded operator
   friend bool operator>(const Position& lhs, const Position& rhs)
   {
      if (lhs.row != rhs.row)
         return lhs.row > rhs.row;
      return lhs.col < rhs.col;
   };
private:
   int row;
   int col;
   static double squareWidth;
   static double squareHeight;
};

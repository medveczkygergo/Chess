#pragma once
/******************************************************************
* Header File:
*    Constants : various values to be used throughout the program.
* Author:
*    Gergo Medveczky
* Summary:
*    Various constants used in the Chess Lab. Helps the project be
*    more data-driven.
******************************************************************/

// Character representations of the pieces.
#define SPACE  ' '
#define PAWN   'P'
#define ROOK   'R'
#define KNIGHT 'N'
#define BISHOP 'B'
#define QUEEN  'Q'
#define KING   'K'

// Board size
#define NUM_ROWS 8
#define NUM_COLS 8

// Piece color
const int RGB_WHITE_PIECE[]{ 255, 255, 255 };
const int RGB_BLACK_PIECE[]{ 0, 0, 0 };

// normal squares: tan and brown
const int RGB_WHITE_SQUARE[] { 210, 180, 140 };
const int RGB_BLACK_SQUARE[]{ 165, 42, 42 };

// the color of a selected square
const int RGB_SELECTED [] { 256, 0, 0 };

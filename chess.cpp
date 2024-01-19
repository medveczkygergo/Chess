/**********************************************************************
 * CHESS
 * Plays a chess game. Currently just runs (and fails) tests.
 **********************************************************************/

#include "test.h"
#include "uiInteract.h"
#include "Board.h"
#include "Position.h"
#include <cassert>
using namespace std;


/*************************************
* No previous click, so just check if the piece
* they clicked on belongs to the player whose
* turn it is.
**************************************/
void handleFirstClick(Position &current, Board *board, Interface *pUI)
{
   // has the user selected something at all?
   if (current.isValid())
   {
      // Selected something. Is it a bad selection?
      Piece* selectedPiece = board->getPieceAt(current);
      if (selectedPiece->getLetter() == SPACE
         || selectedPiece->getIsWhite() != board->getCurrentMove() % 2)
      {
         // Selected a piece whose turn it isn't. Silly user! Clear selection.
         pUI->clearSelectPosition();
      }
      // else: The user selected their piece. Now we wait until they pick a move.
   }
   // else: The user hasn't selected anything yet. They're thinking.
}

/*************************************
* The user selected a piece, now we need to decide what 
* to do about this second click. Might execute a move
* if it's legal, but whether that happens or the user
* clicked on a non-move, the user's selection will be cleared.
*************************************/
void handleSecondClick(Position& prev, Position& current, Board* board, Interface* pUI)
{
   // Selected a piece last click. Check for moves this time.
   assert(current.isValid());
   Piece* selectedPiece = board->getPieceAt(prev);

   // It better be that piece's turn
   assert(selectedPiece->getLetter() != SPACE);
   assert(selectedPiece->getIsWhite() == board->getCurrentMove() % 2);
   set<Move> possible = selectedPiece->getMoves((*board));

   // Is the current selection in the possible moves?
   bool found = false;
   for (Move move : possible)
   {
      if (move.getDest() == current)
      {
         // Found it! Do the move.
         // There better not be any duplicates.
         assert(!found);
         board->move(move);
         found = true;
      }// else: Just keep looking!
   }
   // Whether we did the move or the user selected a non-move, reset selections.
   pUI->clearPreviousPosition();
   pUI->clearSelectPosition();
}


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(Interface* pUI, void* p)
{
    
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Board* board = (Board*)p;

   Position prev = Position(pUI->getPreviousPosition());
   Position current = Position(pUI->getSelectPosition());
    
   if (prev.isValid())
      handleSecondClick(prev, current, board, pUI);
   else
      handleFirstClick(current, board, pUI);

   // draw the board. Current selection may have been cleared, so need to send a fresh version.
   board->display(Position(pUI->getHoverPosition()), Position(pUI->getSelectPosition()));
}

/*********************************
 * Main is pretty sparse.  Just
 * run the test cases for now!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run tests
   //testRunner();

   // Set up the game
   Interface ui("chess");
   Board *board = new Board();
    
   // Put everything in action
   ui.run(callBack, board);

   return 0;
}

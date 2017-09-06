/* 
 * File:   Sudoku.cpp
 * Author: HenryDaniels-Koch
 * 
 * Created on April 11, 2015, 12:56 PM
 */



#include "Sudoku.h"

using namespace std;

Sudoku::Sudoku() {

}

Sudoku::Solve() {
    //
    //Create first move on the board to initialize
    //
    Move firstMove(0,0,1);
    //
    //Continue solving until the board is done
    //
    while (theBoard.success() == false) {
        int row = newMove.getRow();
        int col = newMove.getCol();
        int val = newMove.getValue();
        //
        //Get the next new move
        //
        Move newMove = theBoard.nextMove(firstMove);
        
        //
        //Continue popping the move off of the stack (backtracking) until 
        //the move is legal
        //
        while (newMove.getValue() == 10) {
            
            moves.pop(newMove); 
            theBoard.setValueAt(row, col, 0); //Set the value at spot to 0
            //
            //Find the next new, legal move with the next value
            //
            newMove = theBoard.nextMove(row, col, val + 1);
            //
            //newMove is now legal
            //
            if (newMove.getValue() != 10) {
                break;
            }
        }
        //
        //Move is valid
        //
        theBoard.setValueAt(row, col, val);
        moves.push(newMove);
    }
}


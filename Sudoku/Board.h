/* 
 * File:   Board.h
 * Author: HenryDaniels-Koch
 *
 * Created on April 11, 2015, 12:57 PM
 */

#ifndef BOARD_H
#define	BOARD_H

#include "Move.h"

#define DIM 9 //Dimensions of board



class Board {
public:
    //
    //Constructs puzzle.
    //
    Board();
    
    //
    //Prints board.
    //
    void printBoard();
    
    //
    //Determines if the whole board is correctly filled in
    bool success();
    
    //
    //Determines if a potential move is possible
    //
    bool legalMove(Move move);
    
    //
    //Gets value at a spot on the board
    //
    int getValueAt(int row, int col);
    
    //
    //Sets the value at a spot on the board to a parameter
    //
    void setValueAt(int row, int col, int value);
    
    //
    //Determines what the next legal move is on the board
    //
    Move nextMove(Move move);
    
private:

    int theBoard[DIM][DIM]; //Initializes puzzle
    
};
#endif	/* BOARD_H */


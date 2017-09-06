/* 
 * File:   Entry.h
 * Author: smajerci
 *
 * Created on November 18, 2014, 7:38 PM
 */

#ifndef ENTRY_H
#define	ENTRY_H

#include "GameBoard.h"


class Entry {
    
public:
    //
    //Constructor with no inputs does not create anything
    //
    Entry();
    //
    //Constructor creates an entry with a board and associated value
    //
    Entry(GameBoard board, int value);
    //
    //Returns the board for the entry
    //
    GameBoard getBoard() { return board; }
    //
    //Returns a value for the entry
    //
    int getValue() { return value; } 
    
private:
    GameBoard board; //The board
    int value; //The value associated with the board
    
};

#endif	/* ENTRY_H */

/* 
 * File:   GameBoard.h
 * Author: smajerci
 *
 * Created on November 18, 2014, 7:24 PM
 */

#ifndef GAMEBOARD_H
#define	GAMEBOARD_H
#define p 16908799
#define q 127

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class GameBoard {
    
public:
    //
    //Constructor with no inputs does not do anything
    //
    GameBoard();
    //
    //Creates a GameBoard object with all values equal to the input value
    //
    GameBoard(int val);
    //
    //Sets a specified element on the board to a specified value mod 3
    //
    void setElementAt(int x, int y, int value);
    //
    //Returns the size of the board
    //
    int size() { return DIMENSION; }
    //
    //Returns a value at a specified place on the board
    //
    int elementAt(int x, int y) {return board[x][y]; }
    //
    //Determines if the GameBoard objects is the same board as a specified board
    //
    bool equals(GameBoard board);
    //
    //Generate a hash value for the board
    //
    int hashCode();
    //
    //Prints the game board
    //
    void print();


private:
    static const int DIMENSION = 4; //Dimension of the square board
    
    int board[DIMENSION][DIMENSION]; //an array of integers

};

#endif	/* GAMEBOARD_H */


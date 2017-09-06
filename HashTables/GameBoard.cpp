/* 
 * File:   GameBoard.cpp
 * Author: smajerci
 * 
 * Created on November 18, 2014, 7:24 PM
 */
//GameBoard.cpp.
//      Assignment7.c++-Source code for CSCI2101 Assignment 7.
//FUNCTIONAL DESCRIPTION
//      This program in C++ fulfills the requirements of Assignment 7 in
//      CSCI2101 Spring 2015
//
//      1. If the user does not specify parameters for entry nothing happens
//      2. If the user specifies a value, a GameBoard object is created
//         with all elements equal to the specified value.
//      3. The user can sets a specified element on the board to a specified 
//         value which is then mod by 3.
//      4. The user can check if the GameBoard object is the same board as a 
//         specified board.
//      5. The user can generate a hash value for the board as well as print the
//         board.
//
//Notice
//      Copyright (C) April 28, 2015 to May 3 2015
//      Henry Daniels-Koch All Rights Reserved.
//
#include "GameBoard.h"

//GameBoard.
//GameBoard is constructor
//
//FUNCTIONAL DESCRIPTION.
//      1. The user did not specify parameters for entry, so nothing happens
//
//ENTRY PARAMETERS
//There are no entry parameters
//
//RETURN VALUES
//This function does not return anything.
GameBoard::GameBoard() {
}

//GameBoard.
//GameBoard is constructor with a specified value
//
//FUNCTIONAL DESCRIPTION.
//      1. Each element on the board is set the parameter value.
//
//ENTRY PARAMETERS
//val is the value that specified for each element on the board to be set to.
//
//RETURN VALUES
//This function does not return anything.
GameBoard::GameBoard(int val) {
    
    //
    //Iterate through each element on the board.
    //
    for (int r = 0; r < DIMENSION; r++) {
        for (int c = 0; c < DIMENSION; c++) {
            board[r][c] = val; //Set element to val
        }
    }
}

//setElementAt.
//setElementAt sets a specified place on the board to a value (0,1, or2)
//
//FUNCTIONAL DESCRIPTION.
//      1. An element on the board (determined by the x and y parameters) is set
//         to a value (0,1, or 2) determined by the specified value parameter.
//
//ENTRY PARAMETERS
//x is the x coordinate of the element
//y is the y coordinate of the element
//val is the value that specified for an element on the board to be set to.
//
//RETURN VALUES
//This function does not return anything.
void GameBoard::setElementAt(int x, int y, int value) {
    //
    //Changes the input value into a value between and including 0 and 2.
    //
    board[x][y] = value % 3;
    //
    //Changes the value into a positive number if negative
    //
    if (board[x][y] < 0) {
        board[x][y] = board[x][y] + 3;
    }
}


//equals.
//equals determines if a specified board is the same as the GameBoard object
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterating through each element on the board, if elements in the same
//         position in the board object and input board are different, the
//         function returns false.
//      2. If all the elements are the same, the function returns true.
//
//ENTRY PARAMETERS
//board is the board being compared to the GameBoard object.
//
//RETURN VALUES
//This function returns a boolian determining whether the boards are the same.
bool GameBoard::equals(GameBoard board) {
    //
    //Iterates through each element on the board
    //
    for (int r = 0; r < DIMENSION; r++) {
        for (int c = 0; c < DIMENSION; c++) {
            //
            //Elements are not the same
            //
            if (this->board[r][c] != board.elementAt(r, c))
                return false;
        }
    }
    //
    //Each element is the same.
    //
    return true;
}


//hashCode.
//hashCode creates a hash value associated with a certain board.
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterating through each element on the board, the hash value is 
//         modified using prime numbers and mod.
//      2. Once each element has been used, the hash value is returned. 
//
//ENTRY PARAMETERS
//There are no entry parameters
//
//RETURN VALUES
//This function returns the hash value (int).
int GameBoard::hashCode() {
    int hashVal = 0; //Initialize the hash value
    //
    //Iterate through each element on the board
    //
    for (int r = 0; r < DIMENSION; r++) {
        for (int c = 0; c < DIMENSION; c++) {
            //
            //Modify the previous hash value
            //
            hashVal = ((q * hashVal) + board[r][c]) % p;
        }
    }
    return hashVal;
}

//print.
//print prints out the board
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterating through each element on the board, the value is printed.
//
//ENTRY PARAMETERS
//There are no entry parameters
//
//RETURN VALUES
//This function does not return anything.
void GameBoard::print() {
    //
    //Iterate through each element on the board.
    //
    for (int r = 0; r < DIMENSION; r++) {
        for (int c = 0; c < DIMENSION; c++) {
            //
            //Print the element.
            //
            cout << this->board[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
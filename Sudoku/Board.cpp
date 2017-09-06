/* 
 * File:   Board.cpp
 * Author: HenryDaniels-Koch
 * 
 * Created on April 11, 2015, 12:57 PM
 */

//Board.cpp
//Board.cpp creates a board that can be searched for legal words in Boggle.
//
//FUNCTIONAL DESCRIPTION.
//      1. All functions are performed on the class Board.
//      2. Prompt user to enter Boggle Board file name.
//      3. Read in board line by line with each line a row in the
//         character array.
//      4. If the board is not square, then user is prompted to enter a board
//         file name again until a square board is found.
//      5. The board's dimensions and the board itself are printed.
//      5. The user is asked if they want to play before the computer demolishes
//         them. 
//      6. The computer finds all legal words.
//      7. If user wants to play, their inputed words are checked for legality.
//      8. Words found by the human and computer are shown along with scores.
//
//Notice
//      Copyright (C) March 27, 2015 to April 2, 2015.
//      Henry Daniels-Koch All Rights Reserved.
//


#include "Board.h"
#include "Move.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Board.
//Board is a constructor method without parameters.
//
//FUNCTIONAL DESCRIPTION.
//      1. Prompt user to enter Boggle Board file name.
//      2. Read in board line by line with each line a row in the
//         character array.
//      3. If the board is not square, then user is prompted to enter a board
//         file name again until a square board is found.
//      4. The board's dimensions and the board itself are printed.
//      5. The user is asked if they want to play before the computer demolishes
//         them. 
//      6. The computer finds all possible words.
//      7. If user wants to play, their inputed words are checked for legality.
//      8. Words found by the human and computer are shown along with scores.
//
//ENTRY PARAMETERS
//There are no entry parameters.
//
//RETURN VALUES
//This function does not return anything.
Board::Board() {
    
    string fileName;
    ifstream puzzleStream;
    
    // read in the puzle file name
    do {
        cout << "Enter puzzle file name: ";
        cin >> fileName;
        puzzleStream.open(fileName, ios::in);
    } while (!puzzleStream.good());  //Keep trying until this works
    
    //read in the digits
    for (int r = 0; r < DIM; r++) { //Iterate rows
        
        for (int c = 0; c < DIM; c++) { //Iterate cols
            
            puzzleStream >> theBoard[r][c]; //set values in array
        }
    }


    //
    //Print board
    //
    printBoard();
}

//printBoard.
//printBoard prints the character array theBoard
//
//FUNCTIONAL DESCRIPTION.
//      1. Prints theBoard.
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void Board::printBoard() {
    for (int i = 0; i < DIM; i++) { //Iterates through each row
        
        for (int j = 0; j < DIM; j++) { //Iterates through each column
            
            //
            //Prints the uppercase letter of the character at (i,j)
            //
            cout << theBoard[i][j] << " "; //
        }
        cout << endl;
    }
    cout << endl;
}

//success.
//success determines if the board has been successfully completed
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterates through all the numbers on the board and determines if there
//         are any 0s indicating that the board is not completed.
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function returns true if the board is complete and false if not.
bool Board::success() {
    for (int i = 0; i < DIM; i++) { //Iterates through each row
        
        for (int j = 0; j < DIM; j++) { //Iterates through each column
            //
            //Board is not complete
            //
            if (theBoard[i][j] == 0) {
                return false;
            } 
        }
    }
    //
    //Board is complete.
    return true;
}

//legalMove.
//legalMove determines if a move still creates a potentially filled sudoku board
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterates through each space in the move's row and each space in the 
//         move's column checking for duplicates.
//      2. Checks the box that the move value is in for duplicates.
//      3. If any duplicate is found throughout function, the function returns
//         false, but otherwise returns true
//
//ENTRY PARAMETERS
//move is an object that is being checked for legality
//
//RETURN VALUES
//This function returns true if the move is legal and false if not.
bool Board::legalMove(Move move) {
    //
    //Check each space in move's row for duplicates
    //
    for (int i = 0; i < DIM; i++) { //Iterates through each row
        //
        //Duplicate found
        //
        if (move.getValue() == theBoard[i][move.getCol()]) {
            return false;
        }
    }
    //
    //Check each space in move's column for duplicates
    //
    for (int j = 0; j < DIM; j++) { //Iterates through each column
        //
        //Duplicate found
        //
        if (move.getValue() == theBoard[move.getRow()][j]) {
            return false;
        }
    }
    //
    //Check each box for duplicates
    //
    for (int k = (move.getRow() / 3) * 3; k < ((move.getRow() / 3) * 3) + 3; 
            k++) { //Iterate through each row in the box
        for (int m = (move.getCol() / 3) * 3; m < ((move.getCol() / 3) * 3) + 3;
                m++) { //Iterate through column in box
            //
            //Only need to check 4 corners of the box because the other spots 
            //were already checked above.
            //
            if (k != move.getRow() && m != move.getCol()) {
                //
                //Duplicate found
                //
                if (theBoard[k][m] == move.getValue()) {
                    return false;
                }
            }
        }
    }
    //
    //No duplicate found
    //
    return true;
}

//getValueAt.
//getValueAt returns the value at a spot on the board
//
//FUNCTIONAL DESCRIPTION.
//      1. Returns the value at the row and column specified on theBoard.
//
//ENTRY PARAMETERS
//row and column indicate the position on theBoard
//
//RETURN VALUES
//This function returns the value at a spot on theBoard.
int Board::getValueAt(int row, int col) {
    return theBoard[row][col];
}

//setValueAt.
//setValueAt changes a value at a spot on the board
//
//FUNCTIONAL DESCRIPTION.
//      1. Changes a spot on the board at the specified row and column to a
//         specified value.
//
//ENTRY PARAMETERS
//row and column indicate the position on theBoard.
//value is the new value that the spot is being changed to
//
//RETURN VALUES
//This function does not return anything.
void Board::setValueAt(int row, int col, int value) {
    theBoard[row][col] = value;
}

//nextMove.
//nextMove determines the next legal move on the board.
//
//FUNCTIONAL DESCRIPTION.
//      1. Changes a spot on the board at the specified row and column to a
//         specified value.
//
//ENTRY PARAMETERS
//move is the potential new move to be tried (with a new value)
//
//RETURN VALUES
//This function returns the next legal move
Move Board::nextMove(Move move) {
    bool empty = false;
    
    for (int i = 0; i < DIM; i++) { //Iterates through each row
        
        for (int j = 0; j < DIM; j++) { //Iterates through each column
            //
            //0 is found
            //
            if (theBoard[i][j] == 0) {
                empty = true;
                for (int k = move.getValue() + 1; k < DIM; k++) { //Iterate through possible values
                    Move newMove(i,j,k);
                    if (legalMove(newMove) == true) { //Move is legal
                        return newMove;
                    }
                }
                //
                //New possible moves at "0" spot
                //
                Move illegalMove(10,10,10);
                return illegalMove;
            } 
        }
    }
//    //
//    //No zeros were found
//    //
//    if (empty == false) {
//        Move noZeros(10,10,11);
//        return noZeros;
    }
}
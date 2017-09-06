/* 
 * File:   Board.h
 * Author: HenryDaniels-Koch
 *
 * Created on March 29, 2015, 8:03 PM
 */

#ifndef BOARD_H
#define	BOARD_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Dictionary.h"

#define MAX_ROWS 20 //Maximum number of rows in puzzle
#define MAX_COLUMNS 20 //Maximum number of columns in puzzle
#define MINWORDLENGTH 3 //Minimum word length of legal words on board

using namespace std;

class Board {
public:
    //
    //Constructs puzzle.
    //
    Board();
    
    //
    //Prints dimensions of puzzle.
    //
    void printDimensions();
    
    //
    //Prints board.
    //
    void printBoard();
    
    //
    //User plays
    //
    void userSolve();
    
    //
    //Computer plays Boggle.
    //
    void compBoggle();
    
    //
    //check if the user found word counts
    //
    void checkLegality(string word);
    
    //
    //Recursive function that goes through possible words in the board
    //
    void searchWord(int rows, int cols, string word);
    
    //
    //Print words found by computer
    //
    void printCompWords();
    
    //
    //Print words found by human
    //
    void printHumanWords();
    
private:
    int numRows; //Number of rows in puzzle
    int numCols; //Number of columns in puzzle
    Dictionary dictionary; //Creates dictionary
    char theBoard[MAX_ROWS][MAX_COLUMNS]; //Initializes puzzle
    vector<string> compWords; //Vector of words found by computer
    vector<string> humanWords; //Vector of words found by human
    
};

#endif	/* PUZZLE_H */

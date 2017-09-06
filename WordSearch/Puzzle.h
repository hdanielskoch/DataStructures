/* 
 * File:   Puzzle.h
 * Author: HenryDaniels-Koch
 *
 * Created on February 27, 2015, 1:36 PM
 */

#ifndef PUZZLE_H
#define	PUZZLE_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Dictionary.h"

#define MAX_ROWS 100 //Maximum number of rows in puzzle
#define MAX_COLUMNS 100 //Maximum number of columns in puzzle

using namespace std;

class Puzzle {
public:
    //
    //Constructs puzzle.
    //
    Puzzle();
    
    //
    //Prints dimensions of puzzle.
    //
    void printDimensions();
    
    //
    //Prints puzzle.
    //
    void printPuzzle();
    
    //
    //Prints all words found in dictionary by iterating through all words within
    //the dictionary.
    //
    void naiveSearch();
    
    //
    //Prints all words found in dictionary using binarySearch.
    //
    void binaryAlgorithm();
    
    //
    //Prints all words found in dictionary using isPrefix and binarySearch.
    //
    void prefixAlgorithm();
    
private:
    int numRows; //Number of rows in puzzle
    int numCols; //Number of columns in puzzle
    int minWordLength; //User entered minimum word length
    Dictionary dictionary; //Creates dictionary
    char theBoard[MAX_ROWS][MAX_COLUMNS]; //Initializes puzzle
    
};

#endif	/* PUZZLE_H */


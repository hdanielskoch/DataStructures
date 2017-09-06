/* 
 * File:   main.cpp
 * Author: HenryDaniels-Koch
 *
 * Created on February 27, 2015, 1:28 PM
 */
//main.cpp.
//      Assignment4.c++-Source code for CSCI2101 Assignment 4.
//FUNCTIONAL DESCRIPTION
//      This program in C++ fulfills the requirements of Assignment 4 in
//      CSCI2101 Spring 2015
//
//      1. A puzzle object is constructed through the Puzzle class which also
//         constructs a dictionary object.
//      2. naiveSearch searches for words in the puzzle by comparing the words 
//         in the puzzle to every word in the dictionary.
//      3. binaryAlgorithm searches for words in the puzzle by
//         going through each row, column, and direction in the puzzle and
//         calling binarySearch for each potential word.
//      8. prefixAlgorithm searches for words in the puzzle by
//         going through each row, column, and direction in the puzzle, checking
//         if the word is a prefix of any words in the dictionary and then 
//         calling binarySearch on the word if it is a prefix.
//
//Notice
//      Copyright (C) February 26, 2015 to March 27 2015.
//      Henry Daniels-Koch All Rights Reserved.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Dictionary.h"
#include "Puzzle.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Welcome to Word Search!" << endl << endl;
    //
    //puzzle is constructed.
    //
    Puzzle puzzle;

    //
    //3 different search algorithms find all words in the puzzle
    //
    puzzle.naiveSearch();
    puzzle.binaryAlgorithm();
    puzzle.prefixAlgorithm();
  

    

    return 0;
}

/* 
 * File:   main.cpp
 * Author: HenryDaniels-Koch
 *
 * Created on March 29, 2015, 7:57 PM
 */
//main.cpp.
//      Assignment5.c++-Source code for CSCI2101 Assignment 5.
//FUNCTIONAL DESCRIPTION
//      This program in C++ fulfills the requirements of Assignment 5 in
//      CSCI2101 Spring 2015
//
//      1. A board object is constructed through the Board class which also
//         constructs a dictionary object.
//      2. The user is asked if they want to play before the computer demolishes
//         them.
//      3. The computer finds all possible words.
//      4. If user wants to play, their inputed words are checked for legality.
//      5. Words found and scores of both human and computer are printed.
//
//Notice
//      Copyright (C) March 27, 2015 to April 2, 2015.
//      Henry Daniels-Koch All Rights Reserved.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Dictionary.h"
#include "Board.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Welcome to Boggle!" << endl << endl;
    
    //
    //A board is created, the user CAN play, and the computer finds all words
    //on the board
    //
    Board board;
    
    return 0;
}


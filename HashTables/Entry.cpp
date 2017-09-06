/* 
 * File:   Entry.cpp
 * Author: Stephen Majercik and Henry Daniels-Koch
 * 
 * Created on November 18, 2014 and modified on May 2, 2015
 */
//Entry.cpp.
//      Assignment7.c++-Source code for CSCI2101 Assignment 7.
//FUNCTIONAL DESCRIPTION
//      This program in C++ fulfills the requirements of Assignment 7 in
//      CSCI2101 Spring 2015
//
//      1. If the user does not specify parameters for entry nothing happens
//      2. If the user specifies a board and a value, an entry object is created
//         with a board and value.
//
//Notice
//      Copyright (C) April 28, 2015 to May 3 2015
//      Henry Daniels-Koch All Rights Reserved.
//
#include "Entry.h"

//Entry.
//Entry is constructor
//
//FUNCTIONAL DESCRIPTION.
//      1. The user did not specify parameters for entry, so nothing happens
//
//ENTRY PARAMETERS
//There are no entry parameters
//
//RETURN VALUES
//This function does not return anything.
Entry::Entry() {
}


//Entry.
//Entry is constructor that creates an entry object with a board and value
//
//FUNCTIONAL DESCRIPTION.
//      1. The user specifies a board and a value, an entry object is created
//         with a board and value.
//
//ENTRY PARAMETERS
//board is the game board for that entry
//value is the value associated with that game board
//
//RETURN VALUES
//This function does not return anything.
Entry::Entry(GameBoard board, int value) { 
    this->board = board; 
    this->value = value; 
}



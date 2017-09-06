/* 
 * File:   main.cpp
 * Author: Henry Daniels-Koch and Stephen Majercik
 *
 * Created on November 18, 2014 and modified on May 1, 2015
 */
//main.cpp.
//      Assignment7.c++-Source code for CSCI2101 Assignment 7.
//FUNCTIONAL DESCRIPTION
//      This program in C++ fulfills the requirements of Assignment 7 in
//      CSCI2101 Spring 2015
//
//      1. A hash table object is constructed for various load factors from 0 to
//         5 containing 10,000 boards. The hash table in an array of vectors.
//      2. For each hash table, a randomly generated board is searched for 
//         2,500,000 times. 
//      3. For each hash table, the number of spaces in the array (numBuckets),
//         the load factor, the variance, and time it takes to find all of the 
//         random boards is printed.
//      4. To test the hash functions, a small hash table is created as well as
//         4 boards, two of which are inserted into the hash table.
//      5. All boards are searched for, then removed, then searched for again to
//         test hash functions. The hash table is also checked to see if it is
//         empty, which it is.
//
//Notice
//      Copyright (C) April 26, 2015 to May 1, 2015.
//      Henry Daniels-Koch All Rights Reserved.
//
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "HashTables.h"
#include "GameBoard.h"
#include "Entry.h"

using namespace std;

//
// Creates and returns a GameBoard containing random integers
//
GameBoard randomBoard();
//
//Initializes hash table with a specified number of GameBoards
//
void initTable(HashTables &table, int numBoards);
//
//Determines whether 4 game boards are the same or different
//
bool allDiff(GameBoard boards[4]);
//
//Prints the length of the hash table, the load factor, the variance, and the
//run time of process
//
void printInfo(int numBuckets, double loadFactor, double variance, double time);


int main(int argc, char** argv) {

    int numBoards = 10000; //Number of boards in hash table
    int numSearches = 2500000; //Number of searches to be conducted
    cout << numBoards << " GameBoards inserted; "
            << numSearches << " searches" << endl << endl;

    
    // OUTPUT: PART 1
    // ------
    //
    // *** create required table of statistics with varying load factors
    //Iterate through load factors from 5 to 0.5 in increments of 0.5
    //
    for (double i = 5.00; i >= 0.5; i=i-0.5 ) {
        //
        //Create hash table
        //
        HashTables table(numBoards / i);
        initTable(table, numBoards);
        //
        //Start time for searches
        //
        double start, end, seconds;
        start= clock();
        //
        //Search for a random board numSearches times
        //
        for(int j = 0; j < numSearches; j++) {
            table.find(randomBoard());
        }
        //
        //end time
        //
        end = clock();
        seconds = (end-start)/ CLOCKS_PER_SEC;
        
        //
        //Print information
        //
        int numBucks = table.getNumBuckets();
        double variance = table.calcVariance();
        printInfo(numBucks, i, variance, seconds);
    }
    
    // OUTPUT: PART 2
    // ------
    // NOTE: set DIMENSION in GameBoard.h to 4 for this section
    //
    // *** make a hash table of size 100
    //
    HashTables tableSmall(100);
    //
    // make an array of 4 GameBoards, all of which are different
    //
    GameBoard boards[4];
    for (int i = 0; i < 4; ++i) {
        boards[i] = randomBoard();
    }
    while (allDiff(boards) == false) {
        for (int i = 0; i < 4; ++i) {
            boards[i] = randomBoard();
        }
    }

    //
    // *** insert the first two boards into the hash table with arbitrary values
    //
    tableSmall.insert(boards[0], 69);
    tableSmall.insert(boards[1], 69);
    
    

    cout << "———————————————————------------------------————————" << endl << endl;
    cout << "ADDED BOARDS 1 AND 2 TO THE HASH TABLE" << endl << endl;
    cout << "———————————————————------------------------————————" << endl << endl;
    cout << "SEARCHES AFTER INSERTIONS BUT BEFORE REMOVALS" << endl << endl;
    cout << "———————————————————------------------------————————" << endl;

    //
    //Search for all boards
    //
    cout << "Searching for Board 1 (which is in the hash table).  Board 1:" << endl << endl;
    boards[0].print();
    Entry e = tableSmall.find(boards[0]);// *** try to find boards[0] in the hash table
    cout << "Here’s what was returned from the find:" << endl << endl;
    e.getBoard().print();
    cout << "———————————————————------------------------————————" << endl << endl;
        
    cout << "Searching for Board 2 (which is in the hash table).  Board 2:" << endl << endl;
    boards[1].print();
    e = tableSmall.find(boards[1]);// *** try to find boards[1] in the hash table
    cout << "Here’s what was returned from the find:" << endl << endl;
    e.getBoard().print();
    cout << "———————————————————------------------------————————" << endl << endl;
    
        
    cout << "Searching for Board 3 (which is NOT in the hash table).  Board 3:" << endl << endl;
    boards[1].print();
    e = tableSmall.find(boards[2]);// *** try to find boards[2] in the hash table
    cout << "Here’s what was returned from the find:" << endl << endl;
    e.getBoard().print();
    cout << "———————————————————------------------------————————" << endl << endl;
    
        
    cout << "Searching for Board 4 (which is NOT in the hash table).  Board 4:" << endl << endl;
    boards[1].print();
    e = tableSmall.find(boards[3]); // *** try to find boards[3] in the hash table
    cout << "Here’s what was returned from the find:" << endl << endl;
    e.getBoard().print();
    cout << "———————————————————------------------------————————" << endl << endl;
    //
    //Remove all boards
    //
    cout << "REMOVALS" << endl << endl;
    cout << "———————————————————------------------------————————" << endl;
    cout << "Removing Board 1 (which is in the hash table):" << endl << endl;
    boards[0].print();
    e =  tableSmall.remove(boards[0]); // *** remove boards[0]
    cout << "Here’s what was returned from the remove:" << endl << endl;
    e.getBoard().print();
    cout << "———————————————————------------------------————————" << endl << endl;
        
    cout << "Removing Board 2 (which is in the hash table):" << endl << endl;
    boards[1].print();
    e =  tableSmall.remove(boards[1]); // *** remove boards[1]
    cout << "Here’s what was returned from the remove:" << endl << endl;
    e.getBoard().print();
    cout << "———————————————————------------------------————————" << endl << endl;
        
    cout << "Removing Board 3 (which is NOT in the hash table):" << endl << endl;
    boards[2].print();
    e =  tableSmall.remove(boards[2]); // *** remove boards[2]
    cout << "Here’s what was returned from the remove:" << endl << endl;
    e.getBoard().print();
    cout << "———————————————————------------------------————————" << endl << endl;
        
    cout << "Removing Board 4 (which is NOT in the hash table):" << endl << endl;
    boards[3].print();
    e =  tableSmall.remove(boards[3]); // *** remove boards[3]
    cout << "Here’s what was returned from the remove:" << endl << endl;
    e.getBoard().print();
    cout << "———————————————————------------------------————————" << endl << endl;
        
    //
    //Search for boards that were inserted and then removed
    //
    cout << "SEARCHES AFTER REMOVALS" << endl << endl;
    cout << "———————————————————------------------------————————" << endl;
        
    cout << "Searching for Board 1 (no longer in the hash table).  Board 1:" << endl << endl;
    boards[0].print();
    e = tableSmall.find(boards[0]); // *** try to find boards[0] in the hash table
    cout << "Here’s what was returned from the find:" << endl << endl;
    e.getBoard().print();
    cout << "———————————————————------------------------————————" << endl << endl;
        
    cout << "Searching for Board 2 (no longer in the hash table).  Board 2:" << endl << endl;
    boards[1].print();
    e = tableSmall.find(boards[1]); // *** try to find boards[1] in the hash table
    cout << "Here’s what was returned from the find:" << endl << endl;
    e.getBoard().print();
    cout << "———————————————————------------------------————————" << endl << endl;
        
    //
    //Determine if hash table is empty
    //
    cout << "Call to isEmpty function returns:  " << tableSmall.isEmpty() << endl << endl;
    
    cout << "———————————————————------------------------————————" << endl << endl;

    return EXIT_SUCCESS;

}



//
// Inputs: None.
//
// Output: A random gameboard.
//
// Creates and returns a GameBoard containing random
// integers
//

GameBoard randomBoard(){

    GameBoard board;
    for (int y = 0; y < board.size(); y++) {
        for (int x = 0; x < board.size(); x++) {
            double fval = rand() * 17;
            int value = (int) fval;
            board.setElementAt(x, y, value);
        }
    }
    return board;

}



//
// Inputs: A HashTable and an integer specifiying the
//         number of random Gameboards to be inserted
//         into the table.
//
// Output: None.
//
// The specified number of GameBoards is created and
// inserted into the HashTable. The value associated
// with each board is just the value of the for-loop
// control variable, since, for this lab, this value
// does not matter.
//

void initTable(HashTables &table, int numBoards) {
    for (int i = 0; i < numBoards; i++) {
        table.insert(randomBoard(), i);
    }
}


//
// Inputs: An array of 4 GameBoards.
//
// Output: A Boolean value:
//           - true if all 4 boards are different
//           - false, otherwise
//

bool allDiff(GameBoard boards[4]) {

    return
    !boards[0].equals(boards[1]) &&
            !boards[0].equals(boards[2]) &&
            !boards[0].equals(boards[3]) &&
            !boards[1].equals(boards[2]) &&
            !boards[1].equals(boards[3]) &&
            !boards[2].equals(boards[3]);


}

//printInfo.
//printInfo prints information about hash table searches
//
//FUNCTIONAL DESCRIPTION.
//      1. Print the length of the hash table, the load factor, the variance,
//         and the run time.
//
//ENTRY PARAMETERS
//numBuckets is the length of the array (number of vectors)
//loadFactor is the load factor
//variance is variance
//time is run time
//
//RETURN VALUES
//This function does not return anything.
void printInfo(int numBuckets, double loadFactor, double variance, double time){
    cout << "number buckets = " << 
            setw(6) << numBuckets << 
            "     load factor = " << setw(6) << setiosflags(ios::fixed) << setprecision(2) << loadFactor 
            << "     variance = " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << variance
            << "     time = " << setw(6) << setiosflags(ios::fixed) << setprecision(8) << time << " seconds" << endl;
}
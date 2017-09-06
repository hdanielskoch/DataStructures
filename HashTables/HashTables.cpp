/* 
 * File:   HashTables.cpp
 * Author: HenryDaniels-Koch
 * 
 * Created on May 1, 2015, 11:28 AM
 */
//HashTables.cpp.
//      Assignment7.c++-Source code for CSCI2101 Assignment 7.
//FUNCTIONAL DESCRIPTION
//      This program in C++ fulfills the requirements of Assignment 7 in
//      CSCI2101 Spring 2015
//
//      1. The constructor creates an array of vectors (the hash table) with
//         a user specified "size" number of vectors.
//      2. The user can insert an entry, remove an entry, find an entry, 
//         compress a hash value, check if the hash table is empty, empty the
//         hash table, get the number of entries in the hash table, get the 
//         number of vectors in the hash table (buckets), get the load factor of
//         the hash table, calculate the variance of tests on the hash table,
//         compress a hash value, and print the size of all vectors in the hash 
//         table.
//
//Notice
//      Copyright (C) April 28, 2015 to May 3 2015
//      Henry Daniels-Koch All Rights Reserved.
//
#include "HashTables.h"
#include <vector>
#include <new>
#include <iostream>
#include <iomanip>


using namespace std;

//HashTables.
//HashTables constructs the hash table of a specified size.
//
//FUNCTIONAL DESCRIPTION.
//      1. The constructor creates an array of vectors (the hash table) with
//         a user specified "size" number of vectors.
//
//ENTRY PARAMETERS
//size is the number of vectors in the hash table.
//
//RETURN VALUES
//This function does not return anything.
HashTables::HashTables(int size) {
    numBuckets = size; //Set private constant to size
    
    hashTable = new vector <Entry> [size]; //Hash Table
    if (hashTable == NULL) {
        cout << "Error: did not allocate memory" << endl;
    }
}

//insert.
//insert inserts an entry into the hash table.
//
//FUNCTIONAL DESCRIPTION.
//      1. An entry object is created from the parameters.
//      2. A hash value is created from the board and that value is compressed
//      3. The entry is then added onto a vector in the hash table at the
//         compressed value index.
//
//ENTRY PARAMETERS
//key is the game board being inserted
//value is value associated with game board being inserted
//
//RETURN VALUES
//This function returns the entry.
Entry HashTables::insert(GameBoard key, int value) {
    Entry entry(key, value); //Entry object created
    //
    //A hash value is created and then compressed
    //
    int hashVal= key.hashCode();
    int compressedVal = compress(hashVal);
    //
    //Add entry to end of vector at compressedVal
    //
    hashTable[compressedVal].push_back(entry);
    return entry;
    
}
//remove.
//remove removes an entry in the hash table
//
//FUNCTIONAL DESCRIPTION.
//      1. A hash value is created from the board and that value is compressed.
//      2. The entry is then searched for in the vector at the compressed value
//         in the hash table.
//      3. If the entry in found in the vector, it is erased and returned.
//      4. If the entry is not found, a failed board entry is returned.
//
//ENTRY PARAMETERS
//board is the game board being inserted
//
//RETURN VALUES
//This function returns an entry.
Entry HashTables::remove(GameBoard board) {
    //
    //The board (key) is hashed and compressed.
    //
    int hashVal = board.hashCode();
    int compressedVal = compress(hashVal);
    
    //
    //An vector is created equal to the vector in the HT as the compressedVal
    //
    vector <Entry> vect = hashTable[compressedVal];

    //
    //Iterate through the vector
    //
    for (int i = 0; i < vect.size(); i++) {
        //
        //The board is found in the vector
        //
        if (vect.at(i).getBoard().equals(board)) {
            //
            //Erase the entry in the vector in the hash table
            //
            hashTable[compressedVal].erase(hashTable[compressedVal].begin() 
            + i);
            
            //
            //Return the removed entry
            //
            Entry entry(board, 45);
            return entry;
        }
    }
    //
    //Entry was not found. Return a failed board entry
    //
    GameBoard failBoard(-1);
    Entry failEntry(failBoard, -99);
    return failEntry;
}

//find.
//find finds an entry in the hash table
//
//FUNCTIONAL DESCRIPTION.
//      1. A hash value is created from the board and that value is compressed.
//      2. The entry is then searched for in the vector at the compressed value
//         in the hash table.
//      3. If the entry in found in the vector, it is returned.
//      4. If the entry is not found, a failed board entry is returned.
//
//ENTRY PARAMETERS
//key is the game board being inserted
//
//RETURN VALUES
//This function returns an entry.
Entry HashTables::find(GameBoard key) {
    //
    //The board (key) is hashed and compressed.
    //
    int hashVal = key.hashCode();
    int compressedVal = compress(hashVal);
    //
    //An vector is created equal to the vector in the HT as the compressedVal
    //
    vector <Entry> vect = hashTable[compressedVal];
    
    //
    //Iterate through the vector
    //
    for(int i = 0; i < vect.size(); i++) {
        //
        //key was found
        //
        if (vect.at(i).getBoard().equals(key)) {
            return vect.at(i);
        }
    }
    //
    //key was not found. Return a failed board entry.
    //
    GameBoard board(-1);
    Entry entry(board, -99);
    return entry;
}

//compress.
//compress compresses a hash value/code to be within the size of the hash table.
//
//FUNCTIONAL DESCRIPTION.
//      1. A hash value is compressed using prime numbers and mod.
//      2. The hash value is returned.
//
//ENTRY PARAMETERS
//hash code is the hashed integer associated with a game board.
//
//RETURN VALUES
//This function returns an int which is a compressed hash value.
int HashTables::compress(int hashCode) {
    int compressedVal = 0;
    //
    //hashCode is compressed
    //
    compressedVal = (((a * hashCode) + b) % p) % getNumBuckets();
    return compressedVal;
}

//calcVariance.
//calcVariance finds the variance in the tests of the HT with a load factor
//
//FUNCTIONAL DESCRIPTION.
//      1. The mean is equivalent to the load factor of the hash table.
//      2. Iterating through each entry in the hash table, a statistical
//         variable is modified.
//      3. The variance is found and returned using a variance equation.
//
//ENTRY PARAMETERS
//There are no entry parameters
//
//RETURN VALUES
//This function returns a double (the variance)
double HashTables::calcVariance() {
    //
    //Use mean to calculate variance.
    int mean = getLoadFactor();
    
    double sum; //Variable used to calculate variance
    //
    //Iterates through the hash table.
    //
    for(int i = 0; i < getNumBuckets(); i++) {
        
        sum = sum + ((hashTable[i].size()- mean) * (hashTable[i].size()- mean));
    }
    
    double variance = sum / (getNumBuckets() - 1);
    return variance;
}

//isEmpty.
//isEmpty determines if a hash table is empty
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterating through the hash table array, if any vector is not empty,
//         the function returns false.
//      2. If all vectors are empty, the function returns true.
//
//ENTRY PARAMETERS
//There are no entry parameters
//
//RETURN VALUES
//This function returns a boolian signaling whether the hash table is empty.
bool HashTables::isEmpty() {
    //
    //Iterate through the hash table
    //
    for(int i = 0; i < getNumBuckets(); i++) {
        //
        //vector is not empty
        //
        if (hashTable[i].empty() == false) {
            return false;
        }
    }
    //
    //All vectors in hash table are empty.
    //
    return true;
}

//getNumBuckets.
//getNumBuckets returns the number of vectors in the hash table
//
//FUNCTIONAL DESCRIPTION.
//      1. Returns numBuckets, a private constant associated with the hash
//         table.
//
//ENTRY PARAMETERS
//None.
//
//RETURN VALUES
//This function returns an int (number of vectors in the HT).
int HashTables::getNumBuckets() {
    return numBuckets;
}

//getNumItems.
//getNumItems returns the number of entries in the hash table
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterates through the hash table and adds the size of the vector to
//         a variable.
//
//ENTRY PARAMETERS
//None.
//
//RETURN VALUES
//This function returns an int (number of entries in the HT).
int HashTables::getNumItems() {
    int numItems = 0;
    //
    //Iterates through the hash table
    //
    for (int i = 0; i < getNumBuckets(); i++) {
        //
        //Adds the size of the vector to numItems
        //
        numItems = numItems + hashTable[i].size();
    }
    return numItems;
}

//getLoadFactor.
//getLoadFactor returns the load factor of the hash table
//
//FUNCTIONAL DESCRIPTION.
//      1. Calculates and returns the load factor by dividing the number of
//         entries in the hash table by the number of vectors.
//
//ENTRY PARAMETERS
//None.
//
//RETURN VALUES
//This function returns an int (load factor).
int HashTables::getLoadFactor() {
    int loadFactor = getNumItems() / getNumBuckets();
    return loadFactor;
}

//printListSizes.
//printListSizes prints the size of each vector in the hash table
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterates through the hash table print the size of each vector on 
//         each iteration.
//
//ENTRY PARAMETERS
//None.
//
//RETURN VALUES
//This function does not return anything.
void HashTables::printListSizes() {
    //
    //Iterates through the hash table.
    //
    for(int i = 0; i < getNumBuckets(); i++) {
        cout << "Size of bucket: " << hashTable[i].size() << endl;
    }
}

//makeEmpty.
//makeEmpty clears each vector in the hash table.
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterates through the hash table, clearing each vector on each
//         iteration.
//
//ENTRY PARAMETERS
//None.
//
//RETURN VALUES
//This function does not return anything.
void HashTables::makeEmpty() {
    //
    //Iterates through the hash table.
    //
    for (int i = 0; i < getNumBuckets() ; i++) {
        hashTable[i].clear();
    }
}

//~HashTables.
//HashTables deconstructs the hash table.
//
//FUNCTIONAL DESCRIPTION.
//      1. Deletes the hash table.
//
//ENTRY PARAMETERS
//None
//
//RETURN VALUES
//This function does not return anything.
HashTables::~HashTables() {
    delete[] hashTable;
}


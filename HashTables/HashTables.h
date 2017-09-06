/* 
 * File:   HashTables.h
 * Author: HenryDaniels-Koch
 *
 * Created on May 1, 2015, 11:28 AM
 */

#ifndef HASHTABLES_H
#define	HASHTABLES_H

#include "Entry.h"
#include "GameBoard.h"
#include <vector>
#include <iomanip>
#define a 13 //Used to compress the hashcode value.
#define b 37 //Used to compress the hashcode value.
#define p 16908799 //Used to compress the hashcode value.

using namespace std;

class HashTables {

public:
    //
    //Constructs a hash table
    //
    HashTables(int loadFactor);
    //
    //Deconstructs the hash table
    //
    virtual ~HashTables();
    //
    //Inserts an entry into the hash table
    //
    Entry insert(GameBoard key, int value);
    //
    //Checks if the hash table is empty
    //
    bool isEmpty();
    //
    //Returns the length of the array of vectors--the hash table
    //
    int getNumBuckets();
    //
    //Returns the number of entries in the hash table
    //
    int getNumItems();
    //
    //Returns the load factor of the hash table
    //
    int getLoadFactor();
    //
    //Prints the size of each vector in the hash table
    //
    void printListSizes();
    //
    //Makes the hash table empty
    //
    void makeEmpty();
    //
    //Remove an entry from the hash table
    //
    Entry remove(GameBoard board);
    //
    //Finds an entry in the hash table
    //
    Entry find(GameBoard key);
    //
    //Compresses a hash value and returns the compressed value for use in HT
    //
    int compress(int hashCode);
    //
    //Calculates the variance in the tests of HT with various load factors
    //
    double calcVariance();
    
private:
    vector <Entry> *hashTable; //Array of vectors
    int numBuckets; //Number of vectors in array
};

#endif	/* HASHTABLES_H */


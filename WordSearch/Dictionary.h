/* 
 * File:   Dictionary.h
 * Author: HenryDaniels-Koch
 *
 * Created on February 27, 2015, 1:36 PM
 */

#ifndef DICTIONARY_H
#define	DICTIONARY_H
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Dictionary {
    
public:
    //
    //Constructs dictionary
    //
    Dictionary(); 
    
    //
    //Determines if a specified word is within the dictionary
    //
    bool binarySearch(string word); 
    
    //
    //Determines if a word in the dictinoary starts with a specified prefix
    //
    bool isPrefix(string prefix); //Searches for 
    
    //
    //Returns the number of words in the dictionary
    //
    int size() { return (int) dictionary.size();}
    
    //
    //Returns the word at a specified index of the dictionary
    //
    string at(int i) { return dictionary.at(i);}
    
private:
    vector<string> dictionary; //Creates a vector of strings
};

#endif	/* DICTIONARY_H */


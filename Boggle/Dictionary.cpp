/* 
 * File:   Dictionary.cpp
 * Author: HenryDaniels-Koch
 * 
 * Created on March 29, 2015, 8:45 PM
 */
//Dictionary.cpp.
//      Assignment4.c++-Source code for CSCI2101 Assignment .
//FUNCTIONAL DESCRIPTION
//      This program in C++ fulfills the requirements of Assignment 5 in
//      CSCI2101 Spring 2015
//
//      1. All functions are performed on the class: Dictionary.
//      2. Dictionary creates a dictionary by prompting the user for a
//         dictionary file, creating a vector of strings and reading the file
//         in line by line.
//      3. The size of the dictionary is printed.
//      4. The user can search for a word in the dictionary with binary search,
//         a fast algorithm.
//      5. The user can search for a prefix in the dictionary by comparing
//         the prefix the beginning of words in the dictionary.
//
//Notice
//      Copyright (C) March 27 2015 to April 8 2015.
//      Henry Daniels-Koch All Rights Reserved.
//
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Dictionary.h"
#include "Board.h" 

//Dictionary.
//Dictionary is a constructor method without parameters.
//
//FUNCTIONAL DESCRIPTION.
//      1. Prompt user to enter dictionary file name.
//      2. Read in dictionary line by line with each line a string in the
//         dictionary vector.
//      3. Dictionary size is printed.
//
//ENTRY PARAMETERS
//There are no entry parameters.
//
//RETURN VALUES
//This function does not return anything.
Dictionary::Dictionary() {

    //
    //Read file in
    //
    string fileName; 
    ifstream dictStream;
    
    //
    //Prompt user for dictionary file name until file is found.
    //
    do {
        cout << "Enter dictionary file name: ";
        cin >> fileName;
        dictStream.open(fileName.c_str(), ios::in);
    } while (!dictStream.good());      // Keep trying until this works
    
    string word = ""; //word is each word in dictinoary
    
    //
    // Make sure the file has some stuff in it.
    //
    if (!getline(dictStream, word)) {
        cerr << "Error: dictionary file is empty" << endl;
        return;
        
    
    } else {

        dictionary.push_back(word);
        
        //
        //Adds words to dictionary vector until end of file is reached.
        //
        while (dictStream >> word) {
            dictionary.push_back(word);  
        }
    }
    //
    //Print the number of words in the dictionary.
    //
    int dictSize = dictionary.size();
    cout << "Dictionary size is " << dictSize << endl << endl;  
    

    }

//binarySearch.
//binarySearch determines if a word is in the dictionary file.
//
//FUNCTIONAL DESCRIPTION.
//      1. binarySearch compares the entered word to the middle index of the
//         dictionary and returns true if the words are the same.
//      2. If the entered word occurs after the middle index, the function
//         searches for the word within the upper half of the dictionary.
//      3. Otherwise, the function searches for the word within the lower half
//         of the dictionary.
//      4. The function repeats this process of searching in the upper half or
//         lower half of the remaining part of the dictionary until the word is
//         found or dictionary has no words.
//
//ENTRY PARAMETERS
//word is the word being searched for.
//
//RETURN VALUES
//This function returns the boolian true if the word is found.
bool Dictionary::binarySearch(string word) {
    int iMidd = dictionary.size() / 2; //Middle index of dictionary
    int iEnd = dictionary.size() - 1; //Last index of dictionary
    int iStart = 0; //First index of dictinoary

    //
    //Searches for word in the dictionary until it is found or until the last
    //index is less than the first index which both are changed throughout the
    //loop.
    //
    while (iEnd > iStart) {
        //
        //Word is in dictionary.
        //
        if (dictionary.at(iMidd) == word) {
            return true;
         
        //
        //word occurs before the word at the middle index of the part of the 
        //dictionary being searched.
        //
        } else if (dictionary.at(iMidd) > word) {
            iEnd = iMidd -1;
            iMidd = (iEnd + iStart) / 2;
        //
        //word occurs after the word at the middle index of the part of the 
        //dictionary being searched.
        //
        } else {
            iStart = iMidd + 1;
            iMidd = (iEnd + iStart) / 2;
        }
    }
    //
    //word was not found in dictionary.
    //
    return false;
}

//isPrefix.
//isPrefix determines if a word in the dictionary file starts with the prefix
//
//FUNCTIONAL DESCRIPTION.
//      1. isPrefix compares the entered prefix to a substring of a word in the
//         dictionary at the middle index and returns true if the words are 
//         the same.
//      2. If the entered prefix occurs after the middle index, the function
//         searches for a word with the prefix within the upper half of the 
//         dictionary.
//      3. Otherwise, the function searches for the word  with the prefix 
//         within the lower half of the dictionary.
//      4. The function repeats this process of searching in the upper half or
//         lower half of the remaining part of the dictionary until a word with 
//         the prefix is found or dictionary has no words with that prefix.
//
//ENTRY PARAMETERS
//prefix is the prefix being searched for.
//
//RETURN VALUES
//This function returns the boolian true if the prefix is found.
bool Dictionary::isPrefix(string prefix) {
        
    int wordSize=prefix.length(); //Length of prefix
    int iMidd = dictionary.size() / 2; //Middle index of dictionary
    int iEnd = dictionary.size(); //Last index of dictionary
    int iStart = 0; //First index of dictionary
    
    //
    //Searches for word with the prefix in the dictionary until it is found or 
    //until the last index is less than the first index which both are changed 
    //throughout the while loop.
    //
    while (iEnd >= iStart) {
        //
        //The word at the middle index of the dictionary begins with prefix
        //
        if (dictionary.at(iMidd).substr(0,wordSize) == prefix) {
            return true;
        
        //
        //prefix occurs before the word at the middle index of the part of the 
        //dictionary being searched.
        //
        } else if (dictionary.at(iMidd) > prefix) {
            iEnd = iMidd -1;
            iMidd = (iEnd + iStart) / 2;
        
        //
        //prefix occurs after the word at the middle index of the part of the 
        //dictionary being searched.
        //
        } else {
            iStart = iMidd + 1;
            iMidd = (iEnd + iStart) / 2;
        }
    }
    //
    //No word in the dictionary begins with the specified prefix.
    //
    return false;

} 
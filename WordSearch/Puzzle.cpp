/* 
 * File:   Puzzle.cpp
 * Author: HenryDaniels-Koch
 * 
 * Created on February 27, 2015, 1:36 PM
 */
//Puzzle.cpp.
//      Assignment4.c++-Source code for CSCI2101 Assignment 4.
//FUNCTIONAL DESCRIPTION
//      This program in C++ fulfills the requirements of Assignment 4 in
//      CSCI2101 Spring 2015
//
//      1. All functions are performed on the class: Puzzle.
//      2. Puzzle creates a word search array by prompting the user for a
//         puzzle file, creating an array of characters and reading the file
//         in line by line.
//      3. If the file is not square, then the function prompts the user for
//         another file until a square array of characters is found.
//      4. The puzzle's dimensions and the puzzle itself are printed.
//      5. The user is prompted to enter the minimum word length of words that
//         are to be searched for in puzzle.
//      6. The user can use naiveSearch to search for words in the puzzle by
//         comparing the words in the puzzle to every word in the dictionary.
//      7. The user can use binaryAlgorithm to search for words in the puzzle by
//         going through each row, column, and direction in the puzzle and
//         calling binarySearch for each potential word.
//      8. The user can use prefixAlgorithm to search for words in the puzzle by
//         going through each row, column, and direction in the puzzle, checking
//         if the word is a prefix of any words in the dictionary and then 
//         calling binarySearch on the word if it is a prefix.
//
//Notice
//      Copyright (C) February 26, 2015 to March 27 2015.
//      Henry Daniels-Koch All Rights Reserved.
//
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include "Puzzle.h"

using namespace std;

//Puzzle.
//Puzzle is a constructor method without parameters.
//
//FUNCTIONAL DESCRIPTION.
//      1. Prompt user to enter puzzle file name.
//      2. Read in puzzle line by line with each line a row in the
//         character array.
//      3. If the puzzle is not square, then user is prompted to enter a puzzle
//         file name again until a square puzzle is found.
//      4. The puzzle's dimensions and the puzzle itself are printed.
//      5. The user is prompted to enter the minimum word length of words that
//         are to be searched for in puzzle. The minimum word length must be
//         less than the number of columns in the puzzle.
//
//ENTRY PARAMETERS
//There are no entry parameters.
//
//RETURN VALUES
//This function does not return anything.
Puzzle::Puzzle() {
    //
    //User will continue to be prompted until a file with a square character
    //array is entered.
    while (numCols != numRows) {
        //
        //Read file in.
        //
        string fileName; 
        ifstream puzzleStream; 

        //
        //Prompt user for puzzle file name until file is found.
        //
        do {
            cout << "Enter puzzle file name: ";
            cin >> fileName;
            puzzleStream.open(fileName.c_str(), ios::in);
        } while (!puzzleStream.good()); // Keep trying until this works
        
        string line;
        // Make sure the file has some stuff in it.
        if (!getline(puzzleStream, line)) {
            cerr << "Error: puzzle file is empty" << endl;
            //
            //Need numRows and numCols to be different in order to prompt user
            //for another filename.
            numRows = 0;
            numCols = -1; 
        }

        numCols = line.size();
        //
        //Iterate  across the row, filling in the first row the theBoard.
        //
        for (int i = 0; i < numCols; i++) {
            theBoard[0][i] = tolower(line.at(i));
        }
        
        bool signal = true; //If true, puzzle is rectangular
        
        //
        // Iterate down the column
        //
        for (numRows = 1; getline(puzzleStream, line); numRows++) {
            //
            // Puzzle is not rectangular.
            //
            if (line.size() != numCols) {
                cerr << "Error: puzzle is not rectangular" << endl << endl;
                signal = false;
                numCols = -1;
                break;
            } 
            //
            // Puzzle is rectangular.
            // Iterate across row and fill theBoard in.
            for (int i = 0; i < numCols; i++) {
                theBoard[numRows][i] = tolower(line.at(i));
            }

        }
        //
        //Puzzle is rectangular, but not square (extra row(s) or column(s))
        if (numCols != numRows && signal == true) {
            cout << "Error: Puzzle is not square" << endl << endl;
        }
    }
    //
    //Print dimensions
    //
    printDimensions();

    //
    //Print Puzzle
    //
    printPuzzle();

    //
    //Ask for minimum word length.
    //Minimum word length must be less than or equal to numCols
    //
    do {
    cout << "\nEnter minimum word length: ";
    cin >> minWordLength;
    } while (minWordLength > numCols);
    
    

}

//printDimensions.
//printDimensions prints dimensions of puzzle.
//
//FUNCTIONAL DESCRIPTION.
//      1. Prints number of columns.
//      2. Prints number of rows.
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void Puzzle::printDimensions() {
    printf("Read puzzle with ");
    printf("%d", numCols);
    printf(" rows and ");
    printf("%d", numRows);
    printf(" columns\n\n");
}

//printPuzzle.
//printPuzzle prints the character array theBoard
//
//FUNCTIONAL DESCRIPTION.
//      1. Prints theBoard.
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void Puzzle::printPuzzle() {
    for (int i = 0; i < numRows; i++) { //Iterates through each row
        
        for (int j = 0; j < numCols; j++) { //Iterates through each column
            
            //
            //Prints the uppercase letter of the character at (i,j)
            //
            printf(" %c", toupper(theBoard[i][j])); //
        }
        printf("\n");
    }
}

//naiveSearch.
//naiveSearch searches for words in the puzzle in a naive way.
//FUNCTIONAL DESCRIPTION
//
//      1. A clock to time the search is started.
//      2. The function iterates through all the words in dictionary, across
//         each row in the puzzle, each column in the puzzle, each direction (8)
//         and across the array until the end of the array is reached adding
//         characters to "word".
//      3. If the string in the puzzle is a word in the dictionary that is 
//         greater than the minimum word length, the word is printed along with
//         its coordinates in the puzzle.
//      4. Throughout this algorithm if there is a word in the dictionary 
//         that is less than the minimum word length, the function goes to the
//         next word.
//
void Puzzle::naiveSearch() {
    cout << endl << "Using naive approach:" << endl;
    //
    //Clock is started.
    //
    double start, end, seconds;
    start= clock();

    int sum = 0; //Keeps track of number of words found
    
    string word= ""; //word is a string in the character array
    
    //
    //Iterates through all words in the dictionary
    //
    for (int i = 0; i < dictionary.size(); i++) { 
        
        string dictWord = (dictionary.at(i));
        
        int wordLength = dictWord.length();
        
        //
        //Word in dictionary is greater than the minimum word length.
        //
        if (wordLength >= minWordLength) {
            //
            //Iterates down rows
            //
            for (int j = 0; j < numRows; j++) { 
                //
                //Iterates across columns
                //
                for (int k = 0; k < numCols; k++) { 
                    //
                    //The first letter of word in dictionary matches letter on
                    //theBoard
                    //
                    if (dictWord[0] == theBoard[j][k]) {
                        //
                        //rDelta and cDelta help to iterate through 8 directions
                        //Iterate row directions first
                        //
                        for (int rDelta = -1; rDelta <= 1; ++rDelta) { 
                            //
                            //Iterates column directions
                            //
                            for (int cDelta = -1; cDelta <= 1; ++cDelta) { 
                                word = ""; //Resets word in puzzle
                                //
                                //Makes sure function is going in a direction
                                if (rDelta != 0 || cDelta != 0) {
                                    //
                                    //Iterates across array, adding characters
                                    //to word until word is greater than the
                                    //word in the dictionary
                                    //
                                    for (int p = 0; p < wordLength; p++) { 
                                        //
                                        //Current row
                                        //
                                        int rInside = (j + (rDelta * p));
                                        //
                                        //Current column
                                        //
                                        int cInside = (k + (cDelta * p));
                                        //
                                        //Make sure to stay inside array
                                        //
                                        if ((cInside < numCols) && 
                                                (cInside >= 0) && 
                                                (rInside < numRows) && 
                                                (rInside >= 0)) {
                                            //
                                            //Add the next character to word in
                                            //a specific direction
                                            //
                                            word = word + 
                                                    theBoard[j + (rDelta * p)]
                                                    [k + (cDelta * p)];
                                            //
                                            //Character in word at p matches
                                            //the character in the dictionary
                                            //word
                                            if (word[p] == dictWord[p]) {
                                                //
                                                //word in theBoard matches
                                                //dictionary word
                                                if (dictWord == word) {
                                                    cout << "Found ''"  << word 
                                                            << "'' at (" << j 
                                                            << "," << k << 
                                                            ") to (" << j + 
                                                            (rDelta*p) << "," 
                                                            << k + (cDelta * p)
                                                            << ")" << endl;
                                                    sum = sum + 1;
                                                }
                                            //
                                            //Character in word at p does not 
                                            //match the character in the 
                                            //dictionary word
                                            //
                                            } else {
                                                break;
                                            }
                                        //
                                        //Word is outside the array
                                        //
                                        } else {
                                            break;
                                        }

                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
    }
    //
    //End the clock
    //
    end = clock();
    seconds = (end-start)/ CLOCKS_PER_SEC;
    //
    //Print the number of matches and run time.
    cout << "Found " << sum << " matches" << endl;
    cout << "Solution Time: " << seconds << " seconds." << endl << endl;
}


//binaryAlgorithm.
//binaryAlgorithm searches for words in the puzzle using binarySearch.
//FUNCTIONAL DESCRIPTION
//
//      1. A clock to time the search is started.
//      2. The function iterates across each row in the puzzle, each column in 
//         the puzzle, each direction (8) and across the array until the end of 
//         the array is reached while adding characters to "word".
//      3. Using binarySearch, if the string in the puzzle is a word in the 
//         dictionary that is greater than the minimum word length, the word is 
//         printed along with its coordinates in the puzzle.
//      4. The clock is stopped, and both run time and the number of words 
//         found are printed.
//
void Puzzle::binaryAlgorithm() {
    cout << "Using direction approach: " << endl;
    //
    //Clock is started
    //
    double start, end, seconds;
    start= clock();

    int sum = 0;//Keeps track of number of words found
    
    string word = ""; //word is a string in the character array
    
    //
    //Iterates down rows
    //
    for (int j = 0; j < numRows; j++) { 
        //
        //Iterates across columns
        //
        for (int k = 0; k < numCols; k++) { 
                //
                //rDelta and cDelta help to iterate through 8 directions
                //Iterate row directions first
                //
                for (int rDelta = -1; rDelta <= 1; ++rDelta) { 
                    //
                    //Iterate column directions
                    //
                    for (int cDelta = -1; cDelta <= 1; ++cDelta) { 
                        word = ""; //Reset word
                        
                        //
                        //Makes sure function is going in some direction 
                        //
                        if (rDelta != 0 || cDelta != 0) {
                            
                            //
                            //Iterates across array, adding characters
                            //to word until word is outside of array
                            //
                            for (int p = 0; p < numCols; p++) {

                                int rInside = (j + (rDelta * p));//current row
                                
                                int cInside = (k + (cDelta * p));//current col
                                //
                                //Word is still in array
                                //
                                if ((cInside < numCols) && (cInside >= 0) &&
                                        (rInside < numRows) && (rInside >= 0)) {
                                    
                                    //
                                    //Add the next character to word in
                                    //a specific direction
                                    //
                                    word = word + theBoard[j + (rDelta * p)]
                                            [k + (cDelta * p)];
                                    
                                    //
                                    //word is in dictionary and greater than
                                    //minWordLength.
                                    //
                                    if (dictionary.binarySearch(word) == true &&
                                            word.size() >= minWordLength) {
                                        cout << "Found ''"  << word 
                                        << "'' at (" << j << "," 
                                        << k << ") to (" << 
                                        j + (rDelta*p) << 
                                         "," << k + (cDelta * p)
                                        << ")" << endl;
                                        sum = sum + 1;
                                    }
                                //
                                //Word is outside array
                                //
                                } else {
                                    break;
                                }

                            }
                        }
                    }

                }
            }
        }
    //
    //End the clock.
    //
    end = clock();
    seconds = (end-start)/ CLOCKS_PER_SEC;
    //
    //Print the number of matches and run time.
    //
    cout << "Found " << sum << " matches" << endl;
    cout << "Solution Time: " << seconds << " seconds." << endl <<endl;
}
    
//prefixAlgorithm.
//prefix Algorithm searches for words in the puzzle using isPrefix
//FUNCTIONAL DESCRIPTION
//
//      1. A clock to time the search is started.
//      2. The function iterates across each row in the puzzle, each column in 
//         the puzzle, each direction (8) and across the array until the end of 
//         the array is reached while adding characters to "word".
//      3. Using isPrefix, if the string in the puzzle is not a prefix of a word
//         in the dictionary, the for loop breaks.
//      3. Otherwise, using binarySearch, if the string in the puzzle is a word
//         in the dictionary that is greater than the minimum word length, the 
//         word is printed along with its coordinates in the puzzle.
//      4. The clock is stopped, and both run time and the number of words 
//         found are printed.
//  
void Puzzle::prefixAlgorithm() {
    cout << "Using direction approach with prefixes:" << endl;
    //
    //Start clock.
    //
    double start, end, seconds;
    start= clock();
    
    string word = ""; //word is a string in the puzzle
    
    int sum = 0; //sum keeps track of the number of words found
    
    //
    //Iterates down rows
    //
    for (int j = 0; j < numRows; j++) { 
        
        //
        //Iterates across columns
        //
        for (int k = 0; k < numCols; k++) { 
                
                //
                //rDelta and cDelta help to iterate through 8 directions
                //Iterate row directions first
                //
                for (int rDelta = -1; rDelta <= 1; ++rDelta) { 

                    //
                    //Iterate column directions
                    //
                    for (int cDelta = -1; cDelta <= 1; ++cDelta) {
                        
                        word = ""; //Reset word.
                        
                        //
                        //Makes sure function is going in some direction 
                        //
                        if (rDelta != 0 || cDelta != 0) {
                            
                            //
                            //Iterates across array, adding characters
                            //to word until word is outside of array.
                            //
                            for (int p = 0; p < numCols; p++) { 

                                int rInside = (j + (rDelta * p)); //current row
                                int cInside = (k + (cDelta * p)); //current col
                                //
                                //word is inside array.
                                //
                                if ((cInside < numCols) && (cInside >= 0) &&
                                        (rInside < numRows) && (rInside >= 0)) {
                                    //
                                    //Add the next character to word in
                                    //a specific direction
                                    //
                                    word = word + theBoard[j + (rDelta * p)]
                                            [k + (cDelta * p)];
                                    
                                    //
                                    //word is not a prefix of a word in the
                                    //dictionary.
                                    if (dictionary.isPrefix(word) == false) {
                                        break;
                                    }
                                    
                                    //
                                    //word is in dictionary and greater than
                                    //minWordLength.
                                    //
                                    if (dictionary.binarySearch(word) == true &&
                                            word.size() >= minWordLength) {
                                        cout << "Found ''"  << word << "'' at ("
                                                << j << "," << k << ") to (" << 
                                                j + (rDelta*p) <<  "," << k + 
                                                (cDelta * p)<< ")" << endl;
                                        sum = sum + 1;
                                    }
                                //
                                //word is outside the array
                                //
                                } else { 
                                    break;
                                }

                            }
                        }
                    }

                }
            }
        }
    //
    //End clock.
    end = clock();
    seconds = (end-start)/ CLOCKS_PER_SEC;
    //Print number of matches and run time.
    cout << "Found " << sum << " matches" << endl;
    cout << "Solution Time: " << seconds << " seconds." << endl;
}
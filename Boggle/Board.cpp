/* 
 * File:   Board.cpp
 * Author: HenryDaniels-Koch
 * 
 * Created on March 29, 2015, 8:03 PM
 */
//Board.cpp
//Board.cpp creates a board that can be searched for legal words in Boggle.
//
//FUNCTIONAL DESCRIPTION.
//      1. All functions are performed on the class Board.
//      2. Prompt user to enter Boggle Board file name.
//      3. Read in board line by line with each line a row in the
//         character array.
//      4. If the board is not square, then user is prompted to enter a board
//         file name again until a square board is found.
//      5. The board's dimensions and the board itself are printed.
//      5. The user is asked if they want to play before the computer demolishes
//         them. 
//      6. The computer finds all legal words.
//      7. If user wants to play, their inputed words are checked for legality.
//      8. Words found by the human and computer are shown along with scores.
//
//Notice
//      Copyright (C) March 27, 2015 to April 2, 2015.
//      Henry Daniels-Koch All Rights Reserved.
//

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctype.h>
#include "Board.h"

using namespace std;

//Board.
//Board is a constructor method without parameters.
//
//FUNCTIONAL DESCRIPTION.
//      1. Prompt user to enter Boggle Board file name.
//      2. Read in board line by line with each line a row in the
//         character array.
//      3. If the board is not square, then user is prompted to enter a board
//         file name again until a square board is found.
//      4. The board's dimensions and the board itself are printed.
//      5. The user is asked if they want to play before the computer demolishes
//         them. 
//      6. The computer finds all possible words.
//      7. If user wants to play, their inputed words are checked for legality.
//      8. Words found by the human and computer are shown along with scores.
//
//ENTRY PARAMETERS
//There are no entry parameters.
//
//RETURN VALUES
//This function does not return anything.
Board::Board() {
    
    //
    //User will continue to be prompted until a file with a square character
    //array is entered.
    
    //
    //Set numCols to be something other than 0 so that the while loop continues
    //until a file with a square board is entered.
    //
    numCols = -1;
    
    while (numCols != numRows) {
        //
        //Read file in.
        //
        string fileName; 
        ifstream puzzleStream; 

        //
        //Prompt user for board file name until file is found.
        //
        do {
            cout << "Enter Boggle board file name: ";
            cin >> fileName;
            puzzleStream.open(fileName.c_str(), ios::in);
        } while (!puzzleStream.good()); // Keep trying until this works
        
        string line;
        //
        // Make sure the file has some stuff in it.
        //
        bool empty = false;
        
        if (!getline(puzzleStream, line)) {
            cerr << "Error: puzzle file is empty" << endl;
            empty = true;
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
            // Board is not rectangular but is not empty.
            //
            if (line.size() != numCols && empty == false) {
                cerr << "Error: puzzle is not rectangular" << endl << endl;
                signal = false;
                numCols = -1;
                break;
            } 
            //
            // Board is rectangular.
            // Iterate across row and fill theBoard in.
            //
            for (int i = 0; i < numCols; i++) {
                theBoard[numRows][i] = tolower(line.at(i));
            }

        }

        //
        //Board is rectangular and not empty, but not square 
        //(extra row(s) or column(s))
        //
        if (numCols != numRows && signal == true && empty == false) {
            cout << "Error: Puzzle is not square" << endl << endl;
        }
    }
    //
    //Print dimensions
    //
    printDimensions();

    //
    //Print board
    //
    printBoard();
    
    //
    //Ask if user wants to play or let computer solve it
    //
    string userPlay = "";
    cout << "Would you like to make a fool of yourself and find a few "
            "words before the computer finds them all and demolishes you? "
            "(y or n) ";
    
    while (userPlay != "y" && userPlay != "n") { // Keep trying until this works
        cin >> userPlay;
        cout << endl;
        if (userPlay == "y" || userPlay == "n") {
            break;
        }
        cout << "Error: not a valid choice." << endl;
    }
    //
    //Computer first finds all words in the board (without printing them)
    //
    compBoggle();
    
    //
    //User wants to play
    //
    if (userPlay == "y") {
        userSolve();
        printHumanWords();
    }
    
    
    printCompWords();
    cout << "Better luck next time." << endl;
    cout << "Just kidding, you will never win." << endl;
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
void Board::printDimensions() {
    printf("Read puzzle with ");
    printf("%d", numCols);
    printf(" rows and ");
    printf("%d", numRows);
    printf(" columns\n\n");
}

//printBoard.
//printBoard prints the character array theBoard
//
//FUNCTIONAL DESCRIPTION.
//      1. Prints theBoard.
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void Board::printBoard() {
    for (int i = 0; i < numRows; i++) { //Iterates through each row
        
        for (int j = 0; j < numCols; j++) { //Iterates through each column
            
            //
            //Prints the uppercase letter of the character at (i,j)
            //
            printf(" %c", toupper(theBoard[i][j])); //
        }
        printf("\n");
    }
    cout << endl;
}

//checkLegality.
//checkLegality checks if the word should be counted
//
//FUNCTIONAL DESCRIPTION.
//      1. Checks if the the word is in the dictionary and is long enough.
//      2. If the word satisfies these requirements and is not a duplicate,
//         the function adds the word to the vector list of legal words found 
//         by the computer
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void Board::checkLegality(string word) {
    if (dictionary.binarySearch(word) == true && word.length() >= MINWORDLENGTH) {
        //
        //Check for duplicates by iterating through compWords
        //
        for (int i=0; i < compWords.size(); i++) {
            
            if (word == compWords[i]) { //Word is already in compWords
                return;  
            }
        }
        compWords.push_back(word); //add word to compWords

        
    } 
}

//userSolve.
//userSolve allows user to enter words they find and checks if they count
//
//FUNCTIONAL DESCRIPTION.
//      1. Prompt user to enter word.
//      2. Check for duplicates, if the word is long enough, if the word is in
//         the dictionary, and if the word is on the board.
//      3. If the word satisfies these statements, the word is added to 
//         the vector string: humanWords.
//      4. If the word does not satisfy one or more of these conditions, a 
//         statement explaining why it does not count is shown.
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void Board::userSolve() {
    cout << "Enter as many words as you want, one to a line." << endl;
    cout << "Enter an exclamation point when you are done." << endl << endl;
    
    //
    //User enters potential word(s)
    //
    string userWord;
    
    while (userWord != "!") {
        cin >> userWord;
    
        //
        //Check if user wants to stop searching
        //
        if (userWord == "!") {
            cout << endl;
            return;
        }

        bool valid = true; //When valid is true, word is valid
        
        //
        //Check for duplicates by iterating through humanWords
        //
        for (int i=0; i < humanWords.size(); i++) {

            if (userWord == humanWords[i]) { //Word is already in compWords
                cout << "    Invalid word: already used." << endl;
                valid = false;
                break;  
            }
        }
        
        //
        //word is not a duplicate
        //
        if (valid == true) {
            //
            //Check if word is long enough
            //
            if (userWord.length() < MINWORDLENGTH) {
                cout << "    Invalid word: words must have 3 or more characters"
                        <<endl;
                valid = false;
            }
            //
            //Check if userWord is in the dictionary
            //
            if (dictionary.binarySearch(userWord) == false) { 
                cout << "    Invalid word: word is not in dictionary" << endl;
                valid = false;

            } 

            //
            //Check if userWord is on the board
            //
            bool wordFound = false; //If wordFound is true, it is in board
            //
            //Search compWords for userWord
            //
            for (int i=0; i < compWords.size(); i++) {

                if (userWord == compWords[i]) { //Word is already in compWords
                    cout << "    Good Word!" << endl;
                    humanWords.push_back(userWord);
                    wordFound = true;
                    break;  
                } 
            } 

            //
            //Check if userWord is not on board
            //
            if (wordFound == false) {
                cout << "    Invalid word: word not in the board" << endl;
            }
        }  
    }  
    cout << endl;
}

//compBoggle.
//compBoggle finds all the legal words on the board
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterates through all positions on board to find all potential words
//         starting with each letter on the board.
//      2. searchWord recursively searches for all legal words the start with 
//         the letter at a specific row and column.
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void Board::compBoggle() {
    //
    //Start clock.
    //
    double start, end, seconds;
    start= clock();
    
    //
    //Iterates down rows
    //
    for (int j = 0; j < numRows; j++) { 
        
        //
        //Iterates across columns
        //
        for (int k = 0; k < numCols; k++) { 
            string word = ""; //Reset word.
            //
            //Search for all possible words starting at [j][k]
            //
            searchWord(j,k,word);
        }
    }
    cout << endl;
}

//searchWord.
//searchWord recursively searches for all legal words that start with a letter 
//
//FUNCTIONAL DESCRIPTION.
//      1. Base Case 1: If the word is going outside of the array of the letter 
//         the function is at is a blank, the function returns.
//      2. The new letter is added and if the letter is a q, then a u is also
//         added.
//      3. Base Case 2: If the word is not a prefix of a word in the dictionary,
//         the function returns.
//      4. A place holder at the letter is created and the letter on the board
//         is changed to a space in order to not use that letter again.
//      5. checkLegality checks if the word is long enough, if the word is in
//         the dictionary, and if the word is on the board.
//      6. The function iterates in all 8 directions, calling searchWord in each
//         direction.
//      7. When a base case is satisfied, the blanks that were created are
//         filled in with their original characters using the place holder.
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void Board::searchWord(int rows, int cols, string word) {
    //
    //Base Case 1
    //Word is either outside the array or
    //the letter you are at is a blank space
    //
    if (rows == numRows || rows < 0 || cols == numCols || numCols < 0 || 
            theBoard[rows][cols] == ' ') {
        return;
    }
    //
    //add u letter if it is 'q'
    //
    if (theBoard[rows][cols] == 'q') {
        //string addu = "qu";
        word = word + theBoard[rows][cols] + 'u';
    
    } else {
        //
        //add letter to word (letter is not q)
        //
        word = word + theBoard[rows][cols];
    }
    
    //
    //Base Case 2
    //Word is not a prefix.
    //
    if (dictionary.isPrefix(word) == false) {
        return;
    }
    //
    //Create placeholder and change spot to a blank space
    //
    char placeHolder = theBoard[rows][cols];
    theBoard[rows][cols] = ' ';
    
    //
    //Check if word is legal
    //
    checkLegality(word);
    
    //
    //rDelta and cDelta help to iterate through 8 directions
    //Iterate row directions first
    //
    for (int rDelta = -1; rDelta <= 1; ++rDelta) { 

        //
        //Iterate column directions
        //
        for (int cDelta = -1; cDelta <= 1; ++cDelta) {

            //
            //Makes sure function is going in some direction 
            //
            if (rDelta != 0 || cDelta != 0) {
                searchWord(rows+rDelta,cols+cDelta,word);
            }
        }
    }
    //
    //The character held by placeHolder is reinserted back into the board
    //
    theBoard[rows][cols] = placeHolder;
}

//printCompWords.
//printCompWords prints all the legal words found by the computer
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterates through all the words in compWords.
//      2. For each word in the compWords, the function checks if the human
//         already found the word.
//      3. Each word is printed and if the human already found the word, a
//         statement is printed.
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void Board::printCompWords() {
    cout << "Computer Words:" << endl;
    cout << "===============" << endl;
    
    //
    //Sort words found by human
    //
    sort(compWords.begin(), compWords.end()); 
    
    //
    //If humanFound is true, the human found the word
    //
    bool humanFound = false;
    
    int score = 0; //Total computer score
    //
    //Iterates through compWords
    //
    for (int i = 0; i < compWords.size(); i++) { 
        
        humanFound = false; //Reset indicator
        
        //
        //Iterates through humanWords
        //
        for (int j = 0; j < humanWords.size(); j++) { 
            
            if (compWords[i] == humanWords[j]) { //Human has already found word
                cout << compWords[i] << "   Disallowed: found by human" << endl;
                humanFound = true;
                break;
            }
        }

        if (humanFound == false) { //Human did not find word
            cout << compWords[i] << endl;
            
            //
            //Compute letter based score for computer
            //
            if (compWords[i].length() == 3 || compWords[i].length() == 4) {
            score = score + 1;
            }
            if (compWords[i].length() == 5) {
                score = score + 2;
            }
            if (compWords[i].length() == 6) {
                score = score + 3;
            }
            if (compWords[i].length() >= 7 && compWords[i].length() < 11) {
                score = score + 5;
            }
            if (compWords[i].length() >= 11) {
                score = score + 8;
            } 
        }
    }
    cout << endl;
    cout << "Words Found (that human has no already found): " << 
            compWords.size() - humanWords.size() << endl;
    cout << "Letter-based Score: " << score << endl << endl;
}

//printHumanWords.
//printHumanWords prints all the legal words found by the human
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterates through all the words in humanWords and prints them.
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void Board::printHumanWords() {
    cout << "Human Words:" << endl;
    cout << "============" << endl;
    //
    //Sort words found by human
    //
    sort(humanWords.begin(), humanWords.end()); 
    
    int score = 0; //Letter-based score
    
    for (int i = 0; i < humanWords.size(); i++) { //Iterate through human words
        cout << humanWords[i] << endl;
        
        //
        //Add to letter based score
        //
        if (humanWords[i].length() == 3 || humanWords[i].length() == 4) {
            score = score + 1;
        }
        if (humanWords[i].length() == 5) {
            score = score + 2;
        }
        if (humanWords[i].length() == 6) {
            score = score + 3;
        }
        if (humanWords[i].length() >= 7 && humanWords[i].length() < 11) {
            score = score + 5;
        }
        if (humanWords[i].length() >= 11) {
            score = score + 8;
        }
    }
    cout << endl;
    cout << "Words Found: " << humanWords.size() << endl;
    cout << "Letter-based Score: " << score << endl << endl;
}
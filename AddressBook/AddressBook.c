/* 
 * File:   AddressBook.c
 * Author: HenryDaniels-Koch
 *
 * Created on February 6, 2015, 1:39 PM
 */

//AddressBook.c.
//      Assignment2.c-Source code for CSCI2101 Assignment 2.
//FUNCTIONAL DESCRIPTION
//      This program in C fulfills the requirements of Assignment 2 in
//      CSCI2101 Spring 2015
//
//      1. Load contact information from the file AddressBookData.txt.
//      2. Ask the user to input a last name and search all contacts for the
//         name, printing the data for that entry if found.
//      3. Ask the user for a month and print the names and birth dates of 
//         people whose birthdays are in that month.
//      4. Ask the user for two letter and print the names of people whose 
//         last names in the range specified by the two letters.
//      5. Create a loop that sorts the array from lowest to highest.
//      6. Print the sorted array.
//      7. Free the memory used for the list and exit the program with a success
//         status.
//
//Notice
//      Copyright (C) February 5, 2015 to February 19 2015.
//      Henry Daniels-Koch All Rights Reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "AddressBook.h"
#include <string.h>
/*
 * 
 */
int main(int argc, char** argv) {
    addressInfo *headPtr=loadData(); //Load data into list.

    //
    //Searches list for user input last name and prints contact info of this
    //person.
    //
    searchLastName(headPtr);
    
    //
    //Search list for names with user input birthMonth ane prints names
    //and birthdays.
    //
    searchMonthNames(headPtr);
    
    //
    //Searches list for lastNames the begin with a letter in a user input range
    //and prints the names in this range.
    //
    nameRange(headPtr);

    //
    //Free space in list/
    //
    freeList(headPtr);
    
    return (EXIT_SUCCESS);
}

//loadData.
//loadData loads all entries from a text file into a linked list.
//
//FUNCTIONAL DESCRIPTION.
//      1. loadData gets a contact from AddressBookData.txt and stores it in a
//         struct.
//      2. This struct is added to a sorted linked list using the 
//         insertNode function.
//
//ENTRY PARAMETERS
//There are no entry parameters.
//
//RETURN VALUES
//This function returns a pointer to the head of the list.
addressInfo *loadData() { 
    
    //read data from file into inputf.
    FILE *inputf; 
    char buffer[BUFFER_SIZE]; //Create string length BUFFER_SIZE.
    inputf=fopen("phoneBook.txt", "r");


    addressInfo *headPtr; //Declare pointer to head of list.
    headPtr = NULL;

    //
    //Iterates through each line in inputf, scanning the data into a node in
    //the list. The node is inserted into the list such that the list is sorted
    //alphabetically by last name. 
    //
    while (fgets(buffer, BUFFER_SIZE, inputf) != NULL) {

       //Creating a node to be filled with contact info of one person
       addressInfo *nodePtr = (addressInfo *) malloc(sizeof (addressInfo)); 
       nodePtr->next=NULL;

       //No memory for nodePtr
       if (nodePtr == NULL) {
            printf("error: malloc returned NULL");
            return NULL;
       }

       //
       //Scan each CSV into nodePtr from the file
       //
       sscanf(buffer, "%[^,],%[^,],%[^,],%[^,],%d,%d,%d",
       nodePtr->lastName,
       nodePtr->firstName,
       nodePtr->address,
       nodePtr->phoneNumber,
       &nodePtr->month,
       &nodePtr->day,
       &nodePtr->year);

       //
       //Insert nodePtr into the list such that the list is sorted.
       //
       headPtr=insertNode(headPtr,nodePtr);
       //printAllContacts(headPtr);

    }

    fclose(inputf);
    return headPtr;
   
}

//printContact.
//printContact prints all the contact info of one person.
//
//FUNCTIONAL DESCRIPTION.
//      1. printContact prints each piece of info from a node in the contact 
//          list.
//
//ENTRY PARAMETERS
//*nodePtr is a pointer to the struct addressInfo.
//
//RETURN VALUES
//This function does not return anything.
void printContact(addressInfo *nodePtr) {
    printf("%s,%s,%s,%d,%d,%d,%s\n",nodePtr->lastName,nodePtr->firstName,
            nodePtr->phoneNumber,nodePtr->month,
            nodePtr->day,nodePtr->year,nodePtr->address);
}

//printAllContacts.
//printAllContacts prints all the contact info of everyone.
//
//FUNCTIONAL DESCRIPTION.
//      1. printAllContacts traverses down the list from headPtr and prints 
//         each person's information on the list.
//
//ENTRY PARAMETERS
//*headPtr is a pointer to the struct addressInfo.
//
//RETURN VALUES
//This function does not return anything.
void printAllContacts(addressInfo *headPtr) {
    addressInfo *nodePtr; //Create node to traverse list.
    nodePtr=headPtr;
    
    //
    //Iterate through the list until the end is reached.
    //
    while (nodePtr != NULL) {
        printf("%s,%s,%s,%d,%d,%d,%s\n",nodePtr->lastName,nodePtr->firstName,
            nodePtr->phoneNumber,nodePtr->month,
            nodePtr->day,nodePtr->year,nodePtr->address);
        nodePtr=nodePtr->next;
    }
}

//insertNode.
//insertNode inserts an entry to a location on the list such that the list 
//is sorted.
//
//FUNCTIONAL DESCRIPTION.
//      1. If list is empty, put  new node at head of list.
//      2. If list has one entry, put new node before or after the first node 
//         by checking which last name comes first.
//      3. If list has two or more entries, iterate down the list until place
//         where new node should be put is found.
//      4. Return head of list.

//ENTRY PARAMETERS
//*headPtr is the head of the list.
//*nodePtr is the node you are inserting.
//
//RETURN VALUES
//This function returns a pointer to the head of the list.
addressInfo *insertNode(addressInfo *headPtr,addressInfo *nodePtr) {
    
    //
    //The list is empty. 
    //Insert nodePtr to beginning of list.
    //
    if (headPtr == NULL) {
        return nodePtr;
        
      //
      //There is only one entry in the list. 
      //
    } else if (headPtr->next == NULL) {
        int strcmpNumber; //strcmpNumber is used to compare names.
        strcmpNumber=strcmp(headPtr->lastName,nodePtr->lastName);

        //
        //nodePtr should come before headPtr.
        //
        if (strcmpNumber > 0) { 
            nodePtr->next=headPtr;
            return nodePtr;
        }
        //
        //nodePtr should go after headPtr.
        //
        if (strcmpNumber < 0) {
            headPtr->next=nodePtr;
            return headPtr;
        }
      //
      //At least two entries of the list are filled.
      //
    } else {
        //
        //Check  if node goes at head of list
        //
        int compStrings; //compStrings is used to compare strings.
        compStrings=strcmp(headPtr->lastName,nodePtr->lastName);
        
        if (compStrings > 0) {
            nodePtr->next=headPtr;
            return nodePtr;
        }
        
        //
        //Create nodes to move along list.
        //
        addressInfo *currentPtr;
        addressInfo *previousPtr;

        previousPtr=headPtr;
        currentPtr=headPtr->next;
        
        //
        //Iterate through list until end of list is reached or nodePtr comes
        //before currentPtr.
        //
        while (currentPtr != NULL && strcmp(nodePtr->lastName,
                currentPtr->lastName) > 0) {
            previousPtr=currentPtr;
            currentPtr=currentPtr->next;
    }
        //
        //Not at end of list and want to insert node before currentPtr.
        //
        if (currentPtr!=NULL) {
            previousPtr->next=nodePtr;
            nodePtr->next=currentPtr;
        }
        
        //
        //At end of list. 
        //Want to insert nodePtr at end of list.
        //
        else {
            previousPtr->next=nodePtr;
        }
    //
    // The value of headPtr may have changed (if it was NULL)
    // so we will return the value of headPtr (even though it
    // might not have changed).
    //
    return headPtr;
    } 
}

//searchLastName.
//searchLastName searches the contacts for a user input address and prints it.
//
//FUNCTIONAL DESCRIPTION.
//      1. Ask user to input last name to search.
//      2. Iterate through each last name on the list checking to see if it 
//         matches the user input last name.
//      3. Print the name if it matches.
//
//ENTRY PARAMETERS
//*headPtr is the head of the list.
//
//RETURN VALUES
//This function does not return anything.
void searchLastName(addressInfo *headPtr) {
    //
    //Allocate space for string.
    //
    char lastNameInput[30];

    //
    //Ask user for last name and scan input.
    //
    printf("Enter the last name you would like to search for: ");
    scanf("%s",lastNameInput);
    
    //
    //Create pointers to traverse list.
    //
    addressInfo *currentPtr;
    currentPtr=headPtr;
    
    //
    //Iterate through list until end of list is reached or user input name
    //matches a  last name in the list.
    //
    while (currentPtr != NULL && 
            strcmp(lastNameInput,currentPtr->lastName) != 0) {
        currentPtr=currentPtr->next; 
    }
    
    //
    //End of list is reached without finding a name matching user input.
    //
    if (currentPtr == NULL) {
        printf("Name not found\n");

      //
      //User input name matches a name in the list.
      //
    } else {
        printContact(currentPtr);
        
    }
}

//searchMonthNames.
//searchMonthNames searches the all contacts that match a user input month.
//
//FUNCTIONAL DESCRIPTION.
//      1. Ask user to input month.
//      2. Iterate through each contact's months on the list checking to see if 
//         it matches the user input month.
//      3. Print the name if the months match.
//
//ENTRY PARAMETERS
//*headPtr is the head of the list.
//
//RETURN VALUES
//This function does not return anything.
void searchMonthNames(addressInfo *headPtr) {

    int month; //User will input month from 1 to 12.

    //
    //Ask user for birth month and scan it to month.
    //
    printf("Enter the birth month of the people you "
            "would like to search for: ");
    scanf("%d",&month);
    
    //
    //User entered a non valid month number
    //
    if (month > 12 || month < 1) {
        printf("User did not enter a proper month\n");
        return;
        }
    //
    //Create pointers to traverse list.
    //
    addressInfo *currentPtr;
    currentPtr=headPtr;
    
    int monthFound; //indicator to signal if month is found
    
    //
    //Traverse list until end is reached.
    //
    while (currentPtr != NULL) {
        //
        //User input month matches a contact's birth month.
        //
        if (currentPtr->month == month) {
            printf("%s,%s,%d,%d,%d\n",currentPtr->lastName,
                    currentPtr->firstName,currentPtr->month,
                    currentPtr->day,currentPtr->year);
            monthFound=1; //month found
        }
        currentPtr=currentPtr->next;
    }
    //
    //No contacts with user input birth month were found.
    //
    if (monthFound != 1) {
        printf("No birthdays were found in this month");
        return;
    }
}

//nameRange.
//nameRange searches the contacts for a range of last names between two user
//input letters and prints all of these names.
//
//FUNCTIONAL DESCRIPTION.
//      1. Ask user to input two letters.
//      2. Iterate through each last name on the list checking to see if its 
//         first letter is inside the range .
//      3. Prints all the names from the name just printed up until the first 
//         name not in the range.

//ENTRY PARAMETERS
//*headPtr is the head of the list
//
//RETURN VALUES
//This function does not return anything.
void nameRange(addressInfo *headPtr) {
    
    //
    //Allocate space for string with user input letter range.
    //
    char *letterRange = malloc(3* sizeof(char)); 
    
    //
    //Ask user for range of letters and scan into letterRange.
    //
    printf("Enter the first and last letters (in CAPITALS) of the beginning"
            " of the range of last names you would like to search for: ");
    scanf("%s",letterRange);
    
    //
    //User did not enter a valid range (ex: ZA)
    //
    if (letterRange[0] > letterRange[1]) {
        printf("User did not enter a valid range of letters");
        return;
    }
    
    //Create pointers to traverse list.
    addressInfo *currentPtr;
    currentPtr=headPtr;
    
    //
    //Traverse list until end of list is reached
    //
    while (currentPtr != NULL) {
        //
        //Last name is in user input range.
        //
        if ((currentPtr->lastName[0] >= letterRange[0]) && (currentPtr->lastName[0] <= letterRange[1])) {
            printf("%s,%s\n",currentPtr->lastName,currentPtr->firstName);
            currentPtr=currentPtr->next;
        
        } else {
            currentPtr=currentPtr->next;
        }
    }
    
    //free character array
    free(letterRange);
}



//freeList
//freeList frees all memory allocated for list
//
//FUNCTIONAL DESCRIPTION.
//      1. Iterates through each node of the list
//      2. Frees each node
//
//ENTRY PARAMETERS
//*headPtr is the head of the list.
//
//RETURN VALUES
//This function does not return anything.
void freeList(addressInfo *headPtr) {
    //
    //Create pointer to traverse list.
    //
    addressInfo* currentPtr;
    currentPtr=headPtr->next;
    
    //
    //Traverse list until end of list is reached
    while (currentPtr != NULL) {
        free(headPtr);
        headPtr=currentPtr;
        currentPtr=currentPtr->next;
    }
}
    
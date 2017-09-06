/* 
 * File:   AddressBook.h
 * Author: HenryDaniels-Koch
 *
 * Created on February 6, 2015, 1:42 PM
 */

#ifndef AddressBook_H
#define	AddressBook_H

    //Define Structure
    typedef struct Entry {
        int month;
        int day;
        int year;
        char phoneNumber[100];
        char address[500];
        char lastName[100];
        char firstName[100];
        struct Entry *next;
    } addressInfo;  
    
    
#define BUFFER_SIZE 500 //length of buffer character array 

addressInfo *loadData();

void printContact(addressInfo *nodePtr);

void printAllContacts(addressInfo *headPtr);

addressInfo *insertNode(addressInfo *headPtr, addressInfo *nodePtr);

void searchLastName(addressInfo *headPtr);

void searchMonthNames(addressInfo *headPtr);

void nameRange(addressInfo *headPtr);

void freeList(addressInfo *headPtr);
    
#endif	/* AddressBook_H */


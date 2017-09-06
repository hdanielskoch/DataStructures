/* 
 * File:   BankAccount.cpp
 * Author: HenryDaniels-Koch
 *
 * Created on February 20, 2015, 1:18 PM
 */

//BankAccount.cpp.
//      Assignment3.c++-Source code for CSCI2101 Assignment 3.
//FUNCTIONAL DESCRIPTION
//      This program in C++ fulfills the requirements of Assignment 3 in
//      CSCI2101 Spring 2015
//
//      1. All functions are performed on the class: BankAccount.
//      2. If no parameters are specified for creating a bank account, an error
//         message is printed.
//      3. If the necessary parameters are specified, BankAccount creates a bank
//         account with a name, account number, and balance.
//      4. The user can deposit money to the account and update it accordingly
//      5. The user can withdraw money from their account and update it.
//      6. The user can close their account.
//      7. The user can print their account information.
//
//Notice
//      Copyright (C) February 20, 2015 to February 26 2015.
//      Henry Daniels-Koch All Rights Reserved.
//
#include <cstdlib>
#include <iostream>
#include <string>
#include "BankAccount.h"



using namespace std;

//BankAccount.
//BankAccount is a constructor method without parameters.
//
//FUNCTIONAL DESCRIPTION.
//      1. If the user does not put in parameters to BankAccount, an error
//         message is printed.
//
//ENTRY PARAMETERS
//There are no entry parameters.
//
//RETURN VALUES
//This function does not return anything.
BankAccount::BankAccount() {
    cout << "An account cannot be opened without an initial "
            "deposit greater than zero";
}

//BankAccount.
//BankAccount is a constructor method with parameters.
//
//FUNCTIONAL DESCRIPTION.
//      1. Creates a string firstName within BankAccount.
//      2. Creates a string lastName within BankAccount.
//      3. Creates an int accountNumber.
//      4. Creates an initial balance using deposit function.
//      5. Activates the account. 
//
//ENTRY PARAMETERS
//firstName is a string.
//lastName is a string.
//accountNumber is a string.
//balance is the initial balance one is depositing and an int.
//
//RETURN VALUES
//This function does not return anything.
BankAccount::BankAccount(string firstName, string lastName, int accountNumber, 
        double balance) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->accountNumber = accountNumber;
    deposit(balance);
    activeStatus = true;
}

//deposit.
//deposit adds money to the user's balance.
//
//FUNCTIONAL DESCRIPTION.
//      1. If amount user wishes to add is less than 0, function prints 
//         an error message.
//      2. Otherwise, the amount is added to the balance.
//
//ENTRY PARAMETERS
//amount is the money being deposited.
//
//RETURN VALUES
//This function does not return anything.
void BankAccount::deposit(double amount) {
    //
    //User entered negative amount.
    //
    if (amount <= 0) {
        cout << "Amount deposited must be greater than 0." << endl;
    
    } 
    //
    //User entered valid amount.
    //
    else {
        balance=balance+amount;
    }
}

//withdraw.
//deposit takes away money from the user's balance.
//
//FUNCTIONAL DESCRIPTION.
//      1. If amount user wishes to withdraw is less than 0 or exceed the 
//         balance function prints an error message.
//      2. Otherwise, the amount is subtracted from the balance.
//
//ENTRY PARAMETERS
//amount is the money being withdrawn.
//
//RETURN VALUES
//This function does not return anything.
double BankAccount::withdraw(double amount) {
    
    //
    //User entered negative amount.
    //
    if (amount <= 0) {
        cout << "Amount deposited cannot be negative." << endl;
        return 0;
        
    } 
    //
    //User entered amount greater than balance.
    //
    else if (amount > balance) {
        cout << "Error: Withdrawal exceeds your balance of: " << balance << endl;
        return 0; ///ASK!!!!
    } 
    //
    //User entered valid amount.
    //
    else {
        balance=balance-amount;
        return amount;
    }
}
//closeAccount.
//closeAccount closes the account and returns the remaining balance.
//
//FUNCTIONAL DESCRIPTION.
//      1. Balance is set to 0.
//      2. Account is deactivated.
//      3. Original balance before account was closed is returned
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
double BankAccount::closeAccount() {
    double tempBalance; //Temporary balance
    tempBalance=balance;
    balance = 0.0;
    activeStatus = false;
    return tempBalance;
}

//printAccountInfo.
//printAccountInfo prints all information about the account.
//
//FUNCTIONAL DESCRIPTION.
//      1. Prints account number.
//      2. Prints name of account.
//      3. Prints Balance.
//      4. Prints Activation Status
//
//ENTRY PARAMETERS
//No entry parameters.
//
//RETURN VALUES
//This function does not return anything.
void BankAccount::printAccountInfo() {
    cout << "Account Number: " << accountNumber << endl;
    cout << "Name:" << lastName << ", " << firstName << endl;
    cout << "Balance: $" << balance << endl;
    
    //
    //Account is active.
    //
    if (activeStatus == true) {
        cout << "Active: Yessssssss" << endl << endl;
    } 
    //
    //Account is inactive.
    //
    else {
        cout << "Active: Nooooooooo" << endl << endl;
    }
    
}

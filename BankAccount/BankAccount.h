/* 
 * File:   BankAccount.h
 * Author: HenryDaniels-Koch
 *
 * Created on February 21, 2015, 5:34 PM
 */

#ifndef BANKACCOUNT_H
#define	BANKACCOUNT_H
#include <string>

using namespace std;

//
//BankAccount creates objects (bank accounts) with names, account numbers, and
//balances. One can deposit money, withdraw money, get their balance, print
//their account information, and close their account.
//
class BankAccount {
    
public:
    BankAccount();
    BankAccount(string firstName, string lastName, int accountNumber, 
        double balance);
    double withdraw(double amount);
    double getBalance() { return balance; }
    double closeAccount();

    void deposit(double amount);
    void printAccountInfo();

//
//Creates variables within the class: BankAccount.
//
private:
    
    string firstName;
    string lastName;
    int accountNumber;
    double balance;
    bool activeStatus;
    
};

#endif	/* BANKACCOUNT_H */


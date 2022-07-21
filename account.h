#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include "date.h"
#include "utils.h"

using namespace std;

class account {
private:

    int account_id;
    static int next_account_id;

    string customer_national_id;

    double balance;
    date opening_date;
    bool is_active;


public:
    account();
    account(vector<string>& tokens);
    account(const string &customerNationalId, double balance, date openingDate, bool isActive);

    void setAccountId(int accountId);
    void setCustomerNationalId(string customerNationalId);
    void setBalance(double balance);
    int getAccountId();
    string getCustomerNationalId();
    double getBalance();
    const date &getOpeningDate();
    void setOpeningDate(const date &openingDate);
    bool isActive();
    void setIsActive(bool isActive);

    void deposit(double amount);
    void withdraw(double amount);

    friend std::ostream &operator<<(std::ostream &os, const account &account);
    friend class utils;

    string csv() const;

    static void saveAccounts(vector<account> &s);
    static bool loadAccounts(vector<account> &s);

};




#endif //ACCOUNT_H

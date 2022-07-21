#include "account.h"
#include <vector>

int account::next_account_id = 100;

account::account() {}

account::account(const string &customerNationalId, double balance, date openingDate, bool isActive) {
    account_id = next_account_id++;
    customer_national_id = customerNationalId;
    this->balance = balance;
    opening_date = openingDate;
    is_active = isActive;
}


std::ostream &operator<<(std::ostream &os, const account &account) {
    os << "Account ID: " << account.account_id << std::endl;
    os << "Customer ID: " << account.customer_national_id << std::endl;
    os << "Balance: " << account.balance << std::endl;
    os << "Opening Date: " << account.opening_date << std::endl;
    if (account.is_active) {
        os << "Account is active" << std::endl;
    } else {
        os << "Account is not active" << std::endl;
    }
    return os;
}

void account::deposit(double amount) {
    balance += amount;
}

void account::withdraw(double amount) {
    if (is_active) {
        if (balance >= amount)
            balance -= amount;
        else
            std::cout << "Insufficient balance" << std::endl;
    } else
        std::cout << "Account is not active" << std::endl;
}

int account::getAccountId() {
    return account_id;
}

void account::setAccountId(int accountId) {
    account_id = accountId;
}

string account::getCustomerNationalId() {
    return customer_national_id;
}

void account::setCustomerNationalId(string customerNationalId) {
    customer_national_id = customerNationalId;
}

double account::getBalance() {
    return balance;
}

void account::setBalance(double balance) {
    account::balance = balance;
}

const date &account::getOpeningDate() {
    return opening_date;
}

void account::setOpeningDate(const date &openingDate) {
    opening_date = openingDate;
}

bool account::isActive() {
    return is_active;
}

void account::setIsActive(bool isActive) {
    is_active = isActive;
}


string account::csv() const {
    return to_string(account_id) + "," +
           customer_national_id + "," +
           to_string(balance) + "," +
           opening_date.tostring() + "," +
           to_string(is_active);
}


account::account(vector<string> &v)
        : account_id(stoi(v[0])),
          customer_national_id(v[1]),
          balance(stod(v[2])),
          opening_date(v[3]),
          is_active(stoi(v[4])) {}




void account::saveAccounts(vector<account> &s) {
    ofstream file;
    file.open("accounts.txt");
    for (auto &account: s) {
        file << account.csv() << endl;
    }
    file.close();
}

bool account::loadAccounts(vector<account> &s) {
    ifstream file;
    file.open("accounts.txt");
    if (!file.is_open())
        return false;
    string line;
    int id = 0;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        vector<string> tokens = utils::tokenize(line, ',');
        int i = stoi(tokens[0]);
        if (i > id)
            id = i;
        s.emplace_back(tokens);
    }
    account::next_account_id = id + 1;
    file.close();
    return true;
}


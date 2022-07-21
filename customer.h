#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <vector>

using namespace std;


class customer {
private:
    int customer_id;

    static int next_customer_id;

    string name;
    string last_name;
    string national_id;
    string phone_number;
    string username;
    string password;

    void setPassword(const string &s);


public:

    customer();
    customer(vector<string> &tokens);
    customer(const string &name, const string &lastName, const string &nationalId,
             const string &phoneNumber, const string &username, const string &password);

    int getCustomerId();

    void setCustomerId(int customerId);

    const string &getName();

    void setName(const string &s);

    const string &getLastName();

    void setLastName(const string &s);

    const string &getNationalId();

    void setNationalId(const string &s);

    const string &getPhoneNumber();

    void setPhoneNumber(const string &s);

    const string &getUsername();

    void setUsername(const string &s);


    bool operator==(const customer &rhs) const;

    bool operator!=(const customer &rhs) const;

    friend ostream &operator<<(ostream &os, const customer &customer);


    bool checkLogin(const string &user, const string &pass);

    void printProfile();


    friend class bank;

    friend class utils;

    string csv() const;

    static void saveCustomers(vector<customer> &s);
    static bool loadCustomers(vector<customer> &s);

};


#endif //CUSTOMER_H

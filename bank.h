#ifndef BANK_H
#define BANK_H

#include <vector>
#include "customer.h"
#include "account.h"
#include "employee.h"
#include "admin.h"
#include "facilityEmployee.h"
#include "utils.h"

class bank {

private:

    utils u;

    string name;
    string code;
    string address;

    std::vector<customer> customers;
    std::vector<account> accounts;
    std::vector<employee> employees;
    admin a;
    facilityEmployee fe;

    int isLogin{}; // 0: not login, 1: customer, 2: admin, 3: facility employee, 4: employee
    string username;
    employee *currentEmployee;
    customer *currentCustomer;
    int currentAccount;
    vector<int> accountIndices;

public:

    bank(string name, string code, string address, admin &a);

    bool loginEmployee(const string& user, const string& pass);
    bool loginCustomer(const string& user, const string& pass);

    void customerMenu();

    void employeeMenu();

    int findCustomer(const string& id);

    void saveAll();

    void loadAll();

    void report(string s);
};


#endif //BANK_H

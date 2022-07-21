#include "bank.h"

bool bank::loginCustomer(const string &user, const string &pass) {
    if (!customers.empty())
        for (auto &c: customers) {
            if (c.checkLogin(user, pass)) {
                isLogin = true;
                username = user;
                currentCustomer = &c;
                for (int i = 0; i < accounts.size(); i++)
                    if (accounts[i].getCustomerNationalId() == c.getNationalId())
                        accountIndices.push_back(i);
                currentAccount = accountIndices.empty() ? -1 : 0;
                report("Customer with national id " + c.getNationalId() + " logged in successfully.");
                return true;
            }
        }
    return false;
}

bool bank::loginEmployee(const string &user, const string &pass) {

    if (a.checkLogin(user, pass)) {
        isLogin = a.type + 1;
        username = user;
        currentEmployee = &a;
        report("Admin with username " + user + " and personal code " + to_string(a.getPersonalId()) +
               " logged in successfully.");
        return true;
    } else if (a.getUsername() == user)
        return false;

    if (fe.checkLogin(user, pass)) {
        isLogin = fe.type + 1;
        username = user;
        currentEmployee = &fe;
        report("Facility employee with username " + user + " and personal code " + to_string(fe.getPersonalId()) +
               " logged in successfully.");
        return true;
    } else if (fe.getUsername() == user)
        return false;

    if (!employees.empty())
        for (auto &e: employees) {
            if (e.checkLogin(user, pass)) {
                isLogin = e.type + 1;
                username = user;
                currentEmployee = &e;
                report("Employee with username " + user + " and personal code " + to_string(e.getPersonalId()) +
                       " logged in successfully.");
                return true;
            }
        }

    return false;
}

void bank::customerMenu() {

    do {
        system("cls");
        cout << "===================================" << endl;
        cout << "customer menu: " << endl;
        if (currentAccount == -1)
            cout << "Customer has no account" << endl;
        else {
            cout << "-> Select Account: " << endl;
            cout << "---- selected account: " << accounts[accountIndices[currentAccount]].getAccountId() << endl;
            for (auto &index: accountIndices) {
                auto &acc = accounts[index];
                cout << acc.getAccountId() << ") ";
                if (acc.isActive())
                    cout << "Active";
                else
                    cout << "Inactive";
                cout << " Account" << endl;
                cout << "    Balance: " << acc.getBalance() << ", Open Date: " << acc.getOpeningDate() << endl;
            }
        }
        cout << "1) Deposit" << endl;
        cout << "2) Withdraw" << endl;
        cout << "3) profile" << endl;
        cout << "4) change password" << endl;
        cout << "5) logout" << endl;
        cout << "===================================" << endl << endl;

        cout << "Enter your choice: ";
        int ch;
        cin >> ch;
        if (currentAccount == -1 && (ch == 1 || ch == 2)) {
            cout << "You have no account" << endl;
        } else if (ch < 0 || ch > 5) {
            int f = -1;
            for (auto &index: accountIndices) {
                auto &acc = accounts[index];
                if (acc.getAccountId() == ch) {
                    f = index;
                    if (acc.isActive())
                        currentAccount = f;
                    else
                        cout << "Account is inactive" << endl;
                    break;
                }
            }
            if (f == -1)
                cout << "Invalid selection ... " << endl;
        } else {
            if (ch == 0 and currentAccount == -1) {

            } else if (ch == 1) {
                double amount;
                cout << "Enter amount: ";
                cin >> amount;
                if (amount < 0) {
                    cout << "Invalid amount" << endl;
                } else {
                    int i = accountIndices[currentAccount];
                    accounts[i].deposit(amount);
                    account::saveAccounts(accounts);
                    report("Deposit of " + to_string(amount) + " to account "
                           + to_string(accounts[i].getAccountId()) + " successful.");
                }
            } else if (ch == 2) {
                double amount;
                cout << "Enter amount: ";
                cin >> amount;
                if (amount < 0) {
                    cout << "Invalid amount" << endl;
                } else {
                    int i = accountIndices[currentAccount];
                    accounts[i].withdraw(amount);
                    account::saveAccounts(accounts);
                    report("Withdraw of " + to_string(amount) + " from account "
                           + to_string(accounts[i].getAccountId()) + " successful.");
                }
            } else if (ch == 3) {
                cout << "===================================" << endl;
                currentCustomer->printProfile();
                cout << "\n===================================" << endl;
            } else if (ch == 4) {
                string oldPass, newPass;
                cout << "Enter old password: ";
                cin >> oldPass;
                cout << "Enter new password: ";
                cin >> newPass;
                if (currentCustomer->checkLogin(username, oldPass)) {
                    currentCustomer->setPassword(newPass);
                    cout << "Password changed" << endl;
                    customer::saveCustomers(customers);
                    report("Password changed for customer with national id " + currentCustomer->getNationalId() +
                           ".");
                } else {
                    cout << "Invalid password" << endl;
                }
            } else if (ch == 5) {
                isLogin = 0;
                username = "";
                currentCustomer = nullptr;
                currentAccount = -1;
                accountIndices.clear();
                report("Customer with national id " + currentCustomer->getNationalId() + " logged out successfully.");
                cout << "Logout successful" << endl;
                break;
            }
        }
        cout << "Press enter to continue...";
        cin.get();
        cin.get();
    } while (true);
}

void bank::employeeMenu() {
    string names[3] = {"admin", "facility manager", "employee"};
    if (isLogin < 2)
        return;
    do {
        system("cls");
        cout << "===================================" << endl;
        cout << names[isLogin - 2] << " menu: " << endl;
        cout << "1) off request" << endl;
        cout << "2) overtime request" << endl;
        cout << "3) profile" << endl;
        cout << "4) customer profile" << endl;
        cout << "5) create customer account" << endl;
        cout << "6) remove customer account" << endl;
        if (isLogin == 2) {
            cout << "7) find employee" << endl;
            cout << "8) hire employee" << endl; // create employee
            cout << "9) fire employee" << endl; // remove employee
        }
        cout << "q) logout" << endl;
        cout << "===================================" << endl << endl;
        cout << "Enter your choice: ";
        char choice;
        cin >> choice;
        if (choice == 'q') {
            break;
            report("Employee with username " + username + " and personal code " +
                   to_string(currentEmployee->getPersonalId()) +" logged out successfully.");
        }
        int ch = choice - '0';

        if (ch == 1) {
            int h;
            cout << "\n===================================" << endl;
            cout << "Enter hours: ";
            cin >> h;
            if (h > 0) {
                int off = currentEmployee->checkOffHour(h);
                cout << "you have used " << -(off + h - 15) << " off hours" << endl;
                if (off < 0) {
                    double newSalary = currentEmployee->getSalary() + (off * 100.0);
                    cout << "if you accept this request, your salary will be reduced by " << (off * 100.0) << endl;
                    cout << "new salary: " << newSalary << endl;
                    cout << "accept? (y/n) ";
                    char c;
                    cin >> c;
                    if (c == 'y') {
                        currentEmployee->addOffHour(h);
                        cout << "off request accepted" << endl;
                        employee::saveEmployees(employees);
                        report("Off request [" + to_string(h) + " hours] accepted by employee with personalID " +
                               to_string(currentEmployee->getPersonalId()) + "and salary reduced by " +
                               to_string(off * 100.0) + ".");
                    } else {
                        cout << "request rejected" << endl;
                    }
                } else {
                    currentEmployee->addOffHour(h);
                    cout << "off request accepted" << endl;
                    int remain = currentEmployee->checkOffHour(0);
                    cout << "you have " << remain << " off hours left" << endl;
                    employee::saveEmployees(employees);
                    report("Off request [" + to_string(h) + " hours] accepted by employee with personalID " +
                           to_string(currentEmployee->getPersonalId()) + ".");
                }

            } else
                cout << "Invalid off hour" << endl;

        } else if (ch == 2) {
            int h;
            cout << "\n===================================" << endl;
            cout << "Enter hours: ";
            cin >> h;
            if (h > 0) {
                int overtime = currentEmployee->checkOvertime(h);
                cout << "you have worked " << -(overtime + h - 12) << " hours overtime." << endl;
                if (overtime < 0) {
                    cout << "you cannot work more than 12 hours overtime" << endl;
                    cout << "your request is rejected" << endl;
                } else {
                    cout << "if you accept this request, your salary will be increased by " << (overtime * 100.0)
                         << endl;
                    cout << "new salary: " << currentEmployee->getSalary() + (overtime * 120.0) << endl;
                    cout << "accept? (y/n) ";
                    char c;
                    cin >> c;
                    if (c == 'y') {
                        currentEmployee->addOvertime(h);
                        cout << "overtime request accepted" << endl;
                        employee::saveEmployees(employees);
                        report("Overtime request [" + to_string(h) + " hours] accepted by employee with personalID " +
                               to_string(currentEmployee->getPersonalId()) + "and salary increased by " +
                               to_string(overtime * 120.0) + ".");
                    } else {
                        cout << "request rejected" << endl;
                    }
                }
            } else
                cout << "Invalid overtime hour" << endl;
        } else if (ch == 3) {
            cout << "===================================" << endl;
            cout << "profile: " << endl;
            cout << *currentEmployee << endl;
            cout << "===================================" << endl;
        } else if (ch == 4 || ch == 5 || ch == 6) {
            string id;
            cout << "Enter Customer National ID: ";
            cin >> id;
            int i = findCustomer(id);
            if (i == -1) {
                if (ch != 5)
                    cout << "Customer not found" << endl;
                else {
                    // create customer
                    string n, l, phone, user, pass;
                    cout << "===================================" << endl;
                    cout << "Enter name: ";
                    cin >> n;
                    cout << "Enter last name: ";
                    cin >> l;
                    cout << "Enter phone number: ";
                    cin >> phone;
                    cout << "Enter username: ";
                    cin >> user;
                    cout << "Enter password: ";
                    cin >> pass;
                    bool exist = false;
                    if (!customers.empty())
                        for (auto &customer: customers) {
                            if (customer.getUsername() == user) {
                                cout << "Username already exists" << endl;
                                exist = true;
                                break;
                            }
                        }
                    if (!exist) {
                        customers.emplace_back(n, l, id,
                                               phone, user, pass);
                        cout << "Customer created" << endl;
                        customer::saveCustomers(customers);
                        report("Customer with national ID " + id + " created.");
                    }
                }
            } else {
                cout << "===================================" << endl;
                cout << "profile: " << endl;
                cout << customers[i] << endl;
                cout << "===================================" << endl;
            }
            if (ch == 5) {
                // create account for customer[i]
                double balance;
                cout << "Enter balance: ";
                cin >> balance;
                // balance must be greater than 50000
                if (balance >= 50000) {
                    accounts.emplace_back(id, balance, date(), true);
                    cout << "Account created" << endl;
                    account::saveAccounts(accounts);
                    report("Account " + to_string(accounts.back().getAccountId()) +
                           " created for customer with national ID " + id + ".");
                } else
                    cout << "Initial balance must be greater than 50000" << endl;
            }
            if (ch == 6 && i != -1) {
                // show all accounts of customer[i]
                cout << "===================================" << endl;
                cout << "Accounts: " << endl;
                bool found = false;
                if (!accounts.empty())
                    for (auto &account: accounts) {
                        if (account.getCustomerNationalId() == id) {
                            cout << account << endl;
                            cout << "-----------------------------------" << endl;
                            found = true;
                        }
                    }
                if (!found) {
                    customers.erase(customers.begin() + i);
                    cout << "Customer has no account, customer deleted" << endl;
                    customer::saveCustomers(customers);
                    report("Customer with national ID " + id + " deleted because he/she has no account.");
                } else {
                    cout << "===================================" << endl;
                    cout << "Select Account ID to delete: ";
                    int accId;
                    cin >> accId;
                    bool f = false;
                    for (auto &account: accounts) {
                        if (account.getAccountId() == accId) {
                            accounts.erase(accounts.begin() + i);
                            cout << "Account deleted" << endl;
                            f = true;
                            account::saveAccounts(accounts);
                            report("Account " + to_string(accId) + " deleted.");
                            break;
                        }
                    }
                    if (!f)
                        cout << "Account not found" << endl;
                    if (accounts.empty()) {
                        // delete customer[i]
                        customers.erase(customers.begin() + i);
                        cout << "Customer has no account, customer deleted" << endl;
                        customer::saveCustomers(customers);
                        report("Customer with national ID " + id + " deleted because he/she has no account.");
                    }
                }
            }
        } else if ((ch == 7 || ch == 9) && isLogin == 2) {
            // find employee by personal code
            int personalCode;
            cout << "Enter personal code: ";
            cin >> personalCode;
            bool foundEmployee = false;
            int i = 0;
            if (!employees.empty())
                for (auto &employee: employees) {
                    if (employee.getPersonalId() == personalCode) {
                        foundEmployee = true;
                        break;
                    }
                    i++;
                }
            if (foundEmployee) {
                cout << "===================================" << endl;
                cout << "profile: " << endl;
                cout << employees[i] << endl;
                cout << "===================================" << endl;
                if (ch == 9) {
                    // delete employee[i]
                    employees.erase(employees.begin() + i);
                    cout << "Employee deleted" << endl;
                    employee::saveEmployees(employees);
                    report("Employee with personal ID " + to_string(personalCode) + " deleted.");
                }
            } else
                cout << "Employee not found" << endl;

        } else if (ch == 8 && isLogin == 2) {
            // create employee
            string n, l, user, pass, b_year, b_month, b_day, salary;
            cout << "===================================" << endl;
            cout << "Enter name: ";
            cin >> n;
            cout << "Enter last name: ";
            cin >> l;
            cout << "Enter username: ";
            cin >> user;
            cout << "Enter password: ";
            cin >> pass;
            cout << "Enter birth year: ";
            cin >> b_year;
            cout << "Enter birth month: ";
            cin >> b_month;
            cout << "Enter birth day: ";
            cin >> b_day;
            cout << "Enter salary: ";
            cin >> salary;
            bool exist = false;
            if (!employees.empty())
                for (auto &employee: employees) {
                    if (employee.getUsername() == user) {
                        cout << "Username already exists" << endl;
                        exist = true;
                        break;
                    }
                }
            date d;
            bool valid = true;
            try {
                d.setDay(stoi(b_day));
                d.setMonth(stoi(b_month));
                d.setYear(stoi(b_year));
            } catch (...) {
                valid = false;
            }
            if (!valid)
                cout << "Invalid birth date" << endl;
            else if (!exist) {
                employees.emplace_back(n, l, user, pass, d, stoi(salary));
                cout << "Employee created" << endl;
                cout << "Employee Personal ID: " << employees.back().getPersonalId() << endl;
                employee::saveEmployees(employees);
                report("Employee with personal ID " + to_string(employees.back().getPersonalId()) + " created.");
            } else
                cout << "Employee not created" << endl;
        } else {
            cout << "Invalid selection" << endl;
        }
        cout << "Press enter to continue...";
        cin.get();
        cin.get();

    } while (true);
}


bank::bank(string
           name, string
           code, string
           address, admin &a)
        : name(name), code(code),
          address(address), a(a) {}


int bank::findCustomer(const string &id) {
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getNationalId() == id)
            return i;
    }
    return -1;
}

void bank::saveAll() {
    customer::saveCustomers(customers);
    employee::saveEmployees(employees);
    account::saveAccounts(accounts);
    employee::saveEmployee(&a);
    employee::saveEmployee(&fe);
}

void bank::loadAll() {
    customer::loadCustomers(customers);
    employee::loadEmployees(employees);
    account::loadAccounts(accounts);
    employee::loadEmployee(&a, 1);
    employee::loadEmployee(&fe, 2);
}


void bank::report(string s) {
    u.report(s);
}
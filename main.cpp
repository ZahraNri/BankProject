#include <iostream>
#include "bank.h"

using namespace std;

int menu();

int login(bank &, int);


int main() {

    admin a = admin("admin", "admin", "admin", "admin",
                    date(1, 1, 1), 0);
    bank b("Enghelab", "Eg-110", "Enghelab street", a);
    b.loadAll();
    b.report("Application started");

    int type;

    while ((type = menu()) != 0) {
        int l = login(b, type - 1);
        if (l == 0) {
            cout << "Login failed" << endl;
            cout << "Press any key to continue..." << endl;
            cin.get();
            cin.get();
            continue;
        }

        if (l == 1) {
            b.customerMenu();
        } else if (l == 2) {
            b.employeeMenu();
        }

    }

    b.saveAll();
    b.report("Application closed");
    cout << "Goodbye!" << endl;
    return 0;
}


int menu() {

    char ch;
    do {
        system("cls");
        cout << "===================================" << endl;
        cout << "bank menu: " << endl;
        cout << "1) Employee" << endl;
        cout << "2) Customer" << endl;
        cout << "q) Exit" << endl;
        cout << "===================================" << endl << endl;
        cout << "Enter your choice: ";

        cin >> ch;
        if (ch != '1' && ch != '2' && tolower(ch) != 'q') {
            cout << "Invalid input" << endl;
        } else break;
    } while (true);

    if (ch == '1')
        return 1;
    else if (ch == '2')
        return 2;
    else
        return 0;
}

int login(bank &b, int type) {

    string names[2] = {"employee", "customer"};
    string username, password;

    system("cls");
    cout << "===================================" << endl;
    cout << "login as " << names[type] << ": " << endl;
    cout << "username: ";
    cin >> username;
    cout << "password: ";
    cin >> password;
    cout << "\n===================================" << endl << endl;

    int l;
    if (type == 0)
        l = b.loginEmployee(username, password) ? 2 : 0;
    else {
        l = b.loginCustomer(username, password);
    }


    return l;
}

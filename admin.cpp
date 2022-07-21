#include "admin.h"

string admin::toStr() const {
    return "Admin: " + employee::toStr();
}

admin::admin(string name, string lastName, string username, string password,
             date birthDate, double salary) :
        employee(name, lastName, username, password,
                 birthDate, salary) {
    type = 1;
}

admin::admin(vector<string> &tokens) : employee(tokens) {}






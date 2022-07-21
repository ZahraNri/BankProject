#ifndef ADMIN_H
#define ADMIN_H

#include "employee.h"

class admin : public employee {


public:

    string toStr() const override;

    admin(string name, string lastName, string username, string password,
            date birthDate, double salary);
    admin(vector<string>& tokens);


};


#endif //ADMIN_H

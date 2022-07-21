#ifndef FACILITYEMPLOYEE_H
#define FACILITYEMPLOYEE_H


#include "employee.h"

class facilityEmployee: public employee {


public:
    string toStr() const override;

    facilityEmployee(vector<string>& tokens);
    facilityEmployee();
};


#endif //FACILITYEMPLOYEE_H

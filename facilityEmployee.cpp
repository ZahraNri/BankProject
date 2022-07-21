#include "facilityEmployee.h"

string facilityEmployee::toStr() const {
    return "Facility Employee: " + employee::toStr();
}

facilityEmployee::facilityEmployee() {
    type = 2;
}

facilityEmployee::facilityEmployee(vector<string> &tokens) : employee(tokens) {}

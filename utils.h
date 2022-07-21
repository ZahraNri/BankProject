
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "account.h"
#include "customer.h"
#include "employee.h"

using namespace std;

class utils {

    ofstream file;

public:

    utils();

    static vector<string> tokenize(const string &str, char delimiter);

    // report
    void report(const string &msg);


};


#endif //UTILS_H

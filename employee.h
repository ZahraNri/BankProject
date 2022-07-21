#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include <map>
#include "date.h"
#include "utils.h"

using namespace std;

class employee {


protected:
    int personal_id;
    static int next_personal_id;
    string name;
    string last_name;
    string username;
    string password;
    date birth_date;
    double salary;
    int off_hours;
    int overtime;
    int type;  // 1 for admin, 2 for facilityEmployee, 3 for employee

    void setPassword(const string &pass);

    bool checkLogin(string user, string pass);


public:

    employee();

    employee(string name, string lastName, string username, string password,
             date birthDate, double salary);

    employee(vector<string> &tokens);

    int getPersonalId();

    void setPersonalId(int personalId);

    static int getNextPersonalId();

    static void setNextPersonalId(int nextPersonalId);

    const string &getName();

    void setName(const string &name);

    const string &getLastName();

    void setLastName(const string &lastName);

    const string &getUsername();

    void setUsername(const string &user);

    const date &getBirthDate();

    void setBirthDate(const date &birthDate);

    double getSalary();

    void setSalary(double salary);

    int getType();

    void setType(int type);

    // tostring
    virtual string toStr() const;

    friend ostream &operator<<(ostream &os, const employee &employee);

    int checkOffHour(int h);

    int checkOvertime(int h);

    void addOffHour(int h);

    void addOvertime(int h);

    double getNewSalary() const;

    friend class bank;

    friend class utils;

    string csv() const;

    static void saveEmployees(vector<employee> &s);

    static bool loadEmployees(vector<employee> &s);

    static void saveEmployee(employee *employee);

    static bool loadEmployee(employee *employee, int type);

};


#endif //EMPLOYEE_H

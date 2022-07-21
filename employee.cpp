#include "employee.h"


int employee::next_personal_id = 100;

employee::employee() : personal_id(0), birth_date(0, 0, 0),
                       salary(0), type(3), off_hours(0), overtime(0) {}

employee::employee(string name, string lastName, string username, string password,
                   date birthDate, double salary) :
        personal_id(next_personal_id++),
        name(name),
        last_name(lastName),
        username(username),
        password(password),
        birth_date(birthDate),
        salary(salary),
        type(3),
        off_hours(0),
        overtime(0) {}


int employee::getPersonalId() {
    return personal_id;
}

void employee::setPersonalId(int personalId) {
    personal_id = personalId;
}

int employee::getNextPersonalId() {
    return next_personal_id;
}

void employee::setNextPersonalId(int nextPersonalId) {
    next_personal_id = nextPersonalId;
}

const string &employee::getName() {
    return name;
}

void employee::setName(const string &name) {
    employee::name = name;
}

const string &employee::getLastName() {
    return last_name;
}

void employee::setLastName(const string &lastName) {
    last_name = lastName;
}

const string &employee::getUsername() {
    return username;
}

void employee::setUsername(const string &user) {
    employee::username = user;
}

void employee::setPassword(const string &pass) {
    employee::password = pass;
}

const date &employee::getBirthDate() {
    return birth_date;
}

void employee::setBirthDate(const date &birthDate) {
    birth_date = birthDate;
}

double employee::getSalary() {
    return salary;
}

void employee::setSalary(double salary) {
    employee::salary = salary;
}


int employee::getType() {
    return type;
}

void employee::setType(int type) {
    employee::type = type;
}


ostream &operator<<(ostream &os, const employee &employee) {
    os << employee.toStr();
    return os;
}

string employee::toStr() const {
    string str;
    str += "personal_id: " + to_string(personal_id) + "\n";
    str += "name: " + name + " " + last_name + "\n";
    str += "username: " + username + "\n";
    str += "salary: " + to_string(salary) + "\n";
    if (salary != getNewSalary())
        str += "new salary after overtime and off hours: " + to_string(getNewSalary()) + "\n";
    str += "birth date: " + birth_date.tostring() + "\n";
    return str;
}

bool employee::checkLogin(string user, string pass) {
    return username == user && password == pass;
}


int employee::checkOffHour(int h) {
    return 15 - (off_hours + h);
}

int employee::checkOvertime(int h) {
    return 12 - (overtime + h);
}

void employee::addOffHour(int h) {
    off_hours += h;
}

void employee::addOvertime(int h) {
    if (overtime + h > 12) {
        overtime = 12;
    } else {
        overtime += h;
    }
}

double employee::getNewSalary() const {
    double new_salary = salary;
    if (off_hours > 15) {
        new_salary += (15 - off_hours) * 100.0;
    }
    new_salary += (overtime * 120.0);
    return new_salary;
}

string employee::csv() const {
    string str;
    str += to_string(personal_id) + ",";
    str += name + ",";
    str += last_name + ",";
    str += username + ",";
    str += password + ",";
    str += birth_date.tostring() + ",";
    str += to_string(salary) + ",";
    str += to_string(type) + ",";
    str += to_string(off_hours) + ",";
    str += to_string(overtime);
    return str;
}

employee::employee(vector<string> &tokens)
        : personal_id(stoi(tokens[0])),
          name(tokens[1]),
          last_name(tokens[2]),
          username(tokens[3]),
          password(tokens[4]),
          birth_date(tokens[5]),
          salary(stod(tokens[6])),
          type(stoi(tokens[7])),
          off_hours(stoi(tokens[8])),
          overtime(stoi(tokens[9])) {}





void employee::saveEmployees(vector<employee> &s) {
    ofstream file;
    file.open("employees.txt");
    for (auto &employee: s) {
        file << employee.csv() << endl;
    }
    file.close();
}

bool employee::loadEmployees(vector<employee> &s) {
    ifstream file;
    file.open("employees.txt");
    if (!file.is_open())
        return false;
    string line;
    int id = 0;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        vector<string> tokens = utils::tokenize(line, ',');
        int i = stoi(tokens[0]);
        if (i > id)
            id = i;
        s.emplace_back(tokens);
    }
    employee::next_personal_id = id + 1;
    file.close();
    return true;
}


void employee::saveEmployee(employee *employee) {
    ofstream file;
    if (employee->getType() == 1) {
        file.open("admin.txt");
    } else if (employee->getType() == 2) {
        file.open("facilityEmployee.txt");
    } else {
        file.open("employee.txt");
    }
    file << employee->csv();
    file.close();
}

bool employee::loadEmployee(employee *employee, int type) {
    ifstream file;
    if (type == 1) {
        file.open("admin.txt");
    } else if (type == 2) {
        file.open("facilityEmployee.txt");
    }
    if (!file.is_open())
        return false;
    string line;
    getline(file, line);
    vector<string> tokens = utils::tokenize(line, ',');
    employee->setPersonalId(stoi(tokens[0]));
    employee->setName(tokens[1]);
    employee->setLastName(tokens[2]);
    employee->setUsername(tokens[3]);
    employee->setPassword(tokens[4]);
    employee->setBirthDate(tokens[5]);
    employee->setSalary(stod(tokens[6]));
    employee->setType(stoi(tokens[7]));
    employee->off_hours = stoi(tokens[8]);
    employee->overtime = stoi(tokens[9]);
    file.close();
    return true;
}



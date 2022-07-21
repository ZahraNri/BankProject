#include <fstream>
#include "customer.h"
#include "utils.h"

int customer::next_customer_id = 1;


int customer::getCustomerId() {
    return customer_id;
}


void customer::setCustomerId(int customerId) {
    customer_id = customerId;
}

const string &customer::getName() {
    return name;
}

void customer::setName(const string &n) {
    customer::name = n;
}

const string &customer::getLastName() {
    return last_name;
}

void customer::setLastName(const string &lastName) {
    last_name = lastName;
}

const string &customer::getNationalId() {
    return national_id;
}

void customer::setNationalId(const string &s) {
    national_id = s;
}

const string &customer::getPhoneNumber() {
    return phone_number;
}

void customer::setPhoneNumber(const string &s) {
    phone_number = s;
}

const string &customer::getUsername() {
    return username;
}

void customer::setUsername(const string &s) {
    customer::username = s;
}


void customer::setPassword(const string &s) {
    customer::password = s;
}


bool customer::operator==(const customer &rhs) const {
    return customer_id == rhs.customer_id;
}

bool customer::operator!=(const customer &rhs) const {
    return !(rhs == *this);
}


ostream &operator<<(ostream &os, const customer &customer) {
    os << "username: " << customer.username
       << "\nname: " << customer.name << " " << customer.last_name;
    return os;
}


bool customer::checkLogin(const string &user, const string &pass) {
    return username == user && password == pass;
}

void customer::printProfile() {
    cout << *this
         << "\nnational id: " << national_id
         << "\nphone number: " << phone_number;
}

customer::customer() {}


customer::customer(const string &name, const string &lastName, const string &nationalId, const string &phoneNumber,
                   const string &username, const string &password) : customer_id(next_customer_id++),
                                                                     name(name),
                                                                     last_name(lastName),
                                                                     national_id(nationalId),
                                                                     phone_number(phoneNumber),
                                                                     username(username),
                                                                     password(password) {}

customer::customer(vector<string> &tokens) : customer_id(stoi(tokens[0])),
                                             name(tokens[1]),
                                             last_name(tokens[2]),
                                             national_id(tokens[3]),
                                             phone_number(tokens[4]),
                                             username(tokens[5]),
                                             password(tokens[6]) {}

string customer::csv() const {
    return to_string(customer_id) + "," +
           name + "," +
           last_name + "," +
           national_id + "," +
           phone_number + "," +
           username + "," +
           password;
}


void customer::saveCustomers(vector<customer> &s) {
    ofstream file;
    file.open("customers.txt");
    for (auto &customer: s) {
        file << customer.csv() << endl;
    }
    file.close();
}

bool customer::loadCustomers(vector<customer> &s) {
    ifstream file;
    file.open("customers.txt");
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
    customer::next_customer_id = id + 1;
    file.close();
    return true;
}


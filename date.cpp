#include <sstream>
#include "date.h"
#include "utils.h"

date::date(int day, int month, int year) : day(day), month(month), year(year) {}

date::date() {
    // get current system date
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    day = ltm->tm_mday;
    month = ltm->tm_mon + 1;
    year = ltm->tm_year + 1900;
}

int date::getDay() {
    return day;
}

void date::setDay(int d) {
    if (d > 0 && d <= 31) {
        day = d;
    } else
        throw;
}

int date::getMonth() {
    return month;
}

void date::setMonth(int m) {
    if (m > 0 && m <= 12) {
        month = m;
    } else
        throw;
}

int date::getYear() {
    return year;
}

void date::setYear(int y) {
    if (y > 0) {
        year = y;
    } else
        throw;
}



ostream &operator<<(ostream &os, const date &date) {
    os << date.tostring();
    return os;
}

string date::tostring() const {
    string str;
    str += to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    return str;
}

date::date(const string& d) {
    auto tokens = utils::tokenize(d, '/');
    day = stoi(tokens[0]);
    month = stoi(tokens[1]);
    year = stoi(tokens[2]);
}

